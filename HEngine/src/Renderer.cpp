#include "Renderer.h"

namespace HEngine
{
	Renderer::Renderer()
	{}

	Renderer::~Renderer()
	{
		delete pixels;
	}

	void Renderer::OnInit(int width , int height)
	{
		Width = width;
		Height = height;
		pixels = new uint32_t[Width*Height] {0};
	}

	void Renderer::OnResize(int width, int height)
	{
		Width = width;
		Height = height;
		delete pixels;
		pixels = new uint32_t[Width*Height];
	}

	void Renderer::DrawPixels(HDC hdc, BITMAPINFO Bitmapinfo)
	{
		StretchDIBits(hdc, 0, 0, Width, Height, 0, 0, Width, Height, (const void*)pixels, &Bitmapinfo, DIB_RGB_COLORS, SRCCOPY);
	}

	void Renderer::DrawRect(int x, int y, int w, int h, uint32_t color)
	{
		for (int i = x; i < x + w; i++)
			for (int j = y; j < y + h; j++)
				pixels[Width * j + i] = color;
	}
}