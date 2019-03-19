#include "UrsusEngine/Central/engine.h"

#ifdef  _DEBUG
#define EngineMain main
#else
#define EngineMain WinMain
#endif //  _DEBUG

int EngineMain()
{
	Engine* engine = new Engine();
	//code here
	//nothing
	delete engine;
	return 0;
}