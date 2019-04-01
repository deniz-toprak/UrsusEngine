#pragma once
#include "../UrsusEngine/Patterns/ECS/IComponent.h"

class AmmoComponent : public UrsusEngine::ECS::IComponent
{
public:
	AmmoComponent(){}
	~AmmoComponent(){}

public:
	void GetAmmo(int& ammo) { ammo = m_Ammo; }
	void SetAmmo(int ammo) { m_Ammo = ammo; }

private:
	int m_Ammo = 0;
};