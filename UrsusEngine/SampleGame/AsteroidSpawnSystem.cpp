#include "AsteroidSpawnSystem.h"
#include "PhysicComponent.h"
#include "AsteroidComponent.h"
#include "../UrsusEngine/Central/engine.h"

AsteroidSpawnSystem::AsteroidSpawnSystem()
{

}

AsteroidSpawnSystem::~AsteroidSpawnSystem()
{

}

bool AsteroidSpawnSystem::DoesEntityMatch(std::shared_ptr<UrsusEngine::ECS::Entity> entity)
{
	if (entity->HasComponent<AsteroidComponent>())
	{
		return true;
	}
	return false;
}

void AsteroidSpawnSystem::Update(UrsusEngine::Engine* engine, float dt)
{
	//Check if maximum of asteroids is already reached
	if (m_Entities.size() == m_MaxAsteroids)
	{
		return;
	}

	// check for spawn cooldown
	if (m_CurrentSpawnCD > 0.f)
	{
		m_CurrentSpawnCD -= dt;
		return;
	}

	m_CurrentSpawnCD = m_MaxSpawnCD;

	//Make entity with components
	std::shared_ptr<UrsusEngine::ECS::Entity> asteroidEntity = std::make_shared<UrsusEngine::ECS::Entity>();
	std::shared_ptr<UrsusEngine::ECS::SpriteComponent> asteroidSprite = asteroidEntity->AddComponent<UrsusEngine::ECS::SpriteComponent>();
	std::shared_ptr<PhysicComponent> asteroidPhysic = asteroidEntity->AddComponent<PhysicComponent>();
	std::shared_ptr<AsteroidComponent> asteroidComp = asteroidEntity->AddComponent<AsteroidComponent>();

	//Generate position values
	float x = float(std::rand() % m_Max_X);
	float y = float(std::rand() % m_Max_Y);
	//velocity
	float xVel = float((std::rand() % m_MaxVelocity * 2) - m_MaxVelocity);
	float yVel = float((std::rand() % m_MaxVelocity * 2) - m_MaxVelocity);
	float rotation = float(std::rand() % 360);

	asteroidSprite->CreateSprite("Resources/Asteroid_Graphics/asteroid1.png");
	asteroidSprite->SetPosition(x, y);
	asteroidSprite->SetRotation(rotation);
	asteroidPhysic->SetVelocity(xVel, yVel);
	asteroidPhysic->SetDamping(1.0f);
	asteroidPhysic->SetCollisionFlag(AsteroidCollisionFlag);
	engine->AddEntity(asteroidEntity);
	//Forget spawn protection for player as we gonna throw away this game anyway in
	//later commits for another smaple game
}

void AsteroidSpawnSystem::SetMaxAsteroids(const unsigned int maxAsteroid)
{
	m_MaxAsteroids = maxAsteroid;
}

void AsteroidSpawnSystem::SetSpawnCooldown(const float spawnCD)
{
	m_MaxSpawnCD = spawnCD;
}

void AsteroidSpawnSystem::SetMaxVelocity(const int velocity)
{
	m_MaxVelocity = velocity;
}

void AsteroidSpawnSystem::SetBoundaries(const int max_X, const int max_Y)
{
	m_Max_X = max_X;
	m_Max_Y = max_Y;
}
