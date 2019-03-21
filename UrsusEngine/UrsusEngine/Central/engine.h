#pragma once

#include <string>
#include <vector>
#include "../Graphics/Window.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Window.h"

namespace UrsusEngine
{
	class Engine
	{
	public:
		Engine(const int width, const int height, const std::string title, const bool fullscreen);
		~Engine();

	public:
		const bool IsRunning() const { return m_IsRunning; }
		void Update();

		void Draw();
		Sprite* CreateSprite(const char* url);
		void DestroySprite(Sprite* sprite);

	private:
		bool m_IsRunning;
		Window* m_Window;
		std::vector<Sprite*> m_Sprites;
	};
}
