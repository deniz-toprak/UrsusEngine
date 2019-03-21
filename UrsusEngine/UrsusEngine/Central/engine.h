#pragma once

#include <string>
#include "../Graphics/Window.h"

namespace UrsusEngine
{
	class Engine
	{
	public:
		Engine(const int width, const int height, const std::string title, const bool fullscreen);
		~Engine();

	public:
		const bool IsRunning() const { return m_IsRunning; }
		void Update();

	private:
		bool m_IsRunning;
		Window* m_Window;
	};
}
