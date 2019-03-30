#pragma once
#include <map>
#include <cstring>
#include <memory>

//forward declare needed sf classes
namespace sf
{
	class Texture;
}

namespace UrsusEngine
{
	class TextureManager
	{
	public:
		TextureManager();
		~TextureManager();

		static TextureManager& GetInstance()
		{
			static TextureManager _instance;
			return _instance;
		}

		TextureManager(const TextureManager&) = delete; //delete copy constructor
		TextureManager& operator=(const TextureManager&) = delete; // delete copy operator

	public:
		std::shared_ptr<sf::Texture>& GetTexture(std::string texturePath);

	private:
		std::map<std::string, std::shared_ptr<sf::Texture>> m_Textures;

	};
}