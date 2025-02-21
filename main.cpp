#include "application.h"
#include "gpu.h"
#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup")

void render()
{
	sgl->clear();
	// for(uint32_t i = 0; i < app->getWidth(); ++i)
	// 	sgl->drawPoint(i, 200, RGBA(255, 255, 255));
	sgl->drawLine(0, 0, 200, 500, RGBA(255, 255, 255));
	sgl->drawLine(0, 0, 500, 200, RGBA(255, 255, 255));
}

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

	sgl->initSurface(800, 600, app->getCanvas());

	while (true)
	{
		if (!app->peekMessage())
			break;

		render();
		app->show();
	}

	return 0;
}