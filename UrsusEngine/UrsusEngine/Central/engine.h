#pragma once

#include <string>
#include <vector>
#include "../Graphics/Window.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Text.h"
#include "../Graphics/Window.h"
#include "Input.h"
#include "Time.h"

namespace UrsusEngine
{
	class Engine
	{
	public:
		Engine(const int width, const int height, const std::string title, const bool fullscreen);
		~Engine();

	public:
		//General
		const bool IsRunning() const { return m_IsRunning; }
		void Update();

		//Graphics & Window
		void Draw();

		//Sprite handling
		Sprite* CreateSprite(const char* url);
		void DestroySprite(Sprite* sprite);

		//Text handling
		Text* CreateText(const char* url);
		void DestroyText(Text* text);


		//Input handling
		bool IsKeyPressed(Key key);

		//Time
		const float GetElapsedTimeAsSeconds();

	private:
		//Window handling
		bool m_IsRunning;
		Window* m_Window;
		
		//Input
		Input* m_Input;

		//Graphics
		std::vector<Sprite*> m_Sprites;
		std::vector<Text*> m_Texts;

		//Time handling
		Time* m_Time;
	};
}
