#include "HRenderer.h"

namespace HEngine
{
	HRenderer::HRenderer()
	{}

	HRenderer::~HRenderer()
	{
		delete[] pixels;
	}

	HRenderer& HRenderer::Get()
	{
		static HRenderer instance;
		return instance;
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
		delete[] pixels;
		pixels = new uint32_t[Width*Height];
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
