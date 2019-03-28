#include "Score.h"

Score::Score(std::shared_ptr<UrsusEngine::Text> text)
{
	m_Text = text;
	m_Text->SetSize(24);
	m_Text->SetColour(255, 255, 255);
	SetScore(0);
}

Score::~Score()
{
}

void Score::SetPosition(const float X, const float Y)
{
	m_Text->SetPosition(X, Y);
}

void Score::SetScore(const int Score)
{
	m_Score = Score;
	std::string scoreText = "Score: " + std::to_string(m_Score);
	m_Text->SetText(scoreText);
}

void Score::AddScore(const int AddToScore)
{
	SetScore(m_Score + AddToScore);
}
