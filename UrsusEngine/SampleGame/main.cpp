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

	while (engine->IsRunning())
	{
		engine->Update();

		if (engine->IsKeyPressed(UrsusEngine::Key::S))
		{
			playerSprite->Move(0, 0.1f);
		}
		if (engine->IsKeyPressed(UrsusEngine::Key::W))
		{
			playerSprite->Move(0, -0.1f);
		}if (engine->IsKeyPressed(UrsusEngine::Key::D))
		{
			playerSprite->Move(0.1f, 0);
		}
		if (engine->IsKeyPressed(UrsusEngine::Key::A))
		{
			playerSprite->Move(-0.1f,0);
		}

		engine->Draw();
	}

	//Destroy the player
	engine->DestroySprite(playerSprite);
	//nothing
	delete engine;
	return 0;
}