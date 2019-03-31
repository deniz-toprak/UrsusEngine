#include "BulletSystem.h"
#include "../UrsusEngine/Central/engine.h"
#include "BulletComponent.h"
#include "PhysicComponent.h"
#include "ScoreEvent.h"


BulletSystem::BulletSystem()
{

}

BulletSystem::~BulletSystem()
{

}

bool BulletSystem::DoesEntityMatch(std::shared_ptr<UrsusEngine::ECS::Entity> entity)
{
	if (entity->HasComponent<BulletComponent>())
	{
		return true;
	}
	return false;
}

void BulletSystem::Update(UrsusEngine::Engine* engine, float dt)
{
	//Return if there is nothing to update
	if (m_Entities.size() == 0)
	{
		return;
	}
	//Cache entities as we might delete them
	std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>> copiedEntites = m_Entities;
	for (std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>>::iterator entityItr = copiedEntites.begin(); entityItr != copiedEntites.end();)
	{
		std::shared_ptr<UrsusEngine::ECS::Entity> entity = *entityItr;
		if (!UpdateSingleEntity(engine, entity, dt))
		{
			engine->RemoveEntity(entity);
		}
		++entityItr;
	}
}

bool BulletSystem::UpdateSingleEntity(UrsusEngine::Engine* engine, std::shared_ptr<UrsusEngine::ECS::Entity> entity, const float dt)
{
	std::shared_ptr<BulletComponent> bulletComp = entity->GetComponent<BulletComponent>();
	std::shared_ptr<PhysicComponent> physicComp = entity->GetComponent<PhysicComponent>();

	//decrease lifetime, if it's 0, return false
	float lifeTime = 0.f;
	bulletComp->GetLifeTime(lifeTime);
	lifeTime -= dt;
	if (lifeTime < 0.f)
	{
		return false;
	}

	bulletComp->SetLifeTime(lifeTime);
	std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>> collisions;
	physicComp->GetCollisions(collisions);
	if (collisions.size() == 0)
	{
		return true;
	}
	//get first entity
	std::shared_ptr<UrsusEngine::ECS::Entity>& firstCollision = collisions[0];
	//delete
	engine->RemoveEntity(firstCollision);

	//throw score event
	std::shared_ptr<ScoreEvent> event = std::make_shared<ScoreEvent>();
	event->Score = 10;
	UrsusEngine::EventManager::GetInstance().PushEvent(event);
	return false;
}

