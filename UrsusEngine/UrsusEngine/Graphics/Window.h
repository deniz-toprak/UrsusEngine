#pragma once
#include <string>
#include <memory>
#include "Sprite.h"
#include "Text.h"

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
		void Draw(std::shared_ptr<Sprite> sprite);
		void Draw(std::shared_ptr<Text> text);

	private:
		std::unique_ptr<sf::RenderWindow> m_Window;
	};
}