#include "Sprite.h"
#include <SFML/Graphics.hpp>

using namespace UrsusEngine;

Sprite::Sprite(std::shared_ptr<sf::Texture> texture)
{
	//Dereference pointer
	m_Sprite = std::make_shared<sf::Sprite>(*texture);
	sf::Vector2f origin = sf::Vector2f(texture->getSize().x /2, texture->getSize().y /2);
	m_Sprite->setOrigin(origin);
}

Sprite::~Sprite()
{
}

void Sprite::Move(const float X, const float Y)
{
	//use sfml internal methods to move sprite by X and Y
	m_Sprite->move(X, Y);
}

void Sprite::SetPosition(const float X, const float Y)
{
	m_Sprite->setPosition(X, Y);
}

void Sprite::SetRotation(const float Rot)
{
	m_Sprite->setRotation(Rot);
}

const bool Sprite::IsCollidingWith(std::shared_ptr<Sprite> otherSprite)
{
	//Get SFML sprite for it's intersection methods
	const std::shared_ptr<sf::Sprite> sfmlSprite = otherSprite->GetSprite();
	//Get bounds of other sprite and this sprite
	sf::FloatRect otherRect = sfmlSprite->getGlobalBounds();
	sf::FloatRect thisRect = m_Sprite->getGlobalBounds();
	//does it intersect?
	return thisRect.intersects(otherRect);
}

const bool Sprite::IsCollidingWith(const float left, const float top, const float width, const float height)
{
	sf::FloatRect otherRect(left, top, width, height);
	sf::FloatRect thisRect = m_Sprite->getGlobalBounds();
	return thisRect.intersects(otherRect);
}