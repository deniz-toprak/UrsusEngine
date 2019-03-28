#include "Bullet.h"

Bullet::Bullet(UrsusEngine::Sprite* sprite, const float max_X, const float max_Y)
{
	m_Sprite = sprite;
	m_Max_X = max_X;
	m_Max_Y = max_Y;

	//Default values

	m_X = 0.f;
	m_Y = 0.f;
	m_LifeTimeInSeconds = 3.5f;
}

Bullet::~Bullet()
{
	//Sprite is deleted by engine
}

void Bullet::Init(const float X, const float Y, const float Rotation)
{
	const float PI = 3.141592654f;
	const float speedPerSecond = 200.f;
	float rotationInRadian = (Rotation+90) * PI / 180.f;

	m_Velocity_X = sin(rotationInRadian) * speedPerSecond;
	m_Velocity_Y = -cos(rotationInRadian) * speedPerSecond;
	m_X = X;
	m_Y = Y;
	m_Sprite->SetPosition(m_X, m_Y);
}

void Bullet::SetPosition(const float X, const float Y)
{
	m_Sprite->SetPosition(X, Y);
	m_X = X;
	m_Y = Y;
}

void Bullet::SetRotation(const float Rotation)
{
	m_Sprite->SetRotation(Rotation);
}

void Bullet::SetVelocity(const float X, const float Y)
{
	m_Velocity_X = X;
	m_Velocity_Y = Y;
}


void Bullet::Update(const float dt)
{
	CalculateMovement(dt);

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
	m_LifeTimeInSeconds -= dt;
}

void Bullet::CalculateMovement(const float dt)
{
	m_X += m_Velocity_X * dt;
	m_Y += m_Velocity_Y * dt;
}