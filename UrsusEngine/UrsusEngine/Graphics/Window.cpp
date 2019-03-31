#include "Window.h"
#include <SFML/Graphics.hpp>

using namespace UrsusEngine;

Window::Window(const int width, const int height, const std::string title)
{
	//Set up new mode
	//take over width and height params
	sf::VideoMode mode;
	mode.height = height;
	mode.width = width;
	int style = sf::Style::Default;
	//create instance of RenderWindow
	m_Window = std::make_shared<sf::RenderWindow>(mode, title, style);
}

Window::~Window()
{
}

bool Window::Update()
{
	sf::Event event;
	//Handle window events
	while (m_Window->pollEvent(event))
	{
		//close window if close event was send
		if (event.type == sf::Event::Closed)
		{
			//Return false, close window and close engine
			return false;
		}
	}
	//EndDraw();
	return true;
}

void Window::BeginDraw()
{
	//Clear window
	m_Window->clear(sf::Color::Black);
}

void Window::EndDraw()
{
	//Display everything
	m_Window->display();
}

void Window::Draw(const std::shared_ptr<sf::Sprite>& sprite)
{
	m_Window->draw(*sprite);
}

void Window::Draw(const std::shared_ptr<sf::Text>& text)
{
	m_Window->draw(*text);
}

void Window::Draw(const sf::VertexArray* vertexArray, const std::shared_ptr<sf::Texture> texture)
{
	m_Window->draw(*vertexArray, texture.get());
}