#include "application.h"
#include "gpu.h"
#include <cmath>
#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup")
Image* img = Image::createImage(".\\assets\\textures\\zhaohua.jpg");
void render()
{
	sgl->clear();

	//int r = 150;
	//Point c{ 400, 300, RGBA(255, 0, 0, 255) };
	//for (float i = 0; i < 360; i += 10)
	//{
	//	float radian = DEG2RAD(i);
	//	int x = r * std::sin(radian) + c.x;
	//	int y = r * std::cos(radian) + c.y;

	//	Point pt{ x, y, RGBA(std::rand() % 255, std::rand() % 255, std::rand() % 255, 255) };

	//	sgl->drawLine(c, pt);
	//}

	//Point p1{ 0, 100, RGBA(255, 0, 0, 255) };
	//Point p2{ 500, 100, RGBA(0, 255, 0, 255) };
	//Point p3{ 250, 500, RGBA(0, 0, 255, 255) };

	//sgl->drawTriangle(p1, p2, p3);
	
	sgl->drawImage(img);
	//Image::destroy(img);
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