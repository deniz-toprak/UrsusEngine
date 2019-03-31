#pragma once
#include "../UrsusEngine/Patterns/ECS/IComponent.h"
#include <vector>
#include <memory>

//forward declare
namespace UrsusEngine
{
	namespace ECS
	{
		class Entity;
	}
}

static const unsigned char AsteroidCollisionFlag = 1 << 0;
static const unsigned char BulletCollisionFlag = 1 << 1;

class PhysicComponent : public UrsusEngine::ECS::IComponent
{
public:
	PhysicComponent();
	~PhysicComponent();
	
	//Methods
public:
	void SetVelocity(const float X, const float Y);
	void GetVelocity(float& X, float& Y) const;
	void SetDamping(const float damping);
	void GetDamping(float& damping) const;
	void SetCollisions(std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>>& collisions);
	void GetCollisions(std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>>& collisions) const;

	void SetCollisionFlag(int flag);
	void GetCollisionFlag(int& flag) const;
	void SetTargetFlag(int flag);

	bool CanCollide(int& flag);

	//Members
private:
	float m_Velocity_X = 0.f;
	float m_Velocity_Y = 0.f;
	
	float m_Damping = 0.f;

	//For filtering collisions
	int m_CollisionFlag = 0;
	int m_TargetFlag = 0;

	//Current collisions
	std::vector<std::shared_ptr<UrsusEngine::ECS::Entity>> m_Collisions;
};