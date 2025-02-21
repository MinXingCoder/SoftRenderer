#include "application.h"
#include "base.h"
#include <windef.h>

LRESULT CALLBACK Wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	app->handleMessage(hWnd, message, wParam, lParam);
	return (DefWindowProc(hWnd, message, wParam, lParam));
}

Application* Application::getInstance()
{
	if (mInstance == nullptr)
	{
		static Application application;
		mInstance = &application;
	}

	return mInstance;
}

Application* Application::mInstance = nullptr;

bool Application::initApplication(HINSTANCE hInstance, const uint32_t& width, const uint32_t& height)
{
	mWidth = width;
	mHeight = height;

	// 0 ��ʾ error
	if (0 == registerWindowClass(hInstance))
		return false;

	if (!createWindow(hInstance))
		return false;

	mhDC = GetDC(mHwnd);

	mCanvasDC = CreateCompatibleDC(mhDC);

	BITMAPINFO bmpInfo{};
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = mWidth;
	bmpInfo.bmiHeader.biHeight = mHeight;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;

	mhBmp = CreateDIBSection(
		mCanvasDC,
		&bmpInfo,
		DIB_RGB_COLORS,
		(void**)&mCanvasBuffer,
		0, 0);

	SelectObject(mCanvasDC, mhBmp);

	memset(mCanvasBuffer, 0, mWidth * mHeight * sizeof(RGBA));

	return true;
}

BOOL Application::createWindow(HINSTANCE hInstance)
{
	mWindowInst = hInstance;

	auto dwExStyle = WS_EX_APPWINDOW;
	auto dwStyle =
		WS_OVERLAPPEDWINDOW |
		WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN;

	RECT windowRect;
	windowRect.left = 0L;
	windowRect.top = 0L;
	windowRect.right = (long)mWidth;
	windowRect.bottom = (long)mHeight;

	AdjustWindowRectEx(
		&windowRect,
		dwStyle,
		FALSE,
		dwExStyle
	);

	mHwnd = CreateWindowW(
		mWindowClassName,
		(LPCWSTR)"GraphicLearning",
		dwStyle,
		500, 500,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	if (mHwnd == NULL) return FALSE;

	ShowWindow(mHwnd, true);
	UpdateWindow(mHwnd);

	return TRUE;
}

void Application::handleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CLOSE: {
			DestroyWindow(hWnd);
			break;
		}
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			mAlive = false;
			break;
		}
	}
}

ATOM Application::registerWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wndClass;

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = Wndproc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = mWindowClassName;
	wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	return RegisterClassExW(&wndClass);
}

bool Application::peekMessage()
{
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return mAlive;
}

void Application::show()
{
	BitBlt(mhDC, 0, 0, mWidth, mHeight, mCanvasDC, 0, 0, SRCCOPY);
}

uint32_t Application::getWidth() const
{
	return mWidth;
}

uint32_t Application::getHeight() const
{
	return mHeight;
}

void* Application::getCanvas() const
{
	return reinterpret_cast<void*>(mCanvasBuffer);
}