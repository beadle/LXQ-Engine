#pragma once

#include <Windows.h>


class Window
{
public:
	Window();
	~Window();

	void Initialize();
	void Run();
	void Finalize();

protected:
	void InitializeWindow();
	void ShutdownWindows();

protected:
	bool _fullScreen;

	LPCWSTR _applicationName;
	HINSTANCE _hinstance;
	HWND _hwnd;
};

