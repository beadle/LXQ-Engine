#include <Windows.h>

#include "Math/Math.h"
#include "SimpleMath.h"
#include "d3dx11effect.h"

#include "Core/IObject.h"
#include "Core/IComponent.h"

#include "Core/Logger.h"

using namespace LXQ;

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	Logger::Initialize();

	LOGI << "ÎÒÊÇÐ¤ÏÄ";

	Logger::Finalize();

	system("Pause");
	return 0;
}
