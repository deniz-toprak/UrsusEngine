#pragma once
#include <string>

//forward declare sfml render window class
namespace sf
{
	class RenderWindow;
}

namespace UrsusEngine
{
	class Window
	{
	public:
		Window(const int width, const int height, const std::string title, const bool fullscreen);
		~Window();

	public:
		bool Update();

	private:
		sf::RenderWindow* m_Window;
	};
}