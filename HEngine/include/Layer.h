#pragma once

namespace HEngine
{
	class Layer
	{
	public:
		~Layer() = default;
		virtual void OnResize(int width, int height) {}
		virtual void OnUpdate(float dt) {}
		virtual void OnRender() {}
	};
}