#include <HEngine.h>
#include <cstdint>

class MainLayer : public HEngine::HLayer
{
public:
	MainLayer()
	{

	}

	~MainLayer()
	{

	}

	void OnResize(int width, int height) override
	{

	}

	void OnUpdate(float dt) override
	{
		HEngine::HRenderer::Get().FillScreen(0x00000000);
		HEngine::HRenderer::Get().DrawRect(100, 100, 100, 100, 0xff0000ff);
	}

private:

};

class App : public HEngine::HApplication
{
public:
	App()
		: mRenderer(HEngine::HRenderer::Get())
	{
		SetViewportWidth(mWidth);
		SetViewportHeight(mHeight);
		mRenderer.OnInit(mWidth, mHeight);
		PushLayer(new MainLayer());
	}

	~App()
	{}

private:
	HEngine::HRenderer& mRenderer;
	uint32_t mWidth = 720;
	uint32_t mHeight = 480;

};

HEngine::HApplication* HEngine::CreateApplication()
{
	return new App();
}
