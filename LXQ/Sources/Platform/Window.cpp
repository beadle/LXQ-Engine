#include <fstream>
#include <time.h>
#include <chrono>

#include "Window.h"
#include "Gameplay.h"
#include "Logger.h"
#include "json11.hpp"
#include "Time.h"


Window::Window()
{
	_deltaTime = 0.0;
	_frameRate = 0;
	_frameInterval.QuadPart = 0;
}


Window::~Window()
{
}

void Window::Initialize()
{
	Logger::Initialize();

	this->InitializeWindow();

	Gameplay::GetInstance()->Initialize();
}

void Window::Run()
{
	MSG msg;
	bool done, result;

	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));

	// Main message loop:
	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;
	
	QueryPerformanceCounter(&nLast);

	// Loop until there is a quit message from the window or the user.
	done = false;
	while (!done)
	{
		// Handle the windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			QueryPerformanceCounter(&nNow);
			if (nNow.QuadPart - nLast.QuadPart > _frameInterval.QuadPart)
			{
				LARGE_INTEGER nFreq;
				QueryPerformanceFrequency(&nFreq);
				_deltaTime = double(nNow.QuadPart - nLast.QuadPart) / nFreq.QuadPart;

				nLast.QuadPart = nNow.QuadPart - (nNow.QuadPart % _frameInterval.QuadPart);

				// Otherwise do the frame processing.
				result = Gameplay::GetInstance()->MainLoop();
				if (!result)
				{
					done = true;
				}
			}
		}

	}
}

void Window::Finalize()
{
	Gameplay::GetInstance()->Finalize();

	this->ShutdownWindows();

	Logger::Finalize();
}

LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		// Check if a key has been pressed on the keyboard.
	case WM_KEYDOWN:
	{
		return 0;
	}
	case WM_KEYUP:
	{
		return 0;
	}
	default:
	{
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
	{
		return MessageHandler(hwnd, umessage, wparam, lparam);
	}
	}
}

void Window::SetFrameRate(int rate)
{
	_frameRate = rate;
	double interval = 1.0 / rate;
	LARGE_INTEGER nFreq;
	QueryPerformanceFrequency(&nFreq);
	_frameInterval.QuadPart = (LONGLONG)(interval * nFreq.QuadPart);
}

void Window::InitializeWindow()
{
	std::ifstream ifs("_Config/Engine.json");
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	std::string err;
	auto config = json11::Json::parse(content, err)["window"];

	SetFrameRate(config["frameRate"].int_value());

	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	// Get the instance of this application.
	_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	WCHAR   wstr[MAX_PATH] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, config["title"].string_value().c_str(), -1, wstr, sizeof(wstr));
	_applicationName = wstr;

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = _hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = _applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// TODO: Read from config file
	_fullScreen = config["fullScreen"].bool_value();
	auto screenWidth = config["width"].int_value();
	auto screenHeight = config["height"].int_value();

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (_fullScreen)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)GetSystemMetrics(SM_CXSCREEN);
		dmScreenSettings.dmPelsHeight = (unsigned long)GetSystemMetrics(SM_CYSCREEN);
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// 全屏和窗口使用不同的参数. 
	if (_fullScreen)
	{
		_hwnd = CreateWindowEx(WS_EX_APPWINDOW, _applicationName, _applicationName,
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
			posX, posY, screenWidth, screenHeight, NULL, NULL, _hinstance, NULL);
	}
	else
	{
		_hwnd = CreateWindowEx(WS_EX_APPWINDOW, _applicationName, _applicationName,
			WS_OVERLAPPEDWINDOW,
			posX, posY, screenWidth, screenHeight, NULL, NULL, _hinstance, NULL);
	}

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(_hwnd, SW_SHOW);
	SetForegroundWindow(_hwnd);
	SetFocus(_hwnd);

	// Hide the mouse cursor.
	// ShowCursor(false);

	return;
}

void Window::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if (_fullScreen)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(_hwnd);
	_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(_applicationName, _hinstance);
	_hinstance = NULL;

}
