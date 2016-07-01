#pragma once

#include <Windows.h>
#include <ctime>
#include "Singleton.h"


class Window : public Singleton<Window>
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

	void SetFrameRate(int rate);
	int GetFrameRate() { return _frameRate; }
	float GetDeltaTime() { return _deltaTime; }

	friend class Time;
protected:
	bool _fullScreen;
	int _frameRate;
	float _deltaTime;

	LARGE_INTEGER _frameInterval;
	LPCWSTR _applicationName;
	HINSTANCE _hinstance;
	HWND _hwnd;
};

