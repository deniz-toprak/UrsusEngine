#pragma once
#include "../UrsusEngine/Patterns/ECS/ISystem.h"

class EnemySystem : public UrsusEngine::ECS::ISystem
{
public:
	EnemySystem();
	~EnemySystem();

public:
	//ISystem
	virtual bool DoesEntityMatch(std::shared_ptr<UrsusEngine::ECS::Entity> entity) override;
	virtual void Update(UrsusEngine::Engine* engine, float dt) override;

private:
	bool inline UpdateSingleEntity(UrsusEngine::Engine* engine, std::shared_ptr<UrsusEngine::ECS::Entity> entity, float dt);

private:
	//weak because the player can be destroyed
	//Fun-Fact: People who are not ambi-dextruous do have muscle disbalances
	//Causing them to have a strong dominant side and a weak(_ptr) side
	//This can be counter-measured by training both sides equally hard
	//Now bad joke time over
	std::weak_ptr<UrsusEngine::ECS::Entity> m_PlayerEntity;
};