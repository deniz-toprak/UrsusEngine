#include "InputHelper.h"
#include <SFML/Window.hpp>

using namespace UrsusEngine;

bool InputHelper::IsKeyPressed(Key key)
{
	return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}


