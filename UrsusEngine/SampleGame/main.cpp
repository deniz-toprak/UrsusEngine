#include "UrsusEngine/Central/engine.h"

#ifdef  _DEBUG
#define EngineMain main
#else
#define EngineMain WinMain
#endif //  _DEBUG

int EngineMain()
{
	UrsusEngine::Engine *engine = new UrsusEngine::Engine(640, 480, "Test", false);
	//code here
	while (engine->IsRunning())
	{
		engine->Update();
	}
	//nothing
	delete engine;
	return 0;
}