#pragma once

#include <vector>

#include "HLayer.h"
#include "HEvent.h"
#include "HRenderer.h"

namespace HEngine
{
	class HApplication
	{
	public:
		HApplication(int width, int height);
		HApplication(const HApplication&) = delete;
		HApplication operator= (const HApplication&) = delete;
		~HApplication();

		static HApplication& Get();

		void PushLayer(HLayer* layer);

		void Resize(int width, int height);

		void Run();
		void ShutDown() { Running = false; }

		int GetViewportWidth() const { return ViewportWidth; }
		int GetViewportHeight() const { return ViewportHeight; } 
		const HRenderer& GetRenderer() const { return renderer; }

	private:
		void Init();
		void Clean();
		bool ProccessMessages();

	private:
		int ViewportWidth = 0;
		int ViewportHeight = 0;

		bool Running = false;

		std::vector<HLayer*> LayerStack;

		HINSTANCE hInstance;
		HWND hwnd;
		HDC hdc;
		BITMAPINFO Bitmapinfo;

		HRenderer renderer;
	};
}