#include "MapSystem.h"
#include "../UrsusEngine/Central/LevelComponent.h"
#include "../UrsusEngine/Central/engine.h"
#include "../UrsusEngine/Graphics/TextComponent.h"
#include "ScoreComponent.h"
#include "../UrsusEngine/Graphics/SpriteComponent.h"
#include "PlayerComponent.h"
#include "PhysicComponent.h"
#include "EnemyComponent.h"
#include "ItemComponent.h"
#include "AmmoComponent.h"
#include "HealthComponent.h"
#include "AmmoComponent.h"
#include "Utils.h"

#ifndef MapURL
#define MapURL "Resources/Zombie/Level1.tmx"
#endif // !MapURL


MapSystem::MapSystem()
{

}

MapSystem::~MapSystem()
{

}


bool MapSystem::DoesEntityMatch(std::shared_ptr<UrsusEngine::ECS::Entity> entity)
{
	//for reload, we save everything that has a physicsComponent
	if (entity->HasComponent<UrsusEngine::ECS::SpriteComponent>() || entity->HasComponent<UrsusEngine::ECS::TextComponent>())
	{
		return true;
	}
	return false;
}

void MapSystem::Update(UrsusEngine::Engine* engine, float dt)
{
	bool keyPress = engine->IsKeyPressed(UrsusEngine::Key::F1);
	if (!m_ReloadKeyPress && keyPress)
	{
		Reload(engine, MapURL);
		m_ReloadKeyPress = true;
	}
	else if (m_ReloadKeyPress && !keyPress)
	{
		m_ReloadKeyPress = false;
	}
}

void MapSystem::Init(UrsusEngine::Engine* engine)
{
	m_LevelEntity = std::make_shared<UrsusEngine::ECS::Entity>();
	std::shared_ptr<UrsusEngine::LevelComponent> levelComp = m_LevelEntity->AddComponent<UrsusEngine::LevelComponent>();
	engine->AddEntity(m_LevelEntity);

	LoadLevel(engine, MapURL);
}

const tmx::Tileset::Tile* MapSystem::GetTile(tmx::Map& map, int tileID)
{
	for (const tmx::Tileset& tileset : map.getTilesets())
	{
		if (tileset.hasTile(tileID))
		{
			return tileset.getTile(tileID);
		}
	}
	return nullptr;
}

void MapSystem::Reload(UrsusEngine::Engine* engine, std::string level)
{
	//Delete all entities
	while (m_Entities.size() != 0)
	{
		engine->RemoveEntity(m_Entities[0]);
	}
	LoadLevel(engine, level);
}

void MapSystem::LoadLevel(UrsusEngine::Engine* engine, std::string level)
{
	tmx::Map map;
	map.load(level);
	SetTileset(engine, map);

	const std::vector<tmx::Layer::Ptr>& layers = map.getLayers();
	m_MapWidth = map.getTileCount().x;
	m_MapHeight = map.getTileCount().y;

	//iterate through every layer
	for (int i = 0; i < layers.size(); ++i)
	{
		if (layers[i]->getType() == tmx::Layer::Type::Tile)
		{
			//If the layer is a tileset then add them
			const tmx::TileLayer* layer = dynamic_cast<const tmx::TileLayer*>(layers[i].get());
			AddTiles(layer, map);
		}
		else if (layers[i]->getType() == tmx::Layer::Type::Object)
		{
			//if they are objects then cast and distribute objects.
			const tmx::ObjectGroup& objects = *dynamic_cast<const tmx::ObjectGroup*>(layers[i].get());
			for (const tmx::Object& object : objects.getObjects())
			{
				const tmx::Tileset::Tile* tile = GetTile(map, object.getTileID());
				if (tile->type == "Player")
				{
					AddPlayer(engine, object, tile);
				}
				else if (tile->type == "Enemy")
				{
					AddEnemy(engine, object, tile);
				}
				else if (tile->type == "Item")
				{
					AddItem(engine, object, tile);
				}
			}

		}
	}
	LoadUI(engine);
}

void MapSystem::LoadUI(UrsusEngine::Engine* engine)
{
	std::shared_ptr<UrsusEngine::ECS::Entity> scoreEntity = std::make_shared<UrsusEngine::ECS::Entity>();
	std::shared_ptr<UrsusEngine::ECS::TextComponent> scoreText = scoreEntity->AddComponent<UrsusEngine::ECS::TextComponent>();
	std::shared_ptr<ScoreComponent> scoreComp = scoreEntity->AddComponent<ScoreComponent>();

	scoreText->CreateText("Resources/Asteroid_Graphics/Hyperspace.otf");
	scoreText->SetColour(255, 255, 255, 255);
	scoreText->SetPosition(10.0f, 10.0f);
	scoreText->SetSize(24);

	engine->AddEntity(scoreEntity);

	std::shared_ptr<UrsusEngine::ECS::Entity> ammoEntity = std::make_shared<UrsusEngine::ECS::Entity>();
	std::shared_ptr<UrsusEngine::ECS::TextComponent> ammoText = ammoEntity->AddComponent<UrsusEngine::ECS::TextComponent>();
	std::shared_ptr<AmmoComponent> ammoComp = ammoEntity->AddComponent<AmmoComponent>();

	ammoText->CreateText("Resources/Asteroid_Graphics/Hyperspace.otf");
	ammoText->SetColour(255, 255, 255, 255);
	ammoText->SetPosition(10.0f, 40.0f);
	ammoText->SetSize(24);

	engine->AddEntity(ammoEntity);

	std::shared_ptr<UrsusEngine::ECS::Entity> healthEntity = std::make_shared<UrsusEngine::ECS::Entity>();
	std::shared_ptr<UrsusEngine::ECS::TextComponent> healthText = healthEntity->AddComponent<UrsusEngine::ECS::TextComponent>();
	std::shared_ptr<HealthComponent> healthComp = healthEntity->AddComponent<HealthComponent>();

	healthText->CreateText("Resources/Asteroid_Graphics/Hyperspace.otf");
	healthText->SetColour(255, 255, 255, 255);
	healthText->SetPosition(10.0f, 70.0f);
	healthText->SetSize(24);

	engine->AddEntity(healthEntity);
}

void MapSystem::SetTileset(UrsusEngine::Engine* engine, tmx::Map& map)
{
	std::shared_ptr<UrsusEngine::LevelComponent> levelComp = m_LevelEntity->GetComponent<UrsusEngine::LevelComponent>();
	//Go through every tileset
	for (const tmx::Tileset& tileset : map.getTilesets())
	{
		bool isTileMap = false;
		for (const tmx::Property& property : tileset.getProperties())
		{
			//filter tilemap property out of tileset
			if (property.getName() == "IsTileMap")
			{
				isTileMap = true;
				break;
			}
		}

		if (isTileMap)
		{
			m_TileWidth = tileset.getTileSize().x;
			m_TileHeight = tileset.getTileSize().y;
			levelComp->CreateTileset(tileset.getImagePath(), m_TileWidth, m_TileHeight);
			break;
			//If tilemap is found and processed break first for each loop
		}
	}
}

void MapSystem::AddTiles(const tmx::TileLayer* layer, tmx::Map& map)
{
	//engine internal tile array
	std::vector<Tile> gameTiles;
	std::shared_ptr<UrsusEngine::LevelComponent> levelComp = m_LevelEntity->AddComponent<UrsusEngine::LevelComponent>();
	const std::vector<tmx::TileLayer::Tile>& layerTiles = layer->getTiles();
	for (int i = 0; i < layerTiles.size(); ++i)
	{
		const tmx::TileLayer::Tile& layerTile = layerTiles[i];
		const tmx::Tileset::Tile* tile = GetTile(map, layerTile.ID);

		Tile gameTile;
		gameTile.X = (i % m_MapWidth) * m_TileWidth;
		gameTile.Y = std::floor(i / m_MapHeight) * m_TileHeight;
		gameTile.textureX = tile->imagePosition.x;
		gameTile.textureY = tile->imagePosition.y;
		for (const tmx::Property& property : tile->properties)
		{
			if (property.getName() == "Collidable")
			{
				//Set is walkable property by getting it from the tilemap
				gameTile.IsCollidable = property.getBoolValue();
			}
		}
		gameTiles.push_back(gameTile);
	}
	//at the end set the level
	levelComp->SetLevel(gameTiles, m_MapWidth, m_MapHeight);
}

void MapSystem::AddPlayer(UrsusEngine::Engine* engine, const tmx::Object& object, const tmx::Tileset::Tile* tile)
{
	std::shared_ptr<UrsusEngine::ECS::Entity> playerEntity = std::make_shared<UrsusEngine::ECS::Entity>();
	std::shared_ptr<UrsusEngine::ECS::SpriteComponent> playerSprite = playerEntity->AddComponent<UrsusEngine::ECS::SpriteComponent>();
	std::shared_ptr<PhysicComponent> playerPhysics = playerEntity->AddComponent<PhysicComponent>();
	std::shared_ptr<PlayerComponent> playerComp = playerEntity->AddComponent<PlayerComponent>();
	playerSprite->CreateSprite(tile->imagePath);
	playerSprite->SetPosition(object.getPosition().x, object.getPosition().y);

	playerPhysics->SetVelocity(0.f, 0.0f);
	playerPhysics->SetDamping(0.1f);
	playerPhysics->SetTargetFlag(EnemyCollisionFlag | ItemCollisionFlag);

	for (const tmx::Property& property : tile->properties)
	{
		if (property.getName() == "BulletSpeedPerSecond")
		{
			playerComp->SetBulletSpeedPerSecond(property.getFloatValue());
		}
		if (property.getName() == "MaxBulletSpawnCooldown")
		{
			playerComp->SetMaxBulletSpawnCooldown(property.getFloatValue());
		}
		if (property.getName() == "SpeedPerSecond")
		{
			playerComp->SetSpeedPerSecond(property.getFloatValue());
		}
		if (property.getName() == "StartAmmo")
		{
			playerComp->SetAmmo(property.getIntValue());
		}
		if (property.getName() == "StartHP")
		{
			playerComp->SetHP(property.getIntValue());
		}
	}
	engine->AddEntity(playerEntity);
}

void MapSystem::AddEnemy(UrsusEngine::Engine* engine, const tmx::Object& object, const tmx::Tileset::Tile* tile)
{
	std::shared_ptr<UrsusEngine::ECS::Entity> entity = std::make_shared<UrsusEngine::ECS::Entity>();
	std::shared_ptr<UrsusEngine::ECS::SpriteComponent> spriteComp = entity->AddComponent<UrsusEngine::ECS::SpriteComponent>();
	std::shared_ptr<PhysicComponent> physicComp = entity->AddComponent<PhysicComponent>();
	std::shared_ptr<EnemyComponent> enemyComp = entity->AddComponent<EnemyComponent>();
	spriteComp->CreateSprite(tile->imagePath);
	spriteComp->SetPosition(object.getPosition().x, object.getPosition().y);

	physicComp->SetVelocity(0.f, 0.0f);
	physicComp->SetDamping(0.1f);
	physicComp->SetCollisionFlag(EnemyCollisionFlag);
	physicComp->SetTargetFlag(BulletCollisionFlag);
	for (const tmx::Property& property : tile->properties)
	{
		if (property.getName() == "HP")
		{
			enemyComp->SetHP(property.getIntValue());
		}
		if (property.getName() == "SpeedPerSecond")
		{
			enemyComp->SetSpeedPerSecond(property.getFloatValue());
		}
	}
	engine->AddEntity(entity);
}

void MapSystem::AddItem(UrsusEngine::Engine* engine, const tmx::Object& object, const tmx::Tileset::Tile* tile)
{
	std::shared_ptr<UrsusEngine::ECS::Entity> entity = std::make_shared<UrsusEngine::ECS::Entity>();
	std::shared_ptr<UrsusEngine::ECS::SpriteComponent> spriteComp = entity->AddComponent<UrsusEngine::ECS::SpriteComponent>();
	std::shared_ptr<PhysicComponent> physicComp = entity->AddComponent<PhysicComponent>();
	std::shared_ptr<ItemComponent> itemComp = entity->AddComponent<ItemComponent>();
	spriteComp->CreateSprite(tile->imagePath);
	spriteComp->SetPosition(object.getPosition().x, object.getPosition().y);
	physicComp->SetCollisionFlag(ItemCollisionFlag);
	for (const tmx::Property& property : tile->properties)
	{
		if (property.getName() == "HP")
		{
			itemComp->SetHP(property.getIntValue());
		}
		if (property.getName() == "Ammo")
		{
			itemComp->SetAmmo(property.getIntValue());
		}
	}
	engine->AddEntity(entity);
}

