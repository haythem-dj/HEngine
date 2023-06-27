#include "Event.h"

namespace HEngine
{
	int* Event::keys = new int[256] {0};

	bool Event::IsKeyDown(KeyCode key)
	{
		return keys[key];
	}

	bool Event::IsKeyUp(KeyCode key)
	{
		return !keys[key];
	}

	bool IsMouseButtonDown(MouseButton button)
	{

	}

	bool IsMouseButtonUp(MouseButton button)
	{

	}
}