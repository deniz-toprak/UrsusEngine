#pragma once
#include <memory>
#include "Entity.h"


namespace UrsusEngine
{
	namespace ECS
	{
		class ISystem
		{
		public:
			ISystem(){}
			~ISystem();

		public:
			virtual bool DoesEntityMatch(std::shared_ptr<Entity> entity) = 0;
			void AddEntity(std::shared_ptr<Entity> entity);
			void RemoveEntity(std::shared_ptr<Entity> entity);

		protected:
			std::vector<std::shared_ptr<Entity>> m_Entities;
		};
	}
}