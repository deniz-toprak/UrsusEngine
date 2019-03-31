#pragma once
#include "../UrsusEngine/Patterns/ECS/ISystem.h"
#include "../UrsusEngine/Graphics/SpriteComponent.h"

class AsteroidSpawnSystem : public UrsusEngine::ECS::ISystem
{
public:
	AsteroidSpawnSystem();
	~AsteroidSpawnSystem();

public:
	//ISystem
	virtual bool DoesEntityMatch(std::shared_ptr<UrsusEngine::ECS::Entity> entity) override;
	virtual void Update(UrsusEngine::Engine* engine, float dt) override;

	//Setting spawn params
	void SetMaxAsteroids(const unsigned int maxAsteroid);
	void SetSpawnCooldown(const float spawnCD);
	void SetMaxVelocity(const int velocity);
	void SetBoundaries(const int max_X, const int max_Y);

private:
	unsigned int m_MaxAsteroids = 0;
	float m_CurrentSpawnCD = 0.f;
	float m_MaxSpawnCD = 0.f;
	int m_Max_X = 0;
	int m_Max_Y = 0;
	int m_MaxVelocity = 0;
};