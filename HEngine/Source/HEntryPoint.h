#pragma once

#include "HApplication.h"

extern HEngine::HApplication* HEngine::CreateApplication();

int main()
{
	HEngine::HApplication* app = HEngine::CreateApplication();
	app->Run();
	delete app;
}