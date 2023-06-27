#pragma once

#include <vector>

#include "Layer.h"
#include "Event.h"
#include "Renderer.h"

namespace HEngine
{
	class Application
	{
	public:
		Application(int width, int height);
		Application(const Application&) = delete;
		Application operator= (const Application&) = delete;
		~Application();

		static Application& Get();

		void PushLayer(Layer* layer);

		void Resize(int width, int height);

		void Run();
		void ShutDown() { Running = false; }

		int GetViewportWidth() const { return ViewportWidth; }
		int GetViewportHeight() const { return ViewportHeight; } 
		const Renderer& GetRenderer() const { return renderer; }

	private:
		void Init();
		void Clean();
		bool ProccessMessages();

	private:
		int ViewportWidth = 0;
		int ViewportHeight = 0;

		bool Running = false;

		std::vector<Layer*> LayerStack;

		HINSTANCE hInstance;
		HWND hwnd;
		HDC hdc;
		BITMAPINFO Bitmapinfo;

		Renderer renderer;
	};
}