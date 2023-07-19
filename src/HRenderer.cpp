#include "HRenderer.h"

namespace HEngine
{
	HRenderer::HRenderer()
	{}

	HRenderer::~HRenderer()
	{
		delete pixels;
	}

	void HRenderer::OnInit(int width , int height)
	{
		Width = width;
		Height = height;
		pixels = new uint32_t[Width*Height] {0};
	}

	void HRenderer::OnResize(int width, int height)
	{
		Width = width;
		Height = height;
		delete pixels;
		pixels = new uint32_t[Width*Height];
	}

	void HRenderer::DrawPixels(HDC hdc, BITMAPINFO Bitmapinfo)
	{
		StretchDIBits(hdc, 0, 0, Width, Height, 0, 0, Width, Height, (const void*)pixels, &Bitmapinfo, DIB_RGB_COLORS, SRCCOPY);
	}

	void HRenderer::FillScreen(uint32_t color)
	{
		for (int i = 0; i < Width*Height; i++)
			pixels[i] = color;
	}

	void HRenderer::DrawRect(int x, int y, int w, int h, uint32_t color)
	{
		for (int i = x; i < x + w; i++)
			for (int j = y; j < y + h; j++)
				pixels[Width * j + i] = color;
	}
}