#include "EnemySystem.h"
#include "PlayerComponent.h"
#include "EnemyComponent.h"
#include "PhysicComponent.h"
#include "../UrsusEngine/Graphics/SpriteComponent.h"
#include "../UrsusEngine/Central/engine.h"

EnemySystem::EnemySystem()
{

}

EnemySystem::~EnemySystem()
{

}

bool EnemySystem::DoesEntityMatch(std::shared_ptr<UrsusEngine::ECS::Entity> entity)
{
	if (entity->HasComponent<PlayerComponent>())
	{
		//If player then cache ptr
		m_PlayerEntity = entity;
		return false;
	}
	if (entity->HasComponent<EnemyComponent>())
	{
		return true;
	}
	return false;
}

void EnemySystem::Update(UrsusEngine::Engine* engine, float dt)
{
	//Cache because vector could be edited in the meanwhile
	std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>> copiedEntities = m_Entities;
	for (std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>>::iterator entityItr = copiedEntities.begin(); entityItr != copiedEntities.end();)
	{
		std::shared_ptr<UrsusEngine::ECS::Entity> entity = *entityItr;
		if (!UpdateSingleEntity(engine, entity, dt))
		{
			engine->RemoveEntity(entity);
		}
		++entityItr;
	}
}

bool inline EnemySystem::UpdateSingleEntity(UrsusEngine::Engine* engine, std::shared_ptr<UrsusEngine::ECS::Entity> entity, float dt)
{
	std::shared_ptr<UrsusEngine::ECS::Entity> player = m_PlayerEntity.lock();
	if (player == nullptr)
	{
		return true;
	}
	std::shared_ptr<UrsusEngine::ECS::SpriteComponent> playerSpriteComp = player->GetComponent<UrsusEngine::ECS::SpriteComponent>();
	float player_X = 0.f;
	float player_Y = 0.f;
	playerSpriteComp->GetPosition(player_X, player_Y);
	
	//Get components
	std::shared_ptr<PhysicComponent> physicComp = entity->GetComponent<PhysicComponent>();
	std::shared_ptr<UrsusEngine::ECS::SpriteComponent> spriteComp = entity->GetComponent<UrsusEngine::ECS::SpriteComponent>();
	std::shared_ptr<EnemyComponent> enemyComp = entity->GetComponent<EnemyComponent>();
	float rotationInDegree = 0.f;
	float Vel_X = 0.f;
	float Vel_Y = 0.f;
	float position_X = 0.f;
	float position_Y = 0.f;
	float speedPerSecond = 0.f;
	//cache data
	spriteComp->GetRotation(rotationInDegree);
	spriteComp->GetPosition(position_X, position_Y);
	physicComp->GetVelocity(Vel_X, Vel_Y);
	enemyComp->GetSpeedPerSecond(speedPerSecond);

	//Calculate distance
	float posToPlayerX = player_X - position_X;
	float posToPlayerY = player_Y - position_Y;
	float distance = std::sqrt((posToPlayerY * posToPlayerY) + (posToPlayerX * posToPlayerX));
	const float PI = 3.141592654f;
	//Move to player
	if (distance <= 200.0f)
	{
		Vel_X = (posToPlayerX / distance) * speedPerSecond;
		Vel_Y = (posToPlayerY / distance) * speedPerSecond;
		float rotation = std::atan2(player_Y - position_Y, player_X - position_X);
		rotationInDegree = rotation / PI * 180.0f;
	}
	//Random point for moving there
	else if ((std::rand() % 100) <= 1)
	{
		float randX = (std::rand() % 10) - 5.0f;
		float randY = (std::rand() % 10) - 5.0f;
		Vel_X = (randX / 5.0f) * speedPerSecond;
		Vel_Y = (randY / 5.0f) * speedPerSecond;
		float rotation = std::atan2(Vel_Y, Vel_X);
		rotationInDegree = rotation / PI * 180.0f;
	}

	spriteComp->SetRotation(rotationInDegree);

	physicComp->SetVelocity(Vel_X, Vel_Y);

	std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>> collisions;
	physicComp->GetCollisions(collisions);
	if (collisions.size() == 0)
	{
		//If there are no collisions the return
		return true;
	}
	//collision happened
	int hp = 0;
	enemyComp->GetHP(hp);
	//decrement hp
	hp--;
	//if hp is 0 then do not update
	if (hp == 0)
	{
		return false;
	}
	//set enemy hp
	enemyComp->SetHP(hp);
	return true;
}
