#pragma once
#include "../UrsusEngine/Patterns/ECS/ISystem.h"
#include "ScoreEvent.h"

class UISystem : public UrsusEngine::ECS::ISystem
{
public:
	UISystem();
	~UISystem();
public:
	//ISystem
	virtual bool DoesEntityMatch(std::shared_ptr<UrsusEngine::ECS::Entity> entity) override;
	virtual void Update(UrsusEngine::Engine* engine, float dt) override;

	void OnScoreChange(std::shared_ptr<UrsusEngine::IEvent> event);

private:
	std::shared_ptr<ScoreEventHandler> m_Listener;
	UrsusEngine::EventFunctor m_ScoreEventFunctor;
	//PlayerStats
	int m_Score = 0;
	int m_Health = 0;
	int m_Ammo = 0;
	//Player State
	bool m_Dead = false;

};