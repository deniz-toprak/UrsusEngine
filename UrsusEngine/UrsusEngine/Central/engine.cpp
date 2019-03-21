#include "engine.h"

using namespace UrsusEngine;

Engine::Engine(const int width, const int height, const std::string title, const bool fullscreen)
{
	m_IsRunning = true;
	m_Window = new Window(width, height, title, fullscreen);
}

Engine::~Engine()
{
	m_IsRunning = false;
}

void Engine::Update()
{
	if (!m_Window->Update())
	{
		//Window has been closed
		m_IsRunning = false;
		return;
	}
}