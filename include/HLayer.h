#pragma once

namespace HEngine
{
	class HLayer
	{
	public:
		~HLayer() = default;
		virtual void OnResize(int width, int height) {}
		virtual void OnUpdate(float dt) {}
	};
}