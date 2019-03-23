#include "Time.h"
#include <SFML/System.hpp>

using namespace UrsusEngine;

Time::Time()
{
	m_Clock = new sf::Clock();
	m_DeltaTime = 0.f;
	
}

Time::~Time()
{
	delete m_Clock;
}

void Time::Restart()
{
	m_DeltaTime = m_Clock->restart().asSeconds();
}

const float Time::GetElapsedTimeAsSeconds()
{
	return m_DeltaTime;
}