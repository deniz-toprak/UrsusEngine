#pragma once
#include <string>
#include <memory>


//forward declare sfml render window class
namespace sf
{
	class RenderWindow;
	class Sprite;
	class Text;
	class Texture;
	class VertexArray;
}

namespace UrsusEngine
{
	class Window
	{
	public:
		Window(const int width, const int height, const std::string title);
		~Window();

	public:
		bool Update();
		void BeginDraw();
		void EndDraw();
		void Draw(const std::shared_ptr<sf::Sprite>& sprite);
		void Draw(const std::shared_ptr<sf::Text>& text);
		void Draw(const sf::VertexArray* vertexArray, const std::shared_ptr<sf::Texture> texture);
		const std::shared_ptr<sf::RenderWindow>& GetWindow() { return m_Window; }

	private:
		std::shared_ptr<sf::RenderWindow> m_Window;
	};
}