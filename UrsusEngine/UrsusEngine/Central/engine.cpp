#include "engine.h"
#include <algorithm>

using namespace UrsusEngine;

Engine::Engine(const int width, const int height, const std::string title, const bool fullscreen)
{
	m_IsRunning = true;
	m_Window = new Window(width, height, title, fullscreen);
	m_Time = new Time();
}

Engine::~Engine()
{
	m_IsRunning = false;
	delete m_Window;
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

	for (Text* text : m_Texts)
	{
		m_Window->Draw(text);
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
	if (sprite == nullptr)
	{
		return;
	}
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

Text* Engine::CreateText(const char* url)
{
	Text* text = new Text(url);
	m_Texts.push_back(text);
	return text;
}

void Engine::DestroyText(Text* text)
{
	if (text == nullptr)
	{
		return;
	}
	//Try find text
	std::vector<Text*>::iterator textItr = std::find(m_Texts.begin(), m_Texts.end(), text);
	//Sprite has not been found, return
	if (textItr == m_Texts.end())
	{
		return;
	}

	//remove sprite
	m_Texts.erase(textItr);
	delete text;
}

bool Engine::IsKeyPressed(Key key)
{
	return InputHelper::IsKeyPressed(key);
}

const float Engine::GetElapsedTimeAsSeconds()
{
	return m_Time->GetElapsedTimeAsSeconds();
}