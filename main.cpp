#include "application.h"
#include "gpu.h"
#include <cmath>
#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup")

Image* texture;
Point p1;
Point p2;
Point p3;

Point q1;
Point q2;
Point q3;

void render()
{
	sgl->clear();
	sgl->setTexture(texture);

	sgl->setBilinear(false);
	sgl->drawTriangle(p1, p2, p3);

	sgl->setBilinear(true);
	sgl->drawTriangle(q1, q2, q3);
}

void prepare()
{
	texture = Image::createImage("assets/textures/zhaohua.jpg");

	p1.x = 0;
	p1.y = 0;
	p1.color = RGBA(255, 0, 0, 255);
	p1.uv = math::vec2f(0.0f, 0.0f);

	p2.x = 200;
	p2.y = 599;
	p2.color = RGBA(0, 255, 0, 255);
	p2.uv = math::vec2f(0.5f, 1.0f);

	p3.x = 400;
	p3.y = 0;
	p3.color = RGBA(0, 0, 255, 255);
	p3.uv = math::vec2f(1.0f, 0.0f);

	q1.x = 400;
	q1.y = 0;
	q1.color = RGBA(255, 0, 0, 255);
	q1.uv = math::vec2f(0.0f, 0.0f);

	q2.x = 599;
	q2.y = 599;
	q2.color = RGBA(0, 255, 0, 255);
	q2.uv = math::vec2f(0.5f, 1.0f);

	q3.x = 799;
	q3.y = 0;
	q3.color = RGBA(0, 0, 255, 255);
	q3.uv = math::vec2f(1.0f, 0.0f);
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

	prepare();

	while (true)
	{
		if (!app->peekMessage())
			break;

		render();
		app->show();
	}

	return 0;
}