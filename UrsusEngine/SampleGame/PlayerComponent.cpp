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


void PlayerComponent::GetHP(int& hp)
{
	hp = m_HP;
}

void PlayerComponent::SetHP(int hp)
{
	m_HP = hp;
}

void PlayerComponent::GetAmmo(int& ammo)
{
	ammo = m_Ammo;
}

void PlayerComponent::SetAmmo(int ammo)
{
	m_Ammo = ammo;
}

void PlayerComponent::GetHitCooldown(float& hitCooldown)
{
	hitCooldown = m_HitCooldown;
}

void PlayerComponent::SetHitCooldown(float hitCooldown)
{
	m_HitCooldown = hitCooldown;
}