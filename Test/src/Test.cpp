#include "HEngine.h"

class MainLayer : public HEngine::Layer
{
public:
	MainLayer()
	{
		Width = HEngine::Application::Get().GetViewportWidth();
		Height = HEngine::Application::Get().GetViewportHeight();
		pixels = HEngine::Application::Get().GetRenderer().GetPixels();
	}

	~MainLayer()
	{
		delete pixels;
	}

	void OnResize(int width, int height) override
	{
		Width = width;
		Height = height;
		pixels = HEngine::Application::Get().GetRenderer().GetPixels();
	}

	void OnUpdate(float dt) override
	{
		for (int y = 0; y < Height; y++)
			for (int x = 0; x < Width; x++)
			{
				if ((y * Width + x) % 3 == 0) pixels[y * Width + x] = 0xff0000;
				else if ((y * Width + x) % 3 == 1) pixels[y * Width + x] = 0x00ff00;
				else pixels[y * Width + x] = 0x0000ff;
			}
	}

private:
	int Width, Height;
	uint32_t* pixels = nullptr;
};

HEngine::Application* CreateApplication()
{
	HEngine::Application* app = new HEngine::Application(480, 480);
	app->PushLayer(new MainLayer());
	return app;
}