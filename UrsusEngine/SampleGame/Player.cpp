#include "Player.h"
#include <algorithm>

Player::Player(std::shared_ptr<UrsusEngine::Sprite> sprite, const float max_X, const float max_Y)
{
	m_Sprite = sprite;
	m_Max_X = max_X;
	m_Max_Y = max_Y;

	//Default values
	m_Accelerate = false;
	m_RotateDirection = RotateDirection::RotateDirectionNone;
	m_RotationInDegree = 0.f;
	m_X = 0.f;
	m_Y = 0.f;

}

Player::~Player()
{
	//Sprite is deleted by engine
}


void Player::SetPosition(const float X, const float Y)
{
	m_Sprite->SetPosition(X, Y);
	m_X = X;
	m_Y = Y;
}

void Player::SetRotation(const float Rot)
{
	m_Sprite->SetRotation(Rot);
}

void Player::SetVelocity(const float X, const float Y)
{
	m_Velocity_X = X;
	m_Velocity_Y = Y;
}

void Player::HandleInput(std::shared_ptr<UrsusEngine::Engine> engine)
{
	bool isDPressed = engine->IsKeyPressed(UrsusEngine::Key::D);
	bool isAPressed = engine->IsKeyPressed(UrsusEngine::Key::A);
	if (isDPressed && !isAPressed)
	{
		m_RotateDirection = RotateDirection::RotateDirectionRight;
	}
	else if (isAPressed && !isDPressed)
	{
		m_RotateDirection = RotateDirection::RotateDirectionLeft;
	}
	else if (isDPressed && isAPressed)
	{
		m_RotateDirection = RotateDirection::RotateDirectionNone;
	}
	else
	{
		m_RotateDirection = RotateDirection::RotateDirectionNone;
	}

	m_Accelerate = engine->IsKeyPressed(UrsusEngine::Key::W);
	m_IsShooting = engine->IsKeyPressed(UrsusEngine::Key::Space) && m_ShootCooldown == 0.f;
}

void Player::Update(const float dt)
{
	if (m_ShootCooldown > 0.f)
	{
		m_ShootCooldown = std::max(0.f, m_ShootCooldown - dt);
	}

	if (m_IsShooting)
	{
		m_ShootCooldown = 0.1f;
	}

	CalculateRotation(dt);
	CalculateMovement(dt);

	m_Sprite->SetRotation(m_RotationInDegree);
	if (m_X < 0)
	{
		m_X = m_X + m_Max_X;
	}
	else if (m_X > m_Max_X)
	{
		m_X = m_X - m_Max_X;
	}
	if (m_Y < 0)
	{
		m_Y = m_Y + m_Max_Y;
	}
	else if (m_Y > m_Max_Y)
	{
		m_Y = m_Y - m_Max_Y;
	}
	m_Sprite->SetPosition(m_X, m_Y);
}

void Player::CalculateRotation(const float dt)
{
	if (m_RotateDirection == RotateDirection::RotateDirectionNone)
	{
		return;
	}
	const float rotationPerSecond = 300.f;

	if (m_RotateDirection == RotateDirection::RotateDirectionLeft)
	{
		m_RotationInDegree -= rotationPerSecond * dt;
	}
	else
	{
		m_RotationInDegree += rotationPerSecond * dt;
	}

	if (m_RotationInDegree > 360.f)
	{
		m_RotationInDegree = m_RotationInDegree - 360.f;
	}
	else if (m_RotationInDegree < 360.f)
	{
		m_RotationInDegree = m_RotationInDegree + 360.f;
	}
}

void Player::CalculateMovement(const float dt)
{
	const float inertia = 0.98f;
	const float speedPerSecond = 10.f;

	float x = 0.f;
	float y = 0.f;
	const float PI = 3.141592654f;
	float rotation = (m_RotationInDegree + 90.f) * PI / 180.f;
	if (m_Accelerate)
	{
		x = sin(rotation)  * speedPerSecond;
		y = -cos(rotation) * speedPerSecond;

	}

	m_Velocity_X = (m_Velocity_X + x) * inertia;
	m_Velocity_Y = (m_Velocity_Y + y) * inertia;

	m_X += m_Velocity_X * dt;
	m_Y += m_Velocity_Y * dt;
}