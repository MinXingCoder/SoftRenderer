#pragma once
#include <Windows.h>
#include <stdint.h>

#define app Application::getInstance()

class Application
{
public:
	static Application* getInstance();

	bool initApplication(HINSTANCE hInstance, const uint32_t& width, const uint32_t& height);

	void handleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	bool peekMessage();

	void show();

	uint32_t getWidth() const;

	uint32_t getHeight() const;

	void* getCanvas() const;

private:
	BOOL createWindow(HINSTANCE hInstance);

	ATOM registerWindowClass(HINSTANCE hInstance);

private:
	static Application* mInstance;

	bool mAlive{ true };

	HINSTANCE mWindowInst;

	const WCHAR* mWindowClassName = L"MyApplication";

	HWND mHwnd;

	uint32_t mWidth{ 800 };

	uint32_t mHeight{ 600 };

	HDC mhDC;

	HDC mCanvasDC;

	HBITMAP mhBmp;

	void* mCanvasBuffer{ nullptr };
};