#pragma once
#include "../UrsusEngine/Patterns/ECS/IComponent.h"

class ScoreComponent : public UrsusEngine::ECS::IComponent
{
public:
	ScoreComponent();
	~ScoreComponent();

public:
	void GetScore(int& score);
	void SetScore(const int score);

private:
	int m_Score = 0;
};