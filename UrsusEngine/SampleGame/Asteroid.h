#pragma once
#include "../UrsusEngine/Central/engine.h"
#include "Utils.h"

class Asteroid
{
public:
	Asteroid(UrsusEngine::Sprite* sprite, const float max_X, const float max_Y);
	~Asteroid();

	//Methods
public:
	void SetPosition(const float X, const float Y);
	void SetVelocity(const float X, const float Y);
	void SetRotation(const float Rotation);
	void Update(const float dt);

	UrsusEngine::Sprite* GetSprite() { return m_Sprite; }

private:
	void CalculateRotation(const float dt);
	void CalculateMovement(const float dt);

	//Members
private:
	//Player sprite
	UrsusEngine::Sprite* m_Sprite;
	//Velocity of asteroid
	float m_Velocity_X = 0.f;
	float m_Velocity_Y = 0.f;
	//Actual Position and Rotation
	RotateDirection m_RotateDirection;
	float m_RotationInDegree;
	float m_RotationPerSecond;
	float m_X;
	float m_Y;
	//Window boundaries
	int m_Max_X;
	int m_Max_Y;
};