#include "Asteroid.h"
#include <random>
#include <ctime>

Asteroid::Asteroid(UrsusEngine::Sprite* sprite, const float max_X, const float max_Y)
{
	m_Sprite = sprite;
	m_Max_X = max_X;
	m_Max_Y = max_Y;

	//Default values

	m_RotationInDegree = 0.f;
	m_X = 0.f;
	m_Y = 0.f;

	std::srand(std::time(nullptr));
	if (((std::rand() % 10 *2) - 10) > 0)
	{
		m_RotateDirection = RotateDirection::RotateDirectionRight;
	}
	else
	{
		m_RotateDirection = RotateDirection::RotateDirectionLeft;
	}

	//Range 250 - 350
	m_RotationPerSecond = (std::rand() % 100 * 2) - 100;
}

Asteroid::~Asteroid()
{
	//Sprite is deleted by engine
}


void Asteroid::SetPosition(const float X, const float Y)
{
	m_Sprite->SetPosition(X, Y);
	m_X = X;
	m_Y = Y;
}

void Asteroid::SetRotation(const float Rotation)
{
	m_Sprite->SetRotation(Rotation);
}

void Asteroid::SetVelocity(const float X, const float Y)
{
	m_Velocity_X = X;
	m_Velocity_Y = Y;
}


void Asteroid::Update(const float dt)
{
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

void Asteroid::CalculateRotation(const float dt)
{

	if (m_RotateDirection == RotateDirection::RotateDirectionLeft)
	{
		m_RotationInDegree -= m_RotationPerSecond * dt;
	}
	else
	{
		m_RotationInDegree += m_RotationPerSecond * dt;
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

void Asteroid::CalculateMovement(const float dt)
{
	m_X += m_Velocity_X * dt;
	m_Y += m_Velocity_Y * dt;
}