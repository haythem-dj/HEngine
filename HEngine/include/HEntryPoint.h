#pragma once

#include "HApplication.h"

extern HEngine::HApplication* CreateApplication();

namespace HEngine
{
	static int Main(int argc, char** argv)
	{
		HApplication* app = CreateApplication();
		app->Run();
		delete app;
		return 0;
	}
}

int main(int argc, char** argv)
{
	return HEngine::Main(argc, argv);
}