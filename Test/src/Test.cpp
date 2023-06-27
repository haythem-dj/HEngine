#include "HEngine.h"

class MainLayer : public HEngine::Layer
{
public:
	MainLayer()
	{
		Width = HEngine::Application::Get().GetViewportWidth();
		Height = HEngine::Application::Get().GetViewportHeight();
	}
	~MainLayer()
	{}

	void OnResize(int width, int height) override
	{
		Width = width;
		Height = height;
	}

	void OnUpdate(float dt) override
	{
		if(HEngine::Event::IsKeyDown(HEngine::KeyCode::ESCAPE))
			HEngine::Application::Get().ShutDown();
	}

	void OnRender() override
	{
		HEngine::Renderer renderer = HEngine::Application::Get().GetRenderer();
		renderer.DrawRect(100, 100, 100, 100, 0xff0000);
	}

private:
	int Width, Height;
};

HEngine::Application* CreateApplication()
{
	HEngine::Application* app = new HEngine::Application(720, 480);
	app->PushLayer(new MainLayer());
	return app;
}