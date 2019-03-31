#include "InputHelper.h"
#include <SFML/Graphics.hpp>
#include "engine.h"

using namespace UrsusEngine;

bool InputHelper::IsKeyPressed(Key key)
{
	return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}

bool InputHelper::IsMousePresse(MouseButton button)
{
	return sf::Mouse::isButtonPressed((sf::Mouse::Button)button);
}

void InputHelper::GetCurserPosition(const Engine* engine, float& X, float& Y)
{
	const std::shared_ptr<Window>& window = engine->GetWindow();
	const std::shared_ptr<sf::RenderWindow>& renderWindow = window->GetWindow();
	sf::Vector2i position = sf::Mouse::getPosition(*renderWindow);

	//make relative to view
	float viewX, viewY = 0.f;
	window->GetViewPosition(viewX, viewY);
	X = position.x + viewX;
	Y = position.y + viewY;
}

