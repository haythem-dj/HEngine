#pragma once

#include "Application.h"

extern HEngine::Application* CreateApplication();

namespace HEngine
{
	static int Main(int argc, char** argv)
	{
		Application* app = CreateApplication();
		app->Run();
		delete app;
		return 0;
	}
}

int main(int argc, char** argv)
{
	return HEngine::Main(argc, argv);
}