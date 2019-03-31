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
	std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>> copiedEntities = m_Entities;
	for (std::shared_ptr<Entity> entity : copiedEntities)
	{
		std::shared_ptr<SpriteComponent> sprite = entity->GetComponent<SpriteComponent>();
		std::shared_ptr<TextComponent> text = entity->GetComponent<TextComponent>();
		if (sprite != nullptr)
		{
			window->Draw(sprite->GetSprite());
		}
		if (text != nullptr)
		{
			window->Draw(text->GetText());
		}
	}
}