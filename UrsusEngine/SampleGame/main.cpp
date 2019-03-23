#include "UrsusEngine/Central/engine.h"
#include "../UrsusEngine/Graphics/Sprite.h"

#ifdef  _DEBUG
#define EngineMain main
#else
#define EngineMain WinMain
#endif //  _DEBUG

int EngineMain()
{
	UrsusEngine::Engine *engine = new UrsusEngine::Engine(640, 480, "Test", false);
	

	//Create Player Sprite
	//Resources located in /bin which are ignored for now in github
	UrsusEngine::Sprite* playerSprite = engine->CreateSprite("Resources/Asteroid_Graphics/player.png");
	playerSprite->Move(320.f, 200.0f);

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
			//Time-Scaled Player movement
			float xMovement = 0.f;
			float yMovement = 0.f;

			if (engine->IsKeyPressed(UrsusEngine::Key::S))
			{
				yMovement = speedPerSecond * dt;
			}
			if (engine->IsKeyPressed(UrsusEngine::Key::W))
			{
				yMovement = -speedPerSecond * dt;
			}
			if (engine->IsKeyPressed(UrsusEngine::Key::D))
			{
				xMovement = speedPerSecond * dt;
			}
			if (engine->IsKeyPressed(UrsusEngine::Key::A))
			{
				xMovement = -speedPerSecond * dt;
			}
			playerSprite->Move(xMovement, yMovement);

			accumulator -= dt;

		}
		
		engine->Draw();
	}

	//Destroy the player
	engine->DestroySprite(playerSprite);
	//nothing
	delete engine;
	return 0;
}