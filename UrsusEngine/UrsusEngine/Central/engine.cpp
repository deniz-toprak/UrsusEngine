#include "engine.h"
#include "../Graphics/TextureManager.h"
#include <algorithm>
#include "EventManager.h"

using namespace UrsusEngine;

Engine::Engine(const int width, const int height, const std::string title)
{
	m_IsRunning = true;
	m_Window = std::make_shared<Window>(width, height, title);
	m_Time =  std::make_unique<Time>();
	m_RenderSystem = std::make_shared<ECS::RenderSystem>();
	AddSystem(m_RenderSystem);
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

	//Fps lock

	const float dt = 1 / 60.0f;

	const float elapsedTime = GetElapsedTimeAsSeconds();

	m_AccumulatedTime += elapsedTime;
	while (m_AccumulatedTime >= dt)
	{
		//update all systems
		for (std::shared_ptr<ECS::ISystem> system : m_Systems)
		{
			system->Update(this, dt);
		}
		//Call update on event manager
		EventManager::GetInstance().Update();
		//at the end of the update, decrement accumulator
		m_AccumulatedTime -= dt;
	}
}

void Engine::Draw()
{
	m_Window->BeginDraw();
	
	m_RenderSystem->Draw(m_Window);

	m_Window->EndDraw();
}

bool Engine::IsKeyPressed(Key key)
{
	return InputHelper::IsKeyPressed(key);
}

bool Engine::IsMousePressed(MouseButton button)
{
	return InputHelper::IsMousePresse(button);
}

bool Engine::GetCursorPosition(float& X, float& Y) const
{
	InputHelper::GetCurserPosition(this, X, Y);
}


const float Engine::GetElapsedTimeAsSeconds()
{
	return m_Time->GetElapsedTimeAsSeconds();
}

void Engine::AddEntity(std::shared_ptr<UrsusEngine::ECS::Entity> entity)
{
	//try find entity if it isn't already in vector
	if (std::find(m_Entities.begin(), m_Entities.end(), entity) != m_Entities.end())
	{
		return;
	}
	m_Entities.push_back(entity);
	//Then iterate through the system and add entity to every system it fits
	for (std::shared_ptr<ECS::ISystem>& system : m_Systems)
	{
		if (system->DoesEntityMatch(entity))
		{
			system->AddEntity(entity);
		}
	}
}

void Engine::RemoveEntity(std::shared_ptr<UrsusEngine::ECS::Entity> entity)
{
	//try get iterator for entity
	std::vector<std::shared_ptr<ECS::Entity>>::iterator entityItr = std::find(m_Entities.begin(), m_Entities.end(), entity);
	//if entity has not been found, return
	if (entityItr == m_Entities.end())
	{
		return;
	}
	//remove entity from vector
	m_Entities.erase(entityItr);

	//go through all system and remove the entity if it's inside
	for (std::shared_ptr<ECS::ISystem>& system : m_Systems)
	{
		system->RemoveEntity(entity);
	}
}

void Engine::AddSystem(std::shared_ptr<ECS::ISystem> system)
{
	if (std::find(m_Systems.begin(), m_Systems.end(), system) != m_Systems.end())
	{
		return;
	}
	m_Systems.push_back(system);
}

void Engine::RemoveSystem(std::shared_ptr<ECS::ISystem> system)
{
	//try get iterator for system
	std::vector<std::shared_ptr<ECS::ISystem>>::iterator systemItr = std::find(m_Systems.begin(), m_Systems.end(), system);
	//if system not found, return
	if (systemItr == m_Systems.end())
	{
		return;
	}
	//otherwise erase it from vector
	m_Systems.erase(systemItr);
}

