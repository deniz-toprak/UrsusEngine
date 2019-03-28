#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../Graphics/Window.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Text.h"
#include "../Graphics/Window.h"
#include "InputHelper.h"
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
		std::shared_ptr<Sprite> CreateSprite(const char* url);
		std::shared_ptr<Text> CreateText(const char* url);

		//Input handling
		bool IsKeyPressed(Key key);

		//Time
		const float GetElapsedTimeAsSeconds();

	private:
		//Window handling
		bool m_IsRunning;
		std::unique_ptr<Window> m_Window;
	

		//Graphics
		std::vector<std::shared_ptr<Sprite>> m_Sprites;
		std::vector<std::shared_ptr<Text>> m_Texts;

		//Time handling
		std::unique_ptr<Time> m_Time;
	};
}
