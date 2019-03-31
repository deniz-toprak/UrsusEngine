#include "TextComponent.h"
#include <SFML/Graphics.hpp>

using namespace UrsusEngine::ECS;

TextComponent::TextComponent()
{


}

TextComponent::~TextComponent()
{

}

void TextComponent::CreateText(std::string filePath)
{
	//Initialize Font
	m_Font = std::make_unique<sf::Font>();
	//Load font from filepath parameter
	bool fileLoaded = m_Font->loadFromFile(filePath);
	// Possible optimization: FontManager

	//Initialize Text
	m_Text = std::make_shared<sf::Text>();
	//Reference of m_Font
	const sf::Font& font = *m_Font;
	//Set font
	m_Text->setFont(font);
	//can be written like
	//m_Text->setFont(*m_Font);
}

void TextComponent::SetPosition(const float X, const float Y)
{
	m_Text->setPosition(X, Y);
}

void TextComponent::GetPosition(float& X, float& Y)
{
	X = m_Text->getPosition().x;
	Y = m_Text->getPosition().y;
}

void TextComponent::SetColour(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	sf::Color col(red, green, blue);
	m_Text->setFillColor(col);
}

void TextComponent::SetColour(const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alpha)
{
	sf::Color col(red, green, blue, alpha);
	m_Text->setFillColor(col);
}

void TextComponent::SetSize(const int newSize)
{
	m_Text->setCharacterSize(newSize);
}

void TextComponent::SetText(const std::string newText)
{
	//set text
	m_Text->setString(newText);
}


