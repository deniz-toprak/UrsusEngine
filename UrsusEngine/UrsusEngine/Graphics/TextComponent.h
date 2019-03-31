#pragma once

#include <memory>
#include <string>
#include "../Patterns/ECS/IComponent.h"


namespace sf
{
	class Text;
	class Font;
}


namespace UrsusEngine
{
	namespace ECS
	{
		class TextComponent : public IComponent
		{
		public:
			TextComponent();
			~TextComponent();

		public:
			void CreateText(std::string filePath);
			//return the text for the window
			const std::shared_ptr<sf::Text>& GetText() const { return m_Text; }
			//Move the text (relative to current position)
			void SetPosition(const float X, const float Y);
			//Return text position
			void GetPosition(float& X, float& Y);
			//set Colour
			void SetColour(const unsigned char red, const unsigned char green, const unsigned char blue);
			//with alpha
			void SetColour(const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alpha);
			//Set text size
			void SetSize(const int newSize);
			//Set the text
			void SetText(const std::string text);


		private:
			std::shared_ptr<sf::Text> m_Text;
			std::shared_ptr<sf::Font> m_Font;
		};
	}
}
