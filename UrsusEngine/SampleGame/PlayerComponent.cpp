#include "PlayerComponent.h"

PlayerComponent::PlayerComponent()
{

}

PlayerComponent::~PlayerComponent()
{

}

void PlayerComponent::GetSpeedPerSecond(float& speedPerSecond)
{
	speedPerSecond = m_SpeedPerSecond;
}

void PlayerComponent::SetSpeedPerSecond(const float speedPerSecond)
{
	m_SpeedPerSecond = speedPerSecond;
}

void PlayerComponent::GetRotationPerSecond(float& rotationPerSecond)
{
	rotationPerSecond = m_RotationPerSecond;
}

void PlayerComponent::SetRotationPerSecond(const float rotationPerSecond)
{
	m_RotationPerSecond = rotationPerSecond;
}

void PlayerComponent::GetBulletSpeedPerSecond(float& bulletSpeedPerSecond)
{
	bulletSpeedPerSecond = m_BulletSpeedPerSecond;
}

void PlayerComponent::SetBulletSpeedPerSecond(const float bulletSpeedPerSecond)
{
	m_BulletSpeedPerSecond = bulletSpeedPerSecond;
}

void PlayerComponent::GetBulletSpawnCooldown(float& spawnCD)
{
	spawnCD = m_CurrentBulletSpawnCD;
}

void PlayerComponent::SetBulletSpawnCooldown(const float spawnCD)
{
	m_CurrentBulletSpawnCD = spawnCD;
}

void PlayerComponent::GetMaxBulletSpawnCooldown(float& maxSpawnCD)
{
	maxSpawnCD = m_MaxBulletSpawnCD;
}

void PlayerComponent::SetMaxBulletSpawnCooldown(const float maxSpawnCD)
{
	m_MaxBulletSpawnCD = maxSpawnCD;
}
