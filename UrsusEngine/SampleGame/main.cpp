#include "UrsusEngine/engine.h"

#ifdef  _DEBUG
#define EngineMain main
#else
#define EngineMain WinMain
#endif //  _DEBUG

int EngineMain()
{
	Engine* engine = new Engine();
	//code here
	delete engine;
	return 0;
}