#pragma once
#include <map>
#include <cstring>

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
		sf::Texture* GetTexture(std::string texturePath);

	private:
		std::map<std::string, sf::Texture*> m_Textures;
	};
}