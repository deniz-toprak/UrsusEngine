#include "SpriteComponent.h"
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

using namespace UrsusEngine::ECS;

SpriteComponent::SpriteComponent()
{
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::CreateSprite(std::string url)
{
	//Dereference pointer
	std::shared_ptr<sf::Texture>& texture = TextureManager::GetInstance().GetTexture(url);
	m_Sprite = std::make_shared<sf::Sprite>(*texture);
	
	m_Sprite->setOrigin(texture->getSize().x/2, texture->getSize().y/2);
}

void SpriteComponent::SetPosition(const float X, const float Y)
{
	m_Sprite->setPosition(X, Y);
}

void SpriteComponent::SetRotation(const float Rot)
{
	m_Sprite->setRotation(Rot);
}

void SpriteComponent::GetPosition(float& X, float& Y)
{
	X = m_Sprite->getPosition().x;
	Y = m_Sprite->getPosition().y;
}

void SpriteComponent::GetRotation(float& rotationInDegrees)
{
	rotationInDegrees = m_Sprite->getRotation();
}

const bool SpriteComponent::IsCollidingWith(std::shared_ptr<SpriteComponent> otherSprite)
{
	//Get SFML sprite for it's intersection methods
	const std::shared_ptr<sf::Sprite> sfmlSprite = otherSprite->GetSprite();
	//Get bounds of other sprite and this sprite
	sf::FloatRect otherRect = sfmlSprite->getGlobalBounds();
	sf::FloatRect thisRect = m_Sprite->getGlobalBounds();
	//does it intersect?
	return thisRect.intersects(otherRect);
}

const bool SpriteComponent::IsCollidingWith(const float left, const float top, const float width, const float height)
{
	sf::FloatRect otherRect(left, top, width, height);
	sf::FloatRect thisRect = m_Sprite->getGlobalBounds();
	return thisRect.intersects(otherRect);
}