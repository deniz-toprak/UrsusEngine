#include "Time.h"
#include <SFML/System.hpp>

using namespace UrsusEngine;

Time::Time()
{
	m_Clock = std::make_unique<sf::Clock>();
	m_DeltaTime = 0.f;
	
}

Time::~Time()
{

}

void Time::Restart()
{
	m_DeltaTime = m_Clock->restart().asSeconds();
}

const float Time::GetElapsedTimeAsSeconds()
{
	return m_DeltaTime;
}