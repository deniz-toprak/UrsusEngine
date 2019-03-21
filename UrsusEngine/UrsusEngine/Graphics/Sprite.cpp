#include "Sprite.h"
#include <SFML/Graphics.hpp>

using namespace UrsusEngine;

Sprite::Sprite(const char* url)
{
	m_Texture = new sf::Texture();
	m_Texture->loadFromFile(url);
	//dereference the pointer
	m_Sprite = new sf::Sprite(*m_Texture);
}

Sprite::~Sprite()
{
	delete m_Sprite;
	delete m_Texture;
}

void Sprite::Move(const float X, const float Y)
{
	//use sfml internal methods to move sprite by X and Y
	m_Sprite->move(X, Y);
}