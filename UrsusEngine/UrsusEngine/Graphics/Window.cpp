#include "Window.h"
#include <SFML/Graphics.hpp>

using namespace UrsusEngine;

Window::Window(const int width, const int height, const std::string title, const bool fullscreen)
{
	//Set up new mode
	//take over width and height params
	sf::VideoMode mode;
	mode.height = height;
	mode.width = width;
	//Ternary operator for fullscreen
	int style = fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
	//create instance of RenderWindow
	m_Window = new sf::RenderWindow(mode, title, style);
}

Window::~Window()
{
	delete m_Window;
}

bool Window::Update()
{
	//BeginDraw();

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

void Window::Draw(Sprite* sprite)
{
	m_Window->draw(*sprite->GetSprite());
}

