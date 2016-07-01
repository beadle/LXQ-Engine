#pragma once


class Time
{
public:
	static void SetFrameRate(int rate);
	static int GetFrameRate();

	static float GetDeltaTime();
	static float GetFixedDeltaTime();

protected:
	Time();
	~Time();

	friend class Window;
};

