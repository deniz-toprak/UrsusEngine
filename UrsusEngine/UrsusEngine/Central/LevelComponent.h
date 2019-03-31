#pragma once
#include "../Patterns/ECS/IComponent.h"
#include <string>
#include <vector>

namespace sf
{
	class Texture;
}

struct Tile
{
	float X;
	float Y;
	int textureX;
	int textureY;
	bool IsCollidable;
};

namespace UrsusEngine
{
	class LevelComponent : public UrsusEngine::ECS::IComponent
	{
	public:
		LevelComponent();
		~LevelComponent();

	public:
		void CreateTileset(std::string url, int tileWidth, int tileHeight);
		void SetLevel(std::vector<Tile>& tiles, int width, int height);

		const Tile& GetTileSprite(const unsigned int index) const;
		const std::shared_ptr<sf::Texture>& GetTileSetTexture() { return m_TileSet; }

		const std::string GetTextureUrl() { return m_TextureUrl; }
		const unsigned int GetTotalTileAmount() { return m_Width * m_Height; }
		const void GetTileSize(unsigned int& tileWidth, unsigned int& tileHeight)
		{
			tileWidth = m_TileWidth;
			tileHeight = m_TileHeight;
		}

		const bool IsWalkable(const float left, const float top, const float width, const float height);

	private:
		const Tile& GetTile(const float X, const float Y) const;

	private:
		std::vector<Tile> m_Tiles;
		std::string m_TextureUrl = "";
		std::shared_ptr<sf::Texture> m_TileSet;
		unsigned int m_Width = 0;
		unsigned int m_Height = 0;
		unsigned int m_TileWidth = 0;
		unsigned int m_TileHeight = 0;
	};
}