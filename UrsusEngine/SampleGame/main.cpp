#include "UrsusEngine/Central/engine.h"
#include "../UrsusEngine/Graphics/Sprite.h"
#include "../UrsusEngine/Graphics/Text.h"
#include "Player.h"

#ifdef  _DEBUG
#define EngineMain main
#else
#define EngineMain WinMain
#endif //  _DEBUG

int EngineMain()
{
	const int width = 640;
	const int height = 480;
	UrsusEngine::Engine *engine = new UrsusEngine::Engine(width, height, "Test", false);
	

	//Create Player Sprite
	//Resources located in /bin which are ignored for now in github
	UrsusEngine::Sprite* playerSprite = engine->CreateSprite("Resources/Asteroid_Graphics/player.png");
	Player* player = new Player(playerSprite, width, height);
	playerSprite->Move(320.f, 200.0f);
	
	//Score
	int playerScore = 0;
	UrsusEngine::Text* scoreText = engine->CreateText("Resources/Asteroid_Graphics/Hyperspace.otf");
	scoreText->SetPosition(10.0f, 10.0f);
	scoreText->SetColour(255, 255, 255);
	scoreText->SetSize(24);
	scoreText->SetText("Score: " + std::to_string(0));

	//Asteroids
	UrsusEngine::Sprite* asteroid = engine->CreateSprite("Resources/Asteroid_Graphics/asteroid1.png");
	asteroid->Move(500.0f, 220.f);

	//Game Values
	const float speedPerSecond = 200.f;

	//Define engine chronologics
	//Set update tick rate to 60 times per second
	const float dt = 1 / 60.0f;
	float accumulator = 0.f;

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
			if (playerSprite == nullptr)
			{
				break;
			}


			//Time-Scaled Player movement
			player->HandleInput(engine);
			player->Update(dt);

			if (player->GetSprite()->IsCollidingWith(asteroid))
			{
				delete player;
				player = nullptr;
				//Destroy player
				engine->DestroySprite(playerSprite);
				playerSprite = nullptr;
				//display defeat
				scoreText->SetPosition(150.f, 100.f);
				scoreText->SetColour(255, 0, 0);
				scoreText->SetSize(48);
				scoreText->SetText("You are dead!\nYour score: " + std::to_string(playerScore));
			}

			accumulator -= dt;

		}

		
		engine->Draw();
	}

	//Destroy the player
	engine->DestroySprite(playerSprite);
	engine->DestroyText(scoreText);
	//nothing
	delete engine;
	return 0;
}