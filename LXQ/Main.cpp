#include "Platform/Window.h"


int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	Window window;
	window.Initialize();
	
	window.Run();

	window.Finalize();

	return 0;
}
