#pragma once
#include "../UrsusEngine/Patterns/ECS/IComponent.h"

class PlayerComponent : public UrsusEngine::ECS::IComponent
{
public:
	PlayerComponent();
	~PlayerComponent();

public:
	void GetSpeedPerSecond(float& speedPerSecond);
	void SetSpeedPerSecond(const float speedPerSecond);

	void GetRotationPerSecond(float& rotationPerSecond);
	void SetRotationPerSecond(const float rotationPerSecond);

	void GetBulletSpeedPerSecond(float& bulletSpeedPerSecond);
	void SetBulletSpeedPerSecond(const float bulletSpeedPerSecond);

	void GetBulletSpawnCooldown(float& spawnCD);
	void SetBulletSpawnCooldown(const float spawnCD);

	void GetMaxBulletSpawnCooldown(float& maxSpawnCD);
	void SetMaxBulletSpawnCooldown(const float maxSpawnCD);

	void GetHP(int& hp);
	void SetHP(int hp);

	void GetAmmo(int& ammo);
	void SetAmmo(int ammo);

	void GetHitCooldown(float& hitCooldown);
	void SetHitCooldown(float hitCooldown);

private:
	//Movement
	float m_SpeedPerSecond = 0.f;
	float m_RotationPerSecond = 0.f;

	//Gunzz
	float m_BulletSpeedPerSecond = 0.f;
	float m_CurrentBulletSpawnCD = 0.f;
	float m_MaxBulletSpawnCD = 0.f;
	int m_HP = 0;
	int m_Ammo = 0;

	//Collision
	float m_HitCooldown = 0;
};