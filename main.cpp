#include "application/application.h"
#include "gpu/gpu.h"
#include <cmath>
#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup")

uint32_t WIDTH = 800;
uint32_t HEIGHT = 600;

Image* texture;
Point p1;
Point p2;
Point p3;

Point q1;
Point q2;
Point q3;

math::vec4f pos1;
math::vec4f pos2;
math::vec4f pos3;

math::mat4f modelMatrix;
math::mat4f viewMatrix;
math::mat4f perspectiveMatrix;
math::mat4f screenMatrix;

float angle = 0.0f;
float cameraPos = 5.0f;
void transform()
{
	angle += 0.01f;
	cameraPos += 0.01f;

	modelMatrix = math::rotate(math::mat4f(1.0f), angle, math::vec3f{ 0.0f, 1.0f, 0.0f });

	// modelMatrix.printMatrix();

	auto cameraModelMatrix = math::translate(math::mat4f(1.0f), math::vec3f{ 0.0f, 0.0f, cameraPos });
	viewMatrix = math::inverse(cameraModelMatrix);

	// viewMatrix.printMatrix();

	// mvp
	auto sp1 = perspectiveMatrix * viewMatrix * modelMatrix * pos1;
	auto sp2 = perspectiveMatrix * viewMatrix * modelMatrix * pos2;
	auto sp3 = perspectiveMatrix * viewMatrix * modelMatrix * pos3;

	sp1 /= sp1.w;
	sp2 /= sp2.w;
	sp3 /= sp3.w;

	sp1 = screenMatrix * sp1;
	sp2 = screenMatrix * sp2;
	sp3 = screenMatrix * sp3;

	p1.x = sp1.x; p1.y = sp1.y;

	p2.x = sp2.x; p2.y = sp2.y;

	p3.x = sp3.x; p3.y = sp3.y;
}

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

// 画一条直线, (100, 100) 到 (500, 599)，从红色到绿色
void TestLine0()
{
	Point p0{ 100, 100, RGBA(255, 0, 0, 255) };
	Point p1{ 500, 599, RGBA(0, 255, 0, 255) };
	sgl->drawLine(p0, p1);
}

// 以 (400, 300) 红色点为原点, 半径 150，每隔 10 度画一条线
void TestLine1()
{
	int radius = 150;
	Point origin{ 400, 300, RGBA(255, 0, 0, 255) };

	for (float i = 0; i < 360; i += 10)
	{
		float x = radius * std::cos(DEG2RAD(i)) + origin.x;
		float y = radius * std::sin(DEG2RAD(i)) + origin.y;

		Point pt{ x, y, RGBA(rand() % 255, rand() % 255, rand() % 255, 255) };

		sgl->drawLine(origin, pt);
	}
}

// 画出 (0, 100) 红，(500, 100) 绿，(250, 500) 蓝 三角形
void TestTriangle()
{
	Point p0{ 0, 100, RGBA(255, 0, 0, 255) };
	Point p1{ 500, 100, RGBA(0, 255, 0, 255) };
	Point p2{ 250, 500, RGBA(0, 0, 255, 255) };

	sgl->drawTriangle(p0, p1, p2);
}

Image* image01 = Image::createImage("assets/textures/zhaohua.jpg");
Image* image02 = Image::createImage("assets/textures/house.jpg");

// 设置 blend
void TestImage()
{
	sgl->setBlending(true);

	sgl->drawImage(image02);
	sgl->drawImageWithAlpha(image01, 100);
}

void ReleaseImage()
{
	Image::destroy(image01);
	Image::destroy(image02);
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
	changeUV();

	sgl->setTexture(texture);
	sgl->setTextureWrap(TEXTURE_WRAP_MIRROR);

	sgl->drawTriangle(p1, p2, p3);
	sgl->drawTriangle(q1, q2, q3);
}

void render()
{
	// transform();

	sgl->clear();

	// TestLine0();
	// TestLine1();
	// TestTriangle();
	// TestImage();
	// TestUV0();
	TestUV1();

	//changeUV();
	// TestWrap();

	// sgl->drawTriangle(p1, p2, p3);
}

// 三个点 (0, 0), (400, 599), (799, 0) 对应 uv (0.0f, 0.0f), (0.5f, 1.0f), (1.0f, 0.0f)
void prepare0()
{
	texture = Image::createImage("assets/textures/zhaohua.jpg");

	p1.x = 0; p1.y = 0; p1.color = RGBA(255, 0, 0, 255);
	p2.x = 400; p2.y = 599; p2.color = RGBA(0, 255, 0, 255);
	p3.x = 799; p3.y = 0; p3.color = RGBA(0, 0, 255, 255);

	p1.uv = math::vec2f(0.0f, 0.0f);
	p2.uv = math::vec2f(0.5f, 1.0f);
	p3.uv = math::vec2f(1.0f, 0.0f);
}

/*
* 点 (0, 0), (200, 599), (400, 0)，uv (0.0f, 0.0f), (0.5f, 1.0f), (1.0f, 0.0f)，关闭双线性插值
* 点 (400, 0), (600, 599), (799, 0)，uv (0.0f, 0.0f), (0.5f, 1.0f), (1.0f, 0.0f)，开启双线性插值
*/
void prepare1()
{
	texture = Image::createImage("assets/textures/zhaohua.jpg");

	p1.x = 0; p1.y = 0; p1.color = RGBA(255, 0, 0, 255); p1.uv = math::vec2f(0.0f, 0.0f);
	p2.x = 200; p2.y = 599; p2.color = RGBA(0, 255, 0, 255); p2.uv = math::vec2f(0.5f, 1.0f);
	p3.x = 400; p3.y = 0; p3.color = RGBA(0, 0, 255, 255); p3.uv = math::vec2f(1.0f, 0.0f);

	q1.x = 400; q1.y = 0; q1.color = RGBA(255, 0, 0, 255); q1.uv = math::vec2f(0.0f, 0.0f);
	q2.x = 600; q2.y = 599; q2.color = RGBA(0, 255, 0, 255); q2.uv = math::vec2f(0.5f, 1.0f);
	q3.x = 799; q3.y = 0; q3.color = RGBA(0, 0, 255, 255); q3.uv = math::vec2f(1.0f, 0.0f);
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

void prepare3()
{
	texture = Image::createImage("assets/textures/zhaohua.jpg");

	p1.color = RGBA(255, 0, 0, 255);
	p1.uv = math::vec2f(0.0f, 0.0f);

	p2.color = RGBA(0, 255, 0, 255);
	p2.uv = math::vec2f(1.0f, 1.0f);

	p3.color = RGBA(0, 0, 255, 255);
	p3.uv = math::vec2f(1.0f, 0.0f);

	pos1 = { -1.5f, 0.0f, 0.0f, 1.0f };
	pos2 = { 1.5f, 0.0f, 0.0f, 1.0f };
	pos3 = { 0.0f, 2.0f, 0.0f, 1.0f };

	perspectiveMatrix = math::perspective(60.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	screenMatrix = math::screenMatrix<float>(WIDTH, HEIGHT);

	//perspectiveMatrix.printMatrix();
	//screenMatrix.printMatrix();
}

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,		
	_In_opt_ HINSTANCE hPrevInstance,	
	_In_ LPWSTR    lpCmdLine,		
	_In_ int       nCmdShow)
{
	if (!winApp->initApplication(hInstance, 800, 600))
	{
		return -1;
	}

	sgl->initSurface(800, 600, winApp->getCanvas());

	// prepare0();
	prepare1();
	// prepare2();
	// prepare3();

	while (true)
	{
		if (!winApp->peekMessage())
			break;

		render();
		winApp->show();
	}

	// ReleaseImage();
	Image::destroy(texture);

	return 0;
}