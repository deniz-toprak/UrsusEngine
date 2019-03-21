#pragma once
#include <string>
#include "Sprite.h"

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
		void BeginDraw();
		void EndDraw();
		void Draw(Sprite* sprite);

	private:
		sf::RenderWindow* m_Window;
	};
}