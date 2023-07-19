#include <chrono>

#include "HApplication.h"

static HEngine::HApplication* Instance = nullptr;

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
		HEngine::HApplication::Get().Resize(width, height);
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

namespace HEngine
{
	HApplication::HApplication(int width, int height)
	{
		ViewportWidth = width;
		ViewportHeight = height;
		Instance = this;
		Init();
	}

	HApplication::~HApplication()
	{
		Clean();
		Instance = nullptr;
	}

	HApplication& HApplication::Get()
	{
		return *Instance;
	}

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

		renderer.OnInit(ViewportWidth, ViewportHeight);

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

		renderer.OnResize(width, height);

		for(HLayer* layer : LayerStack)
			layer->OnResize(width, height);
	}

	void HApplication::Run()
	{
		float dt = 1.0f;

		while(Running)
		{
			int frameStart = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

			if(!ProccessMessages())
			{
				Running = false;
				continue;
			}

			for(HLayer* layer : LayerStack)
				layer->OnUpdate(dt);

			renderer.DrawPixels(hdc, Bitmapinfo);

			int frmaeEnd = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

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