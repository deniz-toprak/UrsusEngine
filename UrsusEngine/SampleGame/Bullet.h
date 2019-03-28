#pragma once
#include "../UrsusEngine/Central/engine.h"

class Bullet
{
public:
	Bullet(std::shared_ptr<UrsusEngine::Sprite> sprite, const float max_X, const float max_Y);
	~Bullet();

	//Methods
public:

	void Init(const float X, const float Y, const float Rotation);
	void SetPosition(const float X, const float Y);
	void SetVelocity(const float X, const float Y);
	void SetRotation(const float Rotation);
	void Update(const float dt);

	std::shared_ptr<UrsusEngine::Sprite> GetSprite() { return m_Sprite; }

	const bool IsLifeTimeOver() { return m_LifeTimeInSeconds <= 0.f; }

private:
	void CalculateMovement(const float dt);

	//Members
private:
	//Player sprite
	std::shared_ptr<UrsusEngine::Sprite> m_Sprite;
	//Velocity of Bullet
	float m_Velocity_X = 0.f;
	float m_Velocity_Y = 0.f;
	//Actual Position and Rotation
	float m_X;
	float m_Y;
	//Window boundaries
	int m_Max_X;
	int m_Max_Y;
	//Bullet lifetime
	float m_LifeTimeInSeconds;
};