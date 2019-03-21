#pragma once

#include <string>
#include <vector>
#include "../Graphics/Window.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Window.h"
#include "Input.h"

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

		//Graphics
		void Draw();
		Sprite* CreateSprite(const char* url);
		void DestroySprite(Sprite* sprite);

		//Input handling
		bool IsKeyPressed(Key key);

	private:
		bool m_IsRunning;
		Window* m_Window;
		Input* m_Input;
		std::vector<Sprite*> m_Sprites;
	};
}
