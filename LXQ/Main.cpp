#include "vld.h"
#include "Platform/Window.h"


int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	auto* window = Window::GetInstance();
	
	window->Initialize();
	window->Run();
	window->Finalize();

	return 0;
}
