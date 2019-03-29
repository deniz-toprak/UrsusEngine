#pragma once
#include <vector>
#include <type_traits>
#include <memory>
#include "IComponent.h"

namespace UrsusEngine
{
	namespace ECS
	{
		class Entity
		{
		public:

			Entity() {}

			~Entity() {}

		public:
			template<typename T>
			std::shared_ptr<T> AddComponent()
			{
				//check if T is child of ECS::IComponent
				static_assert(std::is_base_of<ECS::IComponent, T>::value, "T must be derived from ECS::IComponent");
				//Is Component already in list?
				std::shared_ptr<T> foundComponent = GetComponent<T>();
				if (foundComponent != nullptr)
				{
					return foundComponent;
				}

				std::shared_ptr<T> component = std::make_shared<T>();
				m_Components.push_back(std::shared_ptr<T>(component));
				return component;
			}

			template<typename T>
			void RemoveComponent()
			{
				//check if T is child of ECS::IComponent
				static_assert(std::is_base_of<ECS::IComponent, T>::value, "T must be derived from ECS::IComponent");
				//try find component and then delete
				for (std::vector<std::shared_ptr<ECS::IComponent>>::iterator compItr = m_Components.begin(); compItr != m_Components.end();)
				{
					if (std::shared_ptr<T> cast = std::dynamic_pointer_cast<T>(*compItr))
					{
						m_Components.erase(compItr);
						break;
					}
					else
					{
						++compItr;
					}
				}
			}

			template<typename T>
			std::shared_ptr<T> GetComponent()
			{
				//check if T is child of ECS::IComponent
				static_assert(std::is_base_of<ECS::IComponent, T>::value, "T must be derived from ECS::IComponent");
				//Try find component and then return
				for (std::vector<std::shared_ptr<ECS::IComponent>>::iterator compItr = m_Components.begin(); compItr != m_Components.end();)
				{
					if (std::shared_ptr<T> cast = std::dynamic_pointer_cast<T>(*compItr))
					{
						return cast;
					}
					else
					{
						++compItr;
					}
				}
				//Not found - return nullptr
				return nullptr;
			}

			template<typename T>
			bool HasComponent()
			{
				return GetComponent<T>() != nullptr;
			}

		protected:
			std::vector<std::shared_ptr<ECS::IComponent>> m_Components;
		};

	}
}