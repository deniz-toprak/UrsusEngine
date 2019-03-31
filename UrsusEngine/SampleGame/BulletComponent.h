#pragma once
#include "../UrsusEngine/Patterns/ECS/IComponent.h"

class BulletComponent : public UrsusEngine::ECS::IComponent
{
public:
	BulletComponent();
	~BulletComponent();

public:
	void SetLifeTime(const float lifeTime);
	void GetLifeTime(float& lifeTime);

private:
	float m_LifeTime = 0.f;
};