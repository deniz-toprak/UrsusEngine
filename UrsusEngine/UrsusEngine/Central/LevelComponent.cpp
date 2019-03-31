#include "LevelComponent.h"
#include "../Graphics/TextureManager.h"
#include "EngineAssert.h"

using namespace UrsusEngine;

LevelComponent::LevelComponent()
{

}

LevelComponent::~LevelComponent()
{

}

void LevelComponent::CreateTileset(std::string url, int tileWidth, int tileHeight)
{

	TextureManager::GetInstance().GetTexture(url); // cache
	m_TextureUrl = url;
	m_TileWidth = tileWidth;
	m_TileHeight = tileHeight;
}

void LevelComponent::SetLevel(std::vector<Tile>& tiles, int width, int height)
{
	m_Tiles = tiles;
	m_Width = width;
	m_Height = height;
}

const Tile& LevelComponent::GetTileSprite(const unsigned int index) const
{
	assert(m_Tiles.size() >= index);
	return m_Tiles[index];
}

const bool LevelComponent::IsWalkable(const float left, const float top, const float width, const float height)
{
	int centerOffsetX = width / 2;
	int centerOffsetY = height / 2;
	const Tile& leftTopTile = GetTile(left - centerOffsetX, top - centerOffsetY);
	if (leftTopTile.IsCollidable) return false;
	const Tile& rightTopTile = GetTile(left + centerOffsetX, top - centerOffsetY);
	if (rightTopTile.IsCollidable) return false;
	const Tile& leftBottomTile = GetTile(left - centerOffsetX, top + centerOffsetY);
	if (leftBottomTile.IsCollidable) return false;
	const Tile& rightBottomTile = GetTile(left + centerOffsetX, top - centerOffsetY);
	if (rightBottomTile.IsCollidable) return false;

	return true;
}


const Tile& LevelComponent::GetTile(const float X, const float Y) const
{
	int tileX = (int)std::floor(X / (float)m_TileWidth);
	int tileY = (int)std::floor(Y / (float)m_TileHeight);
	//if the calclulated coordinates are bigger than the level, we cap them at the level sizes
	if (m_Width < tileX)
	{
		tileX = m_Width - 1;
	}
	if (m_Height < tileY)
	{
		tileY = m_Height - 1;
	}
	//calculate the index based on the x and y position of one tile
	int index = tileX + (tileY * m_Width);
	//return the tile at this position
	assert(m_Tiles.size() >= index);
	return m_Tiles[index];
}
