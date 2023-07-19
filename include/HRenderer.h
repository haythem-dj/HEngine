#pragma once

#include <iostream>
#include <windows.h>

namespace HEngine
{
	class HRenderer
	{
	public:
		HRenderer();
		~HRenderer();

		void OnInit(int width, int height);
		void OnResize(int width, int height);

		void DrawPixels(HDC hdc, BITMAPINFO Bitmapinfo);
		void FillScreen(uint32_t color);
		void DrawRect(int x, int y, int w, int h, uint32_t color);

		uint32_t* GetPixels() const { return pixels; }

	private:
		uint32_t* pixels = nullptr;
		int Width = 0;
		int Height = 0;
	};
}