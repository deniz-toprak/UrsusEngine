#include "EnemyComponent.h"

EnemyComponent::EnemyComponent()
{

}

EnemyComponent::~EnemyComponent()
{

}

void EnemyComponent::GetSpeedPerSecond(float& speedPerSecond)
{
	speedPerSecond = m_SpeedPerSecond;
}

void EnemyComponent::SetSpeedPerSecond(float speedPerSecond)
{
	m_SpeedPerSecond = speedPerSecond;
}

void EnemyComponent::GetHP(int& hp)
{
	hp = m_HP;
}

void EnemyComponent::SetHP(int hp)
{
	m_HP = hp;
}
