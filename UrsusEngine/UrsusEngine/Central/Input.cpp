#include "Input.h"
#include <SFML/Window.hpp>

using namespace UrsusEngine;

Input::Input()
{

}

Input::~Input()
{

}

bool Input::IsKeyPressed(Key key)
{
	return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}


