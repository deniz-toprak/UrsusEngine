#pragma once
#include "../UrsusEngine/Patterns/ECS/ISystem.h"
#include "ScoreEvent.h"

class ScoreSystem : public UrsusEngine::ECS::ISystem
{
public:
	ScoreSystem();
	~ScoreSystem();
public:
	//ISystem
	virtual bool DoesEntityMatch(std::shared_ptr<UrsusEngine::ECS::Entity> entity) override;
	virtual void Update(UrsusEngine::Engine* engine, float dt) override;

	void OnScoreChange(std::shared_ptr<UrsusEngine::IEvent> event);

private:
	std::shared_ptr<ScoreEventHandler> m_Listener;
	UrsusEngine::EventFunctor m_ScoreEventFunctor;
	int m_ScoreAdd = 0;
	bool m_Dead = false;

};