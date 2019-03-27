#pragma once
#include "../UrsusEngine/Central/engine.h"
#include "Utils.h"

class Player
{
public:
	Player(UrsusEngine::Sprite* sprite, const float max_X, const float max_Y);
	~Player();

	//Methods
public:
	void SetPosition(const float X, const float Y);
	void SetRotation(const float Rot);
	void SetVelocity(const float X, const float Y);
	void HandleInput(UrsusEngine::Engine* engine);
	void Update(const float dt);
	float GetX() const { return m_X; }
	float GetY() const { return m_Y; }

	UrsusEngine::Sprite* GetSprite() { return m_Sprite; }

private:
	void CalculateRotation(const float dt);
	void CalculateMovement(const float dt);

	//Members
private:
	//Player sprite
	UrsusEngine::Sprite* m_Sprite;
	//Velocity of player
	float m_Velocity_X = 0.f;
	float m_Velocity_Y = 0.f;
	//To seperate Input and Update
	bool m_Accelerate;
	RotateDirection m_RotateDirection;
	//Actual Position and Rotation
	float m_RotationInDegree;
	float m_X;
	float m_Y;
	//Window boundaries
	int m_Max_X;
	int m_Max_Y;
};