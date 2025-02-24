#include "application.h"
#include "gpu.h"
#include <cmath>
#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup")

void render()
{
	sgl->clear();

	int r = 150;
	Point c{ 400, 300, RGBA(255, 0, 0, 255) };
	for (float i = 0; i < 360; i += 10)
	{
		float radian = DEG2RAD(i);
		int x = r * std::sin(radian) + c.x;
		int y = r * std::cos(radian) + c.y;

		Point pt{ x, y, RGBA(std::rand() % 255, std::rand() % 255, std::rand() % 255, 255) };

		sgl->drawLine(c, pt);
	}
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