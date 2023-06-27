#include "Application.h"

static HEngine::Application* Instance = nullptr;

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
		HEngine::Application::Get().Resize(width, height);
		return 0;
	}

	case WM_KEYDOWN:
		HEngine::Event::keys[wParam] = 1;
		break;

	case WM_KEYUP:
		HEngine::Event::keys[wParam] = 0;
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

namespace HEngine
{
	Application::Application(int width, int height)
	{
		ViewportWidth = width;
		ViewportHeight = height;
		Instance = this;
		Init();
	}

	Application::~Application()
	{
		Clean();
		Instance = nullptr;
	}

	Application& Application::Get()
	{
		return *Instance;
	}

	void Application::Init()
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
		Bitmapinfo.bmiHeader.biHeight = -ViewportHeight;
		Bitmapinfo.bmiHeader.biPlanes = 1;
		Bitmapinfo.bmiHeader.biBitCount = 32;
		Bitmapinfo.bmiHeader.biCompression = BI_RGB;

		hdc = GetDC(hwnd);

		renderer.OnInit(ViewportWidth, ViewportHeight);

		Running = true;
	}

	void Application::Clean()
	{
		const wchar_t* CLASS_NAME = L"class name";

		for(Layer* layer : LayerStack)
			delete layer;

		UnregisterClass(CLASS_NAME, hInstance);
	}

	void Application::PushLayer(Layer* layer)
	{
		LayerStack.emplace_back(layer);
	}

	void Application::Resize(int width, int height)
	{
		if(ViewportWidth == width && ViewportHeight == height)
			return;

		ViewportWidth = width;
		ViewportHeight = height;

		Bitmapinfo.bmiHeader.biWidth = ViewportWidth;
		Bitmapinfo.bmiHeader.biHeight = -ViewportHeight;

		renderer.OnResize(width, height);

		for(Layer* layer : LayerStack)
			layer->OnResize(width, height);
	}

	void Application::Run()
	{
		while(Running)
		{
			if(!ProccessMessages())
			{
				Running = false;
				continue;
			}

			for(Layer* layer : LayerStack)
			{
				layer->OnUpdate(1.0f);
				layer->OnRender();
			}

			renderer.DrawPixels(hdc, Bitmapinfo);
		}
	}

	bool Application::ProccessMessages()
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