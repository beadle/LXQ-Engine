#include "Time.h"
#include "Window.h"


Time::Time()
{
}


Time::~Time()
{
}

void Time::SetFrameRate(int rate)
{
	Window::GetInstance()->SetFrameRate(rate);
}

int Time::GetFrameRate()
{
	return Window::GetInstance()->GetFrameRate();
}

float Time::GetDeltaTime()
{
	return Window::GetInstance()->GetDeltaTime();
}

float Time::GetFixedDeltaTime()
{
	return 1.0f / Time::GetFrameRate();
}
