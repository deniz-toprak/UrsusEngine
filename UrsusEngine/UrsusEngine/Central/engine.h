#pragma once

//std include 
#include <string>
#include <vector>
#include <memory>
//engine essentials includes
#include "InputHelper.h"
#include "Time.h"
#include "../Graphics/Window.h"

//ECS Include
#include "../Patterns/ECS/Entity.h"
#include "../Patterns/ECS/ISystem.h"
#include "../Graphics/RenderSystem.h"


namespace UrsusEngine
{
	class Engine
	{
	public:
		Engine(const int width, const int height, const std::string title);
		~Engine();

	public:
		//General
		const bool IsRunning() const { return m_IsRunning; }
		void Update();

		//Graphics & Window
		void Draw();


		//Input handling
		bool IsKeyPressed(Key key);
		bool IsMousePressed(MouseButton button);
		bool GetCursorPosition(float& X, float& Y) const;

		//Time
		const float GetElapsedTimeAsSeconds();

		//ESC
		void AddEntity(std::shared_ptr<ECS::Entity> entity);
		void RemoveEntity(std::shared_ptr<ECS::Entity> entity);
		void AddSystem(std::shared_ptr<ECS::ISystem> system);
		void RemoveSystem(std::shared_ptr<ECS::ISystem> system);
		const std::shared_ptr<Window> GetWindow() const { return m_Window; }


	private:
		//Window handling
		bool m_IsRunning;
		std::shared_ptr<Window> m_Window;
		//Rendering
		std::shared_ptr<ECS::RenderSystem> m_RenderSystem;
		//Time handling
		std::unique_ptr<Time> m_Time;
		std::vector<std::shared_ptr<ECS::Entity>> m_Entities;
		std::vector<std::shared_ptr<ECS::ISystem>> m_Systems;

		//For engine update
		float m_AccumulatedTime = 0.f;
	};
}
