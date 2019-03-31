#pragma once
#include "../UrsusEngine/Patterns/ECS/ISystem.h"

class ScoreSystem : public UrsusEngine::ECS::ISystem
{
public:
	ScoreSystem();
	~ScoreSystem();
public:
	//ISystem
	virtual bool DoesEntityMatch(std::shared_ptr<UrsusEngine::ECS::Entity> entity) override;
	virtual void Update(UrsusEngine::Engine* engine, float dt) override;

	

};