#pragma once
#include "../UrsusEngine/Patterns/ECS/ISystem.h"

class PlayerSystem : public UrsusEngine::ECS::ISystem
{
public:
	PlayerSystem();
	~PlayerSystem();

public:
	
	//ISystem
	virtual bool DoesEntityMatch(std::shared_ptr<UrsusEngine::ECS::Entity> entity) override;
	virtual void Update(UrsusEngine::Engine* engine, float dt) override;

private:
	bool inline UpdateEntity(UrsusEngine::Engine* engine, std::shared_ptr<UrsusEngine::ECS::Entity> entity, const float dt);

	private:
		//Chached view pos values
		float m_Camera_X = 0.f;
		float m_Camera_Y = 0.f;
};