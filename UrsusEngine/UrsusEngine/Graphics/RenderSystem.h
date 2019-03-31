#pragma once
#include "../Patterns/ECS/ISystem.h"
#include <memory>
#include "Window.h"

namespace UrsusEngine
{
	namespace ECS
	{
		class RenderSystem : public ISystem
		{
		public:
			RenderSystem();
			~RenderSystem();

		public:
			//ISystem
			virtual bool DoesEntityMatch(std::shared_ptr<Entity> entity) override;

		public:
			void Draw(std::shared_ptr<UrsusEngine::Window> window);
		};
	}
}

