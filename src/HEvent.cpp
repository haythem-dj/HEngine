#include "HEvent.h"

namespace HEngine
{
	int* HEvent::keys = new int[256] {0};

	bool HEvent::IsKeyDown(KeyCode key)
	{
		return keys[key];
	}

	bool HEvent::IsKeyUp(KeyCode key)
	{
		return !keys[key];
	}

	bool HEvent::IsMouseButtonDown(MouseButton button)
	{

	}

	bool HEvent::IsMouseButtonUp(MouseButton button)
	{

	}
}