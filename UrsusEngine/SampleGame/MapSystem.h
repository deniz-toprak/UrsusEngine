#pragma once

#include "../UrsusEngine/Patterns/ECS/ISystem.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

class MapSystem : public UrsusEngine::ECS::ISystem
{
public:
	MapSystem();
	~MapSystem();

public:
	//ISystem override
	virtual bool DoesEntityMatch(std::shared_ptr<UrsusEngine::ECS::Entity> entity) override;
	virtual void Update(UrsusEngine::Engine* engine, float dt) override;
	virtual void Init(UrsusEngine::Engine* engine) override;

private:
	const tmx::Tileset::Tile* GetTile(tmx::Map& map, int tileID);
	void Reload(UrsusEngine::Engine* engine, std::string level);
	void LoadLevel(UrsusEngine::Engine* engine, std::string level);
	void LoadUI(UrsusEngine::Engine* engine);
	void SetTileset(UrsusEngine::Engine* engine, tmx::Map& map);
	void AddTiles(const tmx::TileLayer* layer, tmx::Map& map);
	void AddPlayer(UrsusEngine::Engine* engine, const tmx::Object& object, const tmx::Tileset::Tile* tile);
	void AddEnemy(UrsusEngine::Engine* engine, const tmx::Object& object, const tmx::Tileset::Tile* tile);
	void AddItem(UrsusEngine::Engine* engine, const tmx::Object& object, const tmx::Tileset::Tile* tile);
private:
	std::shared_ptr<UrsusEngine::ECS::Entity> m_LevelEntity = nullptr;
	unsigned int m_MapWidth = 0;
	unsigned int m_MapHeight = 0;
	unsigned int m_TileWidth = 0;
	unsigned int m_TileHeight = 0;

	bool m_ReloadKeyPress = false;

};