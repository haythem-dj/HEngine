#include "HApplication.h"

namespace
{
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch(uMsg)
		{
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_SIZE:
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);
			// HEngine::HApplication::Get().Resize(width, height);
			return 0;
		}

		case WM_KEYDOWN:
			HEngine::HEvent::keys[wParam] = 1;
			break;
	
		case WM_KEYUP:
			HEngine::HEvent::keys[wParam] = 0;
			break;
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

namespace HEngine
{
	HApplication::HApplication()
	{
		Init();
	}

	HApplication::~HApplication()
	{
		Clean();
	}

	// HApplication& HApplication::Get()
	// {
	// 	static HApplication instance;
	// 	return instance;
	// }

	void HApplication::Init()
	{
		const wchar_t* CLASS_NAME = L"class name";

		WNDCLASS wndClass = {};
		wndClass.lpszClassName = CLASS_NAME;
		wndClass.hInstance = hInstance;
		wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.lpfnWndProc = WindowProc;

		RegisterClass(&wndClass);

		DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_SYSMENU;

		RECT WindowRect, DesktopRect;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &DesktopRect);

		WindowRect.left = (DesktopRect.right - ViewportWidth) / 2;
		WindowRect.top = (DesktopRect.bottom - ViewportHeight) / 2;
		WindowRect.right = WindowRect.left + ViewportWidth;
		WindowRect.bottom = WindowRect.top + ViewportHeight;

		AdjustWindowRect(&WindowRect, style, false);

		hwnd = CreateWindowEx(
			0,
			CLASS_NAME,
			L"the window title",
			style,
			WindowRect.left,
			WindowRect.top,
			WindowRect.right - WindowRect.left,
			WindowRect.bottom - WindowRect.top,
			NULL,
			NULL,
			hInstance,
			NULL
		);

		ShowWindow(hwnd, SW_SHOW);

		Bitmapinfo.bmiHeader.biSize = sizeof(Bitmapinfo.bmiHeader);
		Bitmapinfo.bmiHeader.biWidth = ViewportWidth;
		Bitmapinfo.bmiHeader.biHeight = ViewportHeight;
		Bitmapinfo.bmiHeader.biPlanes = 1;
		Bitmapinfo.bmiHeader.biBitCount = 32;
		Bitmapinfo.bmiHeader.biCompression = BI_RGB;

		hdc = GetDC(hwnd);

		Running = true;
	}

	void HApplication::Clean()
	{
		const wchar_t* CLASS_NAME = L"class name";

		for(HLayer* layer : LayerStack)
			delete layer;

		UnregisterClass(CLASS_NAME, hInstance);
	}

	void HApplication::PushLayer(HLayer* layer)
	{
		LayerStack.emplace_back(layer);
	}

	void HApplication::Resize(int width, int height)
	{
		if(ViewportWidth == width && ViewportHeight == height)
			return;

		ViewportWidth = width;
		ViewportHeight = height;

		Bitmapinfo.bmiHeader.biWidth = ViewportWidth;
		Bitmapinfo.bmiHeader.biHeight = ViewportHeight;

		HRenderer::Get().OnResize(width, height);

		for(HLayer* layer : LayerStack)
			layer->OnResize(width, height);
	}

	void HApplication::Run()
	{
		float dt = 1.0f;

		while(Running)
		{
			ULONGLONG frameStart = GetTickCount64();

			if(!ProccessMessages())
			{
				Running = false;
				continue;
			}

			for(HLayer* layer : LayerStack)
				layer->OnUpdate(dt);

			StretchDIBits(hdc, 0, 0, ViewportWidth, ViewportHeight, 0, 0, ViewportWidth, ViewportHeight, (const void*) HRenderer::Get().GetPixels(), &Bitmapinfo, DIB_RGB_COLORS, SRCCOPY);

			ULONGLONG frameEnd = GetTickCount64();

			dt = (frameEnd - frameStart) / 1000.0f;
		}
	}

	bool HApplication::ProccessMessages()
	{
		MSG msg = {};

		while(PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				return false;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return true;
	}
}
