#include "PlayerSystem.h"
#include "PlayerComponent.h"
#include "../UrsusEngine/Central/engine.h"
#include <algorithm>
#include "../UrsusEngine/Graphics/SpriteComponent.h"
#include "PhysicComponent.h"
#include "BulletComponent.h"
#include "ScoreEvent.h"
#include "Utils.h"
//#include "../UrsusEngine/Central/EventManager.h"


PlayerSystem::PlayerSystem()
{

}

PlayerSystem::~PlayerSystem()
{

}

bool PlayerSystem::DoesEntityMatch(std::shared_ptr<UrsusEngine::ECS::Entity> entity)
{
	if (entity->HasComponent<PlayerComponent>())
	{
		return true;
	}
	return false;
}

void PlayerSystem::Update(UrsusEngine::Engine* engine, float dt)
{
	if (m_Entities.size() == 0)
	{
		return;
	}
	//Copy all entitites so that we can iterate through all without worrying about them getting deleted
	//during the loop
	std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>> copiedEntities = m_Entities;

	for (std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>>::iterator entityItr = copiedEntities.begin(); entityItr != copiedEntities.end();)
	{
		std::shared_ptr<UrsusEngine::ECS::Entity> entity = *entityItr;
		//if the entity should be removed
		if (!UpdateEntity(engine, entity, dt))
		{
			//Remove the entity from the engine
			engine->RemoveEntity(entity);

			//throw dead event
			std::shared_ptr<DeadEvent> event = std::make_shared<DeadEvent>();
			UrsusEngine::EventManager::GetInstance().PushEvent(event);
		}
		++entityItr;
	}
	engine->SetViewCenter(m_Camera_X, m_Camera_Y);
}

bool PlayerSystem::UpdateEntity(UrsusEngine::Engine* engine, std::shared_ptr<UrsusEngine::ECS::Entity> entity, const float dt)
{
	//get the components we'll use
	std::shared_ptr<PlayerComponent> playerComp = entity->GetComponent<PlayerComponent>();
	std::shared_ptr<PhysicComponent> physicComp = entity->GetComponent<PhysicComponent>();
	std::shared_ptr<UrsusEngine::ECS::SpriteComponent> spriteComp = entity->GetComponent<UrsusEngine::ECS::SpriteComponent>();
	//get the data of the components
	float speedPerSecond = 0.f;
	float Vel_X, Vel_Y = 0.f;
	float rotationInDegree = 0.f;
	float bulletSpawnCD = 0.f;
	float maxBulletSpawnCD = 0.f;
	float bulletSpeedPerSecond = 0.f;
	float player_X, player_Y = 0.f;
	float rotationPerSecond;
	const float PI = 3.141592654f;
	//Get physicComponent variables
	physicComp->GetVelocity(Vel_X, Vel_Y);
	//Get playerComponent variables
	playerComp->GetSpeedPerSecond(speedPerSecond);
	playerComp->GetBulletSpawnCooldown(bulletSpawnCD);
	playerComp->GetMaxBulletSpawnCooldown(maxBulletSpawnCD);
	playerComp->GetBulletSpeedPerSecond(bulletSpeedPerSecond);
	playerComp->GetRotationPerSecond(rotationPerSecond);
	//Get spriteComponent variables
	spriteComp->GetRotation(rotationInDegree);
	spriteComp->GetPosition(player_X, player_Y);
	m_Camera_X = player_X;
	m_Camera_Y = player_Y;

	float cursorX, cursorY = 0.f;
	engine->GetCursorPosition(cursorX, cursorY);
	float rotationInRadians = std::atan2(cursorY - player_Y, cursorX - player_X);
	//calculate rotation in radians
	rotationInDegree = rotationInRadians / PI * 180.0f;
	//Set rotation
	spriteComp->SetRotation(rotationInDegree);
	//Update velocity
	if (engine->IsKeyPressed(UrsusEngine::Key::W))
	{
		Vel_Y = -speedPerSecond;
	}
	else if (engine->IsKeyPressed(UrsusEngine::Key::S))
	{
		Vel_Y = speedPerSecond;
	}
	if (engine->IsKeyPressed(UrsusEngine::Key::A))
	{
		Vel_X = -speedPerSecond;
	}
	else if (engine->IsKeyPressed(UrsusEngine::Key::D))
	{
		Vel_X = speedPerSecond;
	}

	physicComp->SetVelocity(Vel_X, Vel_Y);


	if (bulletSpawnCD > 0)
	{
		bulletSpawnCD = std::max(0.f, bulletSpawnCD - dt);
	}

	if (engine->IsMousePressed(UrsusEngine::MouseLeft) && bulletSpawnCD <= 0.f)
	{
		//reset cooldown
		bulletSpawnCD = maxBulletSpawnCD;

		float shootRotationInRadians = (rotationInDegree + 90) * PI / 180.f;
		float bulletVelocity_X = sin(shootRotationInRadians) * bulletSpeedPerSecond;
		float bulletVelocity_Y = -cos(shootRotationInRadians) * bulletSpeedPerSecond;


		std::shared_ptr<UrsusEngine::ECS::Entity> bulletEntity = std::make_shared<UrsusEngine::ECS::Entity>();
		std::shared_ptr<UrsusEngine::ECS::SpriteComponent> bulletSprite = bulletEntity->AddComponent<UrsusEngine::ECS::SpriteComponent>();
		std::shared_ptr<PhysicComponent> bulletPhysics = bulletEntity->AddComponent<PhysicComponent>();
		std::shared_ptr<BulletComponent> bulletComp = bulletEntity->AddComponent<BulletComponent>();

		bulletSprite->CreateSprite("Resources/Asteroid_Graphics/Bullet.png");
		bulletSprite->SetPosition(player_X, player_Y);
		bulletPhysics->SetVelocity(bulletVelocity_X, bulletVelocity_Y);
		bulletPhysics->SetTargetFlag(EnemyCollisionFlag);
		bulletPhysics->SetCollisionFlag(BulletCollisionFlag);
		bulletPhysics->SetDamping(1.0f);
		bulletComp->SetLifeTime(2.0f);

		engine->AddEntity(bulletEntity);
	}
	playerComp->SetBulletSpawnCooldown(bulletSpawnCD);
	std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>> collisions;
	physicComp->GetCollisions(collisions);
	if (collisions.size() == 0)
	{
		return true;
	}
	return false;
}