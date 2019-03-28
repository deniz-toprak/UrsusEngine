#pragma once
#include "../UrsusEngine/Graphics/Text.h"

class Score
{

public:
	Score(UrsusEngine::Text* text);
	~Score();

	//Methods
public:
	void SetPosition(const float X, const float Y);
	void SetScore(const int Score);
	void AddScore(const int AddToScore);

	UrsusEngine::Text* GetText() { return m_Text; }

	//Members
private:
	UrsusEngine::Text* m_Text;

	float m_X;
	float m_Y;

	int m_Score;
};