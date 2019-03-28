#pragma once
#include <memory>

namespace sf
{
	class Clock;
}

namespace UrsusEngine
{
	class Time
	{
	public:
		Time();
		~Time();

	public:
		void Restart();
		const float GetElapsedTimeAsSeconds();

	private:
		std::unique_ptr<sf::Clock> m_Clock;
		float m_DeltaTime;
	};
}