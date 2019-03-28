#pragma once
#include <string>
#include <memory>

namespace sf
{
	class Text;
	class Font;
}

namespace UrsusEngine
{
	class Text
	{
	public:
		Text(const std::string fontURL);
		~Text();

	public:
		//Set text
		void SetText(const std::string text);

		//Set character size
		void SetSize(const int size);

		//Set colour - and yes it is COLOUR NOT COLOR. 
		//Learn british english ffs
		//@TO-DO: Make new data type Colour which consists of rbga
		void SetColour(const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alpha = 255);
		
		//Get Text for render
		const std::shared_ptr<sf::Text> GetText() { return m_Text; }

		//Set Text position
		void SetPosition(const float X, const float Y);


	private:
		std::shared_ptr<sf::Text> m_Text;
		std::shared_ptr<sf::Font> m_Font;

	};
}