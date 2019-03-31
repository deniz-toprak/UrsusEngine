#include "RenderSystem.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "../Central/LevelComponent.h"
#include <SFML/Graphics.hpp>
#include "../Central/EngineAssert.h"
#include "TextureManager.h"


using namespace UrsusEngine::ECS;

RenderSystem::RenderSystem()
{

}

RenderSystem::~RenderSystem()
{

}

bool RenderSystem::DoesEntityMatch(std::shared_ptr<Entity> entity)
{
	if (entity->HasComponent<SpriteComponent>()
		|| entity->HasComponent<TextComponent>()
		|| entity->HasComponent<LevelComponent>())
	{
		return true;
	}
	return false;
}

void RenderSystem::Draw(std::shared_ptr<UrsusEngine::Window> window)
{
	std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>> copiedEntities = m_Entities;
	for (std::shared_ptr<Entity> entity : copiedEntities)
	{
		std::shared_ptr<SpriteComponent> sprite = entity->GetComponent<SpriteComponent>();
		std::shared_ptr<TextComponent> text = entity->GetComponent<TextComponent>();
		std::shared_ptr<LevelComponent> level = entity->GetComponent<LevelComponent>();
		if (sprite != nullptr)
		{
			window->Draw(sprite->GetSprite());
		}
		if (text != nullptr)
		{
			window->Draw(text->GetText());
		}
		if (level != nullptr)
		{
			const unsigned int size = level->GetTotalTileAmount();
			unsigned int tileWidth = 0;
			unsigned int tileHeight = 0;
			level->GetTileSize(tileWidth, tileHeight);

			std::shared_ptr<sf::Texture> texture = UrsusEngine::TextureManager::GetInstance().GetTexture(level->GetTextureUrl());
			
			unsigned int textureX = texture->getSize().x;
			unsigned int textureY = texture->getSize().y;

			//tiles within the tileset
			int XTiles = std::floor(textureX / tileWidth);
			int YTiles = std::floor(textureY / tileHeight);

			sf::VertexArray quad(sf::Quads, 4);
			for (int i = 0; i < size; ++i)
			{
				const Tile& tile = level->GetTileSprite(i);

				//Set Position of each vertex
				quad[0].position = sf::Vector2f(tile.X, tile.Y);
				quad[1].position = sf::Vector2f(tile.X + tileWidth, tile.Y);
				quad[2].position = sf::Vector2f(tile.X + tileWidth, tile.Y + tileHeight);
				quad[3].position = sf::Vector2f(tile.X, tile.Y + tileHeight);

				int X = tile.textureX;
				int Y = tile.textureY;

				//Set UV Coordinates
				quad[0].texCoords = sf::Vector2f(X, Y);
				quad[1].texCoords = sf::Vector2f(X + tileWidth, Y);
				quad[2].texCoords = sf::Vector2f(X + tileWidth, Y + tileHeight);
				quad[3].texCoords = sf::Vector2f(X, Y + tileHeight);

				window->Draw(&quad, texture);

			}
		}
	}
}