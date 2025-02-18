#include "application/application.h"
#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup")

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,		
	_In_opt_ HINSTANCE hPrevInstance,	
	_In_ LPWSTR    lpCmdLine,		
	_In_ int       nCmdShow)
{
	if (!app->initApplication(hInstance, 800, 600))
	{
		return -1;
	}


	while (true)
	{
		if (!app->peekMessage())
			break;
	}

	return 0;
}