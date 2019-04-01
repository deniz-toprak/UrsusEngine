#pragma once
#include "../UrsusEngine/Patterns/ECS/IComponent.h"

class HealthComponent : public UrsusEngine::ECS::IComponent
{
public:
	HealthComponent(){}
	~HealthComponent(){}

public:
	void GetHealth(int& health) { health = m_Health; }
	void SetHealth(int health) { m_Health = health; }

private:
	int m_Health = 0;
};