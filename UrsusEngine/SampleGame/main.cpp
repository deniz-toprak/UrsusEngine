#include "UrsusEngine/Central/engine.h"
#include "../UrsusEngine/Graphics/SpriteComponent.h"
#include "PhysicSystem.h"
#include "BulletSystem.h"
#include "PlayerSystem.h"
#include "MapSystem.h"
#include "EnemySystem.h"
#include "UISystem.h"

#include <memory>
#include <ctime>
#include <algorithm>



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
	engine->AddSystem(physicSystem);

	//Create Bullet system
	std::shared_ptr<BulletSystem> bulletSystem = std::make_shared<BulletSystem>();
	engine->AddSystem(bulletSystem);

	//Create Player system
	std::shared_ptr<PlayerSystem> playerSystem = std::make_shared<PlayerSystem>();
	engine->AddSystem(playerSystem);

	//Create enemy system
	std::shared_ptr<EnemySystem> enemySystem = std::make_shared<EnemySystem>();
	engine->AddSystem(enemySystem);

	//UISystem
	std::shared_ptr<UISystem> uiSystem = std::make_shared<UISystem>();
	engine->AddSystem(uiSystem);

	//Load map and player 	
	std::shared_ptr<MapSystem> mapSystem = std::make_shared<MapSystem>();
	engine->AddSystem(mapSystem);

	while (engine->IsRunning())
	{
		engine->Update();
		engine->Draw();
	}
}
