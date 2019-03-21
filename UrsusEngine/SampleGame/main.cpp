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
		engine->Draw();
	}

	//Destroy the player
	engine->DestroySprite(playerSprite);
	//nothing
	delete engine;
	return 0;
}