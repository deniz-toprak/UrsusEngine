#include "engine.h"

Engine::Engine()
{
	m_IsRunning = true;
}

Engine::~Engine()
{
	m_IsRunning = false;
}