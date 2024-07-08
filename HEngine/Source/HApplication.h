#pragma once

#include <vector>
#include <windows.h>

#include "HLayer.h"
#include "HEvent.h"
#include "HRenderer.h"

namespace HEngine
{
	class HApplication
	{
	public:
		HApplication();
		HApplication(const HApplication&) = delete;
		HApplication& operator= (const HApplication&) = delete;
		~HApplication();

		// static HApplication& Get();

		void PushLayer(HLayer* layer);

		void Resize(int width, int height);

		void Run();
		void ShutDown() { Running = false; }

		void SetViewportWidth(int width) { Resize(width, GetViewportHeight()); }
		void SetViewportHeight(int height) { Resize(GetViewportWidth(), height); }

		int GetViewportWidth() const { return ViewportWidth; }
		int GetViewportHeight() const { return ViewportHeight; } 

	private:
		void Init();
		void Clean();
		bool ProccessMessages();

	private:
		int ViewportWidth = 720;
		int ViewportHeight = 480;

		bool Running = false;

		std::vector<HLayer*> LayerStack;

		HINSTANCE hInstance;
		HWND hwnd;
		HDC hdc;
		BITMAPINFO Bitmapinfo;
	};

	HApplication* CreateApplication();
}
