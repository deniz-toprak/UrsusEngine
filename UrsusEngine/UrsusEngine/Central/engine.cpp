#include "engine.h"
#include <algorithm>

using namespace UrsusEngine;

Engine::Engine(const int width, const int height, const std::string title, const bool fullscreen)
{
	m_IsRunning = true;
	m_Window = new Window(width, height, title, fullscreen);
	m_Input = new Input();
	m_Time = new Time();
}

Engine::~Engine()
{
	m_IsRunning = false;
	delete m_Window;
	delete m_Input;
	delete m_Time;
}

void Engine::Update()
{
	if (!m_Window->Update())
	{
		//Window has been closed
		m_IsRunning = false;
		return;
	}
	m_Time->Restart();
}

void Engine::Draw()
{
	m_Window->BeginDraw();
	for (Sprite* sprite : m_Sprites)
	{
		m_Window->Draw(sprite);
	}
	m_Window->EndDraw();
}

Sprite* Engine::CreateSprite(const char* url)
{
	Sprite* sprite = new Sprite(url);
	m_Sprites.push_back(sprite);
	return sprite;
}

void Engine::DestroySprite(Sprite* sprite)
{
	//Try find sprite
	std::vector<Sprite*>::iterator spriteItr = std::find(m_Sprites.begin(), m_Sprites.end(), sprite);
	//Sprite has not been found, return
	if (spriteItr == m_Sprites.end())
	{
		return;
	}

	//remove sprite
	m_Sprites.erase(spriteItr);
	delete sprite;
}

bool Engine::IsKeyPressed(Key key)
{
	return m_Input->IsKeyPressed(key);
}

const float Engine::GetElapsedTimeAsSeconds()
{
	return m_Time->GetElapsedTimeAsSeconds();
}