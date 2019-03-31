#pragma once

#include <memory>
#include "../UrsusEngine/Patterns/ECS/ISystem.h"


//Forward declare entity
namespace UrsusEngine
{
	class Engine;

	namespace ECS
	{
		class Entity;
	}
}

class PhysicSystem : public UrsusEngine::ECS::ISystem
{
public:
	PhysicSystem();
	~PhysicSystem();

	//Methods
public:
	//ISystem override
	virtual bool DoesEntityMatch(std::shared_ptr<UrsusEngine::ECS::Entity> entity) override;
	virtual void Update(UrsusEngine::Engine* engine, float dt) override;

private:
	void inline UpdateSingleEntityPosition(std::shared_ptr<UrsusEngine::ECS::Entity> entity, float dt);
	void inline UpdateSingleEntityCollision(std::shared_ptr<UrsusEngine::ECS::Entity> entity, float dt);

private:
	std::shared_ptr<UrsusEngine::ECS::Entity> m_LevelEntity;

};