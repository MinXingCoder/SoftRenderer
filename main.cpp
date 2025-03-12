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

float speed = 0.01f;
void changeUV()
{
	p1.uv.x += speed;
	p2.uv.x += speed;
	p3.uv.x += speed;
	q1.uv.x += speed;
	q2.uv.x += speed;
	q3.uv.x += speed;
}

void TestLine0()
{
	Point p1{ 100, 100, RGBA(255, 0, 0, 255) };
	Point p2{ 500, 599, RGBA(0, 255, 0, 255) };

	sgl->drawLine(p1, p2);
}

void TestLine1()
{
	int r = 150;
	Point c{ 400, 300, RGBA(255, 0, 0, 255) };

	for (float i = 0; i < 360; i += 10)
	{
		float radian = DEG2RAD(i);
		int x = r * std::sin(radian) + c.x;
		int y = r * std::cos(radian) + c.y;

		Point pt{ x, y, RGBA(rand() % 255, rand() % 255, rand() % 255, 255) };
		sgl->drawLine(c, pt);
	}
}

void TestTriangle()
{
	Point p1{ 0, 100, RGBA(255, 0, 0, 255) };
	Point p2{ 500, 100, RGBA(0, 255, 0, 255) };
	Point p3{ 250, 500, RGBA(0, 0, 255, 255) };

	sgl->drawTriangle(p1, p2, p3);
}

void TestUV0()
{
	sgl->setTexture(texture);
	sgl->drawTriangle(p1, p2, p3);
}

void TestUV1()
{
	sgl->setTexture(texture);
	sgl->setBilinear(false);
	sgl->drawTriangle(p1, p2, p3);

	sgl->setBilinear(true);
	sgl->drawTriangle(q1, q2, q3);
}

void TestWrap()
{
	sgl->setTexture(texture);
	sgl->setTextureWrap(TEXTURE_WRAP_MIRROR);

	sgl->drawTriangle(p1, p2, p3);
	sgl->drawTriangle(q1, q2, q3);
}

void render()
{
	sgl->clear();

	// TestLine0();
	// TestLine1();
	// TestTriangle();
	// TestUV0();
	// TestUV1();

	changeUV();
	TestWrap();
}

void prepare0()
{
	texture = Image::createImage("assets/textures/zhaohua.jpg");

	p1.x = 0;
	p1.y = 0;
	p1.color = RGBA(255, 0, 0, 255);
	p1.uv = math::vec2f(0.0f, 0.0f);

	p2.x = 400;
	p2.y = 599;
	p2.color = RGBA(0, 255, 0, 255);
	p2.uv = math::vec2f(0.5f, 1.0f);

	p3.x = 799;
	p3.y = 0;
	p3.color = RGBA(0, 0, 255, 255);
	p3.uv = math::vec2f(1.0f, 0.0f);
}

void prepare1()
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

	q2.x = 600;
	q2.y = 599;
	q2.color = RGBA(0, 255, 0, 255);
	q2.uv = math::vec2f(0.5f, 1.0f);

	q3.x = 799;
	q3.y = 0;
	q3.color = RGBA(0, 0, 255, 255);
	q3.uv = math::vec2f(1.0f, 0.0f);
}

void prepare2()
{
	texture = Image::createImage("assets/textures/zhaohua.jpg");

	p1.x = 0;
	p1.y = 0;
	p1.color = RGBA(255, 0, 0, 255);
	p1.uv = math::vec2f(0.0f, 0.0f);

	p2.x = 400;
	p2.y = 300;
	p2.color = RGBA(0, 255, 0, 255);
	p2.uv = math::vec2f(1.0f, 1.0f);

	p3.x = 400;
	p3.y = 0;
	p3.color = RGBA(0, 0, 255, 255);
	p3.uv = math::vec2f(1.0f, 0.0f);

	q1.x = 0;
	q1.y = 0;
	q1.color = RGBA(255, 0, 0, 255);
	q1.uv = math::vec2f(0.0f, 0.0f);

	q2.x = 0;
	q2.y = 300;
	q2.color = RGBA(0, 255, 0, 255);
	q2.uv = math::vec2f(0.0f, 1.0f);

	q3.x = 400;
	q3.y = 300;
	q3.color = RGBA(0, 0, 255, 255);
	q3.uv = math::vec2f(1.0f, 1.0f);
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

	// prepare0();
	// prepare1();
	prepare2();

	while (true)
	{
		if (!app->peekMessage())
			break;

		render();
		app->show();
	}

	return 0;
}