#pragma once

#include <iostream>
#include <windows.h>

namespace HEngine
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void OnInit(int width, int height);
		void OnResize(int width, int height);

		void DrawPixels(HDC hdc, BITMAPINFO Bitmapinfo);
		void DrawRect(int x, int y, int w, int h, uint32_t color);

	private:
		uint32_t* pixels = nullptr;
		int Width = 0;
		int Height = 0;
	};
}