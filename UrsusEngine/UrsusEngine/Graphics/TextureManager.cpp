#include "TextureManager.h"
#include <SFML/Graphics.hpp>

using namespace UrsusEngine;

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	for (auto& textureItr : m_Textures)
	{
		textureItr.second = nullptr;
	}
	m_Textures.clear();
}

std::shared_ptr<sf::Texture> TextureManager::GetTexture(std::string texturePath)
{
	if (m_Textures.find(texturePath) == m_Textures.end())
	{
		std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
		texture->loadFromFile(texturePath);
		m_Textures[texturePath] = texture;
		return texture;
	}
	return m_Textures.find(texturePath)->second;
}