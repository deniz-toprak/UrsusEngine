#include "Text.h"
#include <SFML/Graphics.hpp>

using namespace UrsusEngine;

Text::Text(const std::string fontURL)
{
	m_Font = std::make_shared<sf::Font>();
	m_Font->loadFromFile(fontURL);
	m_Text = std::make_shared<sf::Text>();
	m_Text->setFont(*m_Font);
}

Text::~Text()
{
}

//Set text
void Text::SetText(const std::string text)
{
	m_Text->setString(text);
}

//Set character size
void Text::SetSize(const int size)
{
	m_Text->setCharacterSize(size);
}

//Set colour - and yes it is COLOUR NOT COLOR. 
//Learn british english ffs
//@TO-DO: Make new data type Colour which consists of rbga
void Text::SetColour(const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alpha)
{
	sf::Color colour(red, green, blue, alpha);
	m_Text->setFillColor(colour);
}

//Set Text position
void Text::SetPosition(const float X, const float Y)
{
	m_Text->setPosition(X, Y);
}