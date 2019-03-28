#include "engine.h"
#include "../Graphics/TextureManager.h"
#include <algorithm>

using namespace UrsusEngine;

Engine::Engine(const int width, const int height, const std::string title, const bool fullscreen)
{
	m_IsRunning = true;
	m_Window = std::make_unique<Window>(width, height, title, fullscreen);
	m_Time =  std::make_unique<Time>();
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
	m_Time->Restart();
}

void Engine::Draw()
{
	m_Window->BeginDraw();

	std::vector<std::shared_ptr<Sprite>>::iterator spriteItr = m_Sprites.begin();
	std::vector<std::shared_ptr<Text>>::iterator textItr = m_Texts.begin();

	while (spriteItr != m_Sprites.end())
	{
		if ((*spriteItr).unique())
		{
			spriteItr = m_Sprites.erase(spriteItr);
		}
		else
		{
			m_Window->Draw((*spriteItr));
			++spriteItr;
		}
	}

	while (textItr != m_Texts.end())
	{
		if ((*textItr).unique())
		{
			textItr = m_Texts.erase(textItr);
		}
		else
		{
			m_Window->Draw((*textItr));
			++textItr;
		}
	}

	m_Window->EndDraw();
}

std::shared_ptr<Sprite> Engine::CreateSprite(const char* url)
{
	std::shared_ptr<sf::Texture> texture = TextureManager::GetInstance().GetTexture(url);
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(texture);
	m_Sprites.push_back(sprite);
	return sprite;
}

std::shared_ptr<Text> Engine::CreateText(const char* url)
{
	std::shared_ptr<Text> text = std::make_shared<Text>(url);
	m_Texts.push_back(text);
	return text;
}

bool Engine::IsKeyPressed(Key key)
{
	return InputHelper::IsKeyPressed(key);
}

const float Engine::GetElapsedTimeAsSeconds()
{
	return m_Time->GetElapsedTimeAsSeconds();
}