#include <memory>
#include <ctime>
#include <algorithm>
#include "UrsusEngine/Central/engine.h"
#include "../UrsusEngine/Graphics/SpriteComponent.h"
#include "PhysicComponent.h"
#include "PhysicSystem.h"
#include "BulletSystem.h"
#include "PlayerComponent.h"
#include "PlayerSystem.h"
#include "ScoreSystem.h"
#include "ScoreComponent.h"
#include "../UrsusEngine/Graphics/TextComponent.h"
#include "../UrsusEngine/Central/LevelComponent.h"



#ifdef  _DEBUG
#define EngineMain main
#else
#define EngineMain WinMain
#endif //  _DEBUG

int EngineMain()
{
	//Window dimension
	const int width = 800;
	const int height = 800;
	//Create Engine
	std::shared_ptr<UrsusEngine::Engine> engine = std::make_shared<UrsusEngine::Engine>(width, height, "Test");
	
	//Create PhysicSystem
	std::shared_ptr<PhysicSystem> physicSystem = std::make_shared<PhysicSystem>();
	physicSystem->SetBoundaries((float)width, (float)height);
	engine->AddSystem(physicSystem);

	//Create Bullet system
	std::shared_ptr<BulletSystem> bulletSystem = std::make_shared<BulletSystem>();
	engine->AddSystem(bulletSystem);

	//Create Player system
	std::shared_ptr<PlayerSystem> playerSystem = std::make_shared<PlayerSystem>();
	engine->AddSystem(playerSystem);

	//Create score
	std::shared_ptr<ScoreSystem> scoreSystem = std::make_shared<ScoreSystem>();
	engine->AddSystem(scoreSystem);

	//Create Level
	std::shared_ptr<UrsusEngine::ECS::Entity> levelEntity = std::make_shared<UrsusEngine::ECS::Entity>();
	std::shared_ptr<UrsusEngine::LevelComponent>levelComp = levelEntity->AddComponent<UrsusEngine::LevelComponent>();

	const int tileWidth = 50;
	const int tileHeight = 50;
	levelComp->CreateTileset("Resources/Zombie/tiles.png", tileWidth, tileHeight);

	const int levelHeight = 15;
	const int levelWidth = 12;
	char level[levelHeight * levelWidth] =
	{
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, //3, 3, 3, 3, 3, 3, 3, 3,
		3, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, //0, 0, 0, 0, 0, 0, 0, 3,
		3, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, //0, 0, 0, 0, 0, 0, 0, 3,
		3, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, //0, 0, 0, 0, 0, 0, 0, 3,
		3, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, //0, 0, 0, 0, 0, 0, 0, 3,
		3, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, //0, 0, 0, 0, 0, 0, 0, 3,
		3, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, //0, 0, 0, 0, 0, 0, 0, 3,
		3, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, //0, 0, 0, 0, 0, 0, 0, 3,
		3, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, //0, 0, 0, 0, 0, 0, 0, 3,
		3, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, //0, 0, 0, 0, 0, 0, 0, 3,
		3, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, //0, 0, 0, 0, 0, 0, 0, 3,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, //3, 3, 3, 3, 3, 3, 3, 3,
	};

	std::vector<Tile> tiles;
	for (int j = 0; j < levelHeight; ++j)
	{
		for (int i = 0; i < levelWidth; ++i)
		{
			Tile tile;
			tile.X = i * tileWidth;
			tile.Y = j * tileHeight;
			int idx = i + (j* levelWidth);
			tile.Sprite = level[idx];
			tile.IsCollidable = tile.Sprite == 3;
			tiles.push_back(tile);
		}
	}
	levelComp->SetLevel(tiles, levelHeight, levelWidth);
	engine->AddEntity(levelEntity);

	//Score Entity
	std::shared_ptr<UrsusEngine::ECS::Entity> scoreEntity = std::make_shared<UrsusEngine::ECS::Entity>();
	std::shared_ptr<UrsusEngine::ECS::TextComponent> scoreText = scoreEntity->AddComponent<UrsusEngine::ECS::TextComponent>();
	std::shared_ptr<ScoreComponent> scoreComp = scoreEntity->AddComponent<ScoreComponent>();
	scoreText->CreateText("Resources/Asteroid_Graphics/Hyperspace.otf");
	scoreText->SetPosition(10.f, 10.f);
	scoreText->SetColour(255, 255, 255, 255);
	scoreText->SetSize(24);
	engine->AddEntity(scoreEntity);

	//Player entity
	std::shared_ptr<UrsusEngine::ECS::Entity> playerEntity = std::make_shared<UrsusEngine::ECS::Entity>();
	std::shared_ptr<UrsusEngine::ECS::SpriteComponent> playerSprite = playerEntity->AddComponent<UrsusEngine::ECS::SpriteComponent>();
	std::shared_ptr<PhysicComponent> playerPhysic = playerEntity->AddComponent<PhysicComponent>();
	std::shared_ptr<PlayerComponent> playerComp = playerEntity->AddComponent<PlayerComponent>();
	playerComp->SetSpeedPerSecond(1200.f);
	playerComp->SetRotationPerSecond(200.f);
	playerComp->SetBulletSpeedPerSecond(300.f);
	playerComp->SetMaxBulletSpawnCooldown(0.2f);

	playerSprite->CreateSprite("Resources/Asteroid_Graphics/player.png");
	playerSprite->SetPosition(width / 2, height / 2);
	playerPhysic->SetVelocity(0.f, 0.f);
	playerPhysic->SetDamping(0.1f);
	playerPhysic->SetTargetFlag(AsteroidCollisionFlag);
	engine->AddEntity(playerEntity);
	

	while (engine->IsRunning())
	{
		engine->Update();
		engine->Draw();
	}
}

/*

LEGACY



	//Create Player Sprite
	//Resources located in /bin which are ignored for now in github
	std::shared_ptr<UrsusEngine::Sprite> playerSprite = engine->CreateSprite("Resources/Asteroid_Graphics/player.png");
	std::unique_ptr<Player> player = std::make_unique<Player>(playerSprite, width, height);
	player->SetPosition(320.f, 200.0f);

	//Bullets for player
	std::vector<std::shared_ptr<Bullet>> bullets;

	//Score
	std::shared_ptr<UrsusEngine::Text> scoreText = engine->CreateText("Resources/Asteroid_Graphics/Hyperspace.otf");
	std::unique_ptr<Score> score = std::make_unique<Score>(scoreText);
	score->SetPosition(10.0f, 10.0f);
	score->SetScore(0);

	//Asteroids
	std::vector<std::shared_ptr<Asteroid>> asteroids;
	const int asteroidCount = 10;
	const int maxVelocity = 50.f;
	float spawnCD = 0.f;
	std::srand(std::time(nullptr));


	//Define engine chronologics
	//Set update tick rate to 60 times per second
	const float dt = 1 / 60.0f;
	float accumulator = 0.f;

	bool gameEnd = false;

	while (engine->IsRunning())
	{
		//Update engine and thus deltaTime
		engine->Update();

		//Add current elapsed time to accumulator
		accumulator += engine->GetElapsedTimeAsSeconds();

		//Accumulator logic is for scaling the physics correct
		//depending on your computer
		//Meaning: low-end pcs will go through the loop more often than
		//high-end pcs
		while (accumulator >= dt)
		{
			//If the player is dead we can just exit this loop!
			if (gameEnd)
			{
				break;
			}

			//Time-Scaled Player movement
			player->HandleInput(engine);
			player->Update(dt);

			//Check for bullet input
			if (player->IsShooting())
			{
				std::shared_ptr<UrsusEngine::Sprite> bulletSprite = engine->CreateSprite("Resources/Asteroid_Graphics/bullet.png");
				std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(bulletSprite, width, height);
				bullet->Init(player->GetX(), player->GetY(), player->GetRotation());
				bullets.push_back(bullet);
			}

			//If asteroid spawn time run out then try to spawn asteroid
			if (spawnCD <= 0.f && asteroids.size() < asteroidCount)
			{
				std::shared_ptr<UrsusEngine::Sprite> asteroidSprite = engine->CreateSprite("Resources/Asteroid_Graphics/asteroid1.png");
				std::shared_ptr<Asteroid> asteroid = std::make_shared<Asteroid>(asteroidSprite, width, height);
				float x = std::rand() % width;
				float y = std::rand() % height;
				float xVelocity = (std::rand() % maxVelocity * 2) - maxVelocity;
				float yVelocity = (std::rand() % maxVelocity * 2) - maxVelocity;
				float rotation = std::rand() % 360;

				asteroid->SetPosition(x, y);
				asteroid->SetVelocity(xVelocity, yVelocity);
				asteroid->SetRotation(rotation);

				//Check if spawned asteroid overlaps with player
				if (asteroid->GetSprite()->IsCollidingWith(
						player->GetX() - 64,
						player->GetY() - 64,
						128,
						128
				))
				{
					//If created asteroid does overlap with player then delete it
					asteroid = nullptr;
				}
				else
				{
					//If asteroids does not overlaps with player pushback into vector and reset
					//spawn time for next asteroid
					asteroids.push_back(asteroid);
					spawnCD = 1.0f;
				}
			} //otherwise decrement spawntime
			else
			{
				spawnCD -= dt;
			}


			//Iterate through all bullets for collision and lifetime check
			for (std::vector<std::shared_ptr<Bullet>>::iterator bulletIterator = bullets.begin(); bulletIterator != bullets.end();)
			{
				std::shared_ptr<Bullet> bullet = (*bulletIterator);
				bullet->Update(dt);

				//OnCollision and OnLifeTimeOver bullets gets destroyed
				//therefore we describe it with the same logical reaction
				bool collide = bullet->IsLifeTimeOver();
				for (std::vector<std::shared_ptr<Asteroid>>::iterator asteroidIterator = asteroids.begin(); asteroidIterator != asteroids.end();)
				{
					std::shared_ptr<Asteroid> asteroid = (*asteroidIterator);
					if (bullet->GetSprite()->IsCollidingWith(asteroid->GetSprite()))
					{

						asteroidIterator = asteroids.erase(asteroidIterator);
						asteroid = nullptr;
						collide = true;
						//Add score
						score->AddScore(10);
						break;
					}
					//If the asteroid is destroyed we break already, so it's save to always call it here
					++asteroidIterator;
				}

				if (collide)
				{
					bulletIterator = bullets.erase(bulletIterator);
					bullet = nullptr;
				}
				else
				{
					++bulletIterator;
				}
			}

			//Update all asteroids
			for (std::shared_ptr<Asteroid> asteroid : asteroids)
			{
				asteroid->Update(dt);
				if (player != nullptr && player->GetSprite()->IsCollidingWith(asteroid->GetSprite()))
				{
					//Destroy player
					player = nullptr;
					playerSprite = nullptr;
					//display defeat
					scoreText->SetPosition(150.f, 100.f);
					scoreText->SetColour(255, 0, 0);
					scoreText->SetSize(48);
					scoreText->SetText("You are dead!");
					gameEnd = true;
				}
			}

			accumulator -= dt;

		}

		engine->Draw();
	}

	//Destroy the player
	if (player != nullptr)
	{
		player = nullptr;
	}
	//Destroy asteroids
	for (std::shared_ptr<Asteroid> asteroid : asteroids)
	{
		asteroid = nullptr;
	}
	//Destory bullets
	for (std::shared_ptr<Bullet> bullet : bullets)
	{
		bullet = nullptr;
	}
	scoreText = nullptr;
	//nothing
	engine = nullptr;
	return 0;

	*/