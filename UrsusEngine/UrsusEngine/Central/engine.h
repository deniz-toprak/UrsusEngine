#pragma once

class Engine
{
public:
	Engine();
	~Engine();

public:
	const bool isRunning() const { return m_IsRunning; }

private:
	bool m_IsRunning;
};