#pragma once
#include <memory>

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
		Sprite(std::shared_ptr<sf::Texture> texture);
		~Sprite();

	public:
		//Public getter for sprites
		const std::shared_ptr<sf::Sprite> GetSprite() { return m_Sprite; }

		//Move sprite method
		void Move(const float X, const float Y);
		void SetPosition(const float X, const float Y);
		void SetRotation(const float Rot);

		//Collision check with other sprite
		const bool IsCollidingWith(std::shared_ptr<Sprite> otherSprite);
		const bool IsCollidingWith(const float left, const float top, const float width, const float height);

	private:
		std::shared_ptr<sf::Sprite> m_Sprite;

	};
}