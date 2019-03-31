#include "RenderSystem.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include <SFML/Graphics.hpp>


using namespace UrsusEngine::ECS;

RenderSystem::RenderSystem()
{

}

RenderSystem::~RenderSystem()
{

}

bool RenderSystem::DoesEntityMatch(std::shared_ptr<Entity> entity)
{
	if (entity->HasComponent<SpriteComponent>()
		|| entity->HasComponent<TextComponent>())
	{
		return true;
	}
	return false;
}

void RenderSystem::Draw(std::shared_ptr<UrsusEngine::Window> window)
{
	for (std::shared_ptr<Entity> entity : m_Entities)
	{
		std::shared_ptr<SpriteComponent> sprite = entity->GetComponent<SpriteComponent>();
		window->Draw(sprite->GetSprite());
	}
}