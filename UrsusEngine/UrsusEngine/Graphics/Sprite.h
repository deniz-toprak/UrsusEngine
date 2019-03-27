#pragma once

//forward declare sprite and texture
namespace sf
{
	class Texture;
	class Sprite;
}

namespace UrsusEngine
{
	class Sprite
	{
	public:
		Sprite(const char* url);
		~Sprite();

	public:
		//Public getter for sprites
		const sf::Sprite* GetSprite() { return m_Sprite; }

		//Move sprite method
		void Move(const float X, const float Y);
		void SetPosition(const float X, const float Y);
		void SetRotation(const float Rot);

		//Collision check with other sprite
		const bool IsCollidingWith(Sprite* otherSprite);
		const bool IsCollidingWith(const float left, const float top, const float width, const float height);

	private:
		sf::Texture* m_Texture;
		sf::Sprite* m_Sprite;

	};
}