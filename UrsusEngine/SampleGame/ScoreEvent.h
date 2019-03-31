#pragma once
#include "../UrsusEngine/Central/EventManager.h"

class ScoreEvent : public UrsusEngine::IEvent
{
public:
	int Score = 0;
};

class ScoreEventHandler : public UrsusEngine::IEventHandler
{
public:
	bool DoesEventMatch(std::shared_ptr<UrsusEngine::IEvent> event) override
	{
		return std::dynamic_pointer_cast<ScoreEvent>(event) != nullptr;
	}
};