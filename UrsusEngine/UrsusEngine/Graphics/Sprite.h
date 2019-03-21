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

	private:
		sf::Texture* m_Texture;
		sf::Sprite* m_Sprite;

	};
}