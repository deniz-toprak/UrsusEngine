#include "PhysicSystem.h"
#include "../UrsusEngine/Central/engine.h"
#include "../UrsusEngine/Patterns/ECS/Entity.h"
#include "../UrsusEngine/Graphics/SpriteComponent.h"
#include "PhysicComponent.h"

PhysicSystem::PhysicSystem()
{

}

PhysicSystem::~PhysicSystem()
{

}


void PhysicSystem::SetBoundaries(const float max_X, const float max_Y)
{
	m_Max_X = max_X;
	m_Max_Y = max_Y;
}

bool PhysicSystem::DoesEntityMatch(std::shared_ptr<UrsusEngine::ECS::Entity> entity)
{
	if (entity->HasComponent<UrsusEngine::ECS::SpriteComponent>() && entity->HasComponent<PhysicComponent>())
	{
		return true;
	}
	return false;
}

void PhysicSystem::Update(UrsusEngine::Engine* engine, float dt)
{
	for (std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>>::iterator entityItr = m_Entities.begin(); entityItr != m_Entities.end();)
	{
		std::shared_ptr<UrsusEngine::ECS::Entity> entity = *entityItr;
		UpdateSingleEntityPosition(entity, dt);
		++entityItr;
	}
	
	for (std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>>::iterator entityItr = m_Entities.begin(); entityItr != m_Entities.end();)
	{
		std::shared_ptr<UrsusEngine::ECS::Entity> entity = *entityItr;
		UpdateSingleEntityCollision(entity, dt);
		++entityItr;
	}
}

void inline PhysicSystem::UpdateSingleEntityPosition(std::shared_ptr<UrsusEngine::ECS::Entity> entity, float dt)
{
	std::shared_ptr<UrsusEngine::ECS::SpriteComponent> spriteComp = entity->GetComponent<UrsusEngine::ECS::SpriteComponent>();
	std::shared_ptr<PhysicComponent> physicsComp = entity->GetComponent<PhysicComponent>();
	float X, Y = 0.f;
	float Vel_X, Vel_Y = 0.f;
	float damping = 0.f;
	spriteComp->GetPosition(X, Y);
	physicsComp->GetVelocity(Vel_X, Vel_Y);
	physicsComp->GetDamping(damping);

	Vel_X *= damping;
	Vel_Y *= damping;
	if (Vel_X < 0.1f && Vel_X > -0.1f)
	{
		Vel_X = 0.f;
	}
	if (Vel_Y < 0.1f && Vel_Y > -0.1f)
	{
		Vel_Y = 0.f;
	}
	physicsComp->SetVelocity(Vel_X, Vel_Y);

	if (Vel_X == 0.f && Vel_Y == 0.f)
	{
		return;
	}

	X += Vel_X * dt;
	Y += Vel_Y * dt;

	if (X < 0)
	{
		X = X + m_Max_X;
	}
	else if (X > m_Max_X)
	{
		X = X - m_Max_X;
	}

	if (Y < 0)
	{
		Y = Y + m_Max_Y;
	}
	else if (Y > m_Max_Y)
	{
		Y = Y - m_Max_Y;
	}

	spriteComp->SetPosition(X, Y);
}

void inline PhysicSystem::UpdateSingleEntityCollision(std::shared_ptr<UrsusEngine::ECS::Entity> entity, float dt)
{
	std::shared_ptr<UrsusEngine::ECS::SpriteComponent> spriteComp = entity->GetComponent<UrsusEngine::ECS::SpriteComponent>();
	std::shared_ptr<PhysicComponent> physicsComp = entity->GetComponent<PhysicComponent>();

	std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>> collisions;

	for (std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>>::iterator otherEntityItr = m_Entities.begin(); otherEntityItr != m_Entities.end();)
	{
		std::shared_ptr<UrsusEngine::ECS::Entity> otherEntity = *otherEntityItr;
		if (entity == otherEntity)
		{
			++otherEntityItr;
			continue;
		}

		std::shared_ptr<UrsusEngine::ECS::SpriteComponent>  otherSpriteComp = otherEntity->GetComponent<UrsusEngine::ECS::SpriteComponent>();
		std::shared_ptr<PhysicComponent> otherPhysicsComp = otherEntity->GetComponent<PhysicComponent>();
		int otherCollisionFlag = 0;
		otherPhysicsComp->GetCollisionFlag(otherCollisionFlag);
		if (physicsComp->CanCollide(otherCollisionFlag) && spriteComp->IsCollidingWith(otherSpriteComp))
		{
			collisions.push_back(otherEntity);
		}
		++otherEntityItr;
	}

	physicsComp->SetCollisions(collisions);
}