#include <random>
#include <ctime>
#include "UrsusEngine/Central/engine.h"
#include "../UrsusEngine/Graphics/Sprite.h"
#include "../UrsusEngine/Graphics/Text.h"
#include "Player.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Score.h"


#ifdef  _DEBUG
#define EngineMain main
#else
#define EngineMain WinMain
#endif //  _DEBUG

int EngineMain()
{
	const int width = 640;
	const int height = 480;
	std::shared_ptr<UrsusEngine::Engine> engine = std::make_shared<UrsusEngine::Engine>(width, height, "Test", false);
	

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
}