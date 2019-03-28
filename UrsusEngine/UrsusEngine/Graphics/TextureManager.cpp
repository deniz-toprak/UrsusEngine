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
		delete textureItr.second;
	}
	m_Textures.clear();
}

sf::Texture* TextureManager::GetTexture(std::string texturePath)
{
	if (m_Textures.find(texturePath) == m_Textures.end())
	{
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile(texturePath);
		m_Textures[texturePath] = texture;
		return texture;
	}
	return m_Textures.find(texturePath)->second;
}