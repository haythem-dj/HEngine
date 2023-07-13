#pragma once

namespace HEngine
{
	enum KeyCode
	{
		TAB = 9, ENTER = 13, SHIFT = 16, CTRL, ALT, ESCAPE = 27, SPACE = 32, LEFT = 37, UP, RIGHT, DOWN,
		A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
	};

	enum MouseButton
	{

	};

	class Event
	{
	public:
		static bool IsKeyDown(KeyCode key);
		static bool IsKeyUp(KeyCode key);

		static bool IsMouseButtonDown(MouseButton button);
		static bool IsMouseButtonUp(MouseButton button);

		static int* keys;
	};
}