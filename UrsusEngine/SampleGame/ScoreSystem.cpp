#include "ScoreSystem.h"
#include "ScoreComponent.h"
#include "../UrsusEngine/Graphics/TextComponent.h"
#include "../UrsusEngine/Central/EngineAssert.h"

ScoreSystem::ScoreSystem()
{
	m_Listener = std::make_shared<ScoreEventHandler>();
	m_ScoreEventFunctor = std::bind(&ScoreSystem::OnScoreChange, this, std::placeholders::_1);
	m_Listener->AddCallback(m_ScoreEventFunctor);
	UrsusEngine::EventManager::GetInstance().AddEventListener(m_Listener);
}

ScoreSystem::~ScoreSystem()
{
	UrsusEngine::EventManager::GetInstance().RemoveEventListener(m_Listener);
	m_Listener->RemoveCallback(m_ScoreEventFunctor);
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

void ScoreSystem::OnScoreChange(std::shared_ptr<UrsusEngine::IEvent> event)
{
	std::shared_ptr<ScoreEvent> scoreEvent = std::dynamic_pointer_cast<ScoreEvent>(event);
	assert(scoreEvent != nullptr);

	std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>> copiedEntities = m_Entities;
	for (std::shared_ptr<UrsusEngine::ECS::Entity>& entity : m_Entities)
	{
		std::shared_ptr<ScoreComponent> scoreComp = entity->GetComponent<ScoreComponent>();
		//get the values from the component
		int score = 0;
		scoreComp->GetScore(score);
		score += scoreEvent->Score;
		scoreComp->SetScore(score);
	}
}
