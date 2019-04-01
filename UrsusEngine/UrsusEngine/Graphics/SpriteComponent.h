#pragma once
#include <memory>
#include <string>
#include "../Patterns/ECS/IComponent.h"

//forward declare sprite and texture
namespace sf
{
	class Texture;
	class Sprite;
}

namespace UrsusEngine
{
	namespace ECS
	{
		class SpriteComponent : public IComponent
		{
		public:
			SpriteComponent();
			~SpriteComponent();

		public:
			void CreateSprite(std::string url);

			//Public getter for sprites
			const std::shared_ptr<sf::Sprite>& GetSprite() { return m_Sprite; }
			//Set Position
			void SetPosition(const float X, const float Y);
			//Set Rotation
			void SetRotation(const float Rot);
			//Get Position
			void GetPosition(float& X, float& Y);
			//Get Rotation
			void GetRotation(float& RotationInDegree);
			//
			void GetSize(unsigned int& Width, unsigned int& Height);
			//Woosh houdini confirmed
			void SetVisible(bool visible);
			//Woosh houdini busted
			void GetVisible(bool& visible);

			//Collision check with other sprite
			const bool IsCollidingWith(std::shared_ptr<SpriteComponent> otherSprite);
			//Collision check for fixed rectangle
			const bool IsCollidingWith(const float left, const float top, const float width, const float height);

		private:
			std::shared_ptr<sf::Sprite> m_Sprite = nullptr;
			//Houdini state
			bool m_Visible = true;
		};
	
	}
}