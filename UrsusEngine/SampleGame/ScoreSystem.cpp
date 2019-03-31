#include "ScoreSystem.h"
#include "ScoreComponent.h"
#include "../UrsusEngine/Graphics/TextComponent.h"

ScoreSystem::ScoreSystem()
{

}

ScoreSystem::~ScoreSystem()
{

}

bool ScoreSystem::DoesEntityMatch(std::shared_ptr<UrsusEngine::ECS::Entity> entity)
{
	if (entity->HasComponent<ScoreComponent>() && entity->HasComponent<UrsusEngine::ECS::TextComponent>())
	{
		return true;
	}
	return false;
}

void ScoreSystem::Update(UrsusEngine::Engine* engine, float dt)
{

	if (m_Entities.size() == 0)
	{
		return;
	}
	std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>> copiedEntities = m_Entities;
	for (std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>>::iterator entityItr = copiedEntities.begin(); entityItr != copiedEntities.end();)
	{
		std::shared_ptr<UrsusEngine::ECS::Entity> entity = *entityItr;
		std::shared_ptr<UrsusEngine::ECS::TextComponent> textComp = entity->GetComponent<UrsusEngine::ECS::TextComponent>();
		std::shared_ptr<ScoreComponent> scoreComp = entity->GetComponent<ScoreComponent>();
		int score = 0;
		scoreComp->GetScore(score);

		//Dead screen will be reintroduced later with event system
		textComp->SetText("Score " + std::to_string(score));
		++entityItr;
	}
}

