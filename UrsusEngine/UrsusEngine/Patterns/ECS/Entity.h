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
				//check during compile-time if the template class is valid
				static_assert(std::is_base_of<IComponent, T>::value, "T must be derived from IComponent");
				//if the component is already inside, return it directly
				std::shared_ptr<T> foundComponent = GetComponent<T>();
				if (foundComponent)
				{
					return foundComponent;
				}
				//if not already inside, then create and add new component
				std::shared_ptr<T> addedComponent = std::make_shared<T>();
				m_Components.push_back(addedComponent);
				return addedComponent;
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
				for (std::shared_ptr<IComponent>& component : m_Components)
				{
					//try to cast component to specific type and if possible, return it
					if (std::shared_ptr<T> cast = std::dynamic_pointer_cast<T>(component))
					{
						return cast;
					}
				}

				//if component not found, return nullptr
				return nullptr;
			}

			template<typename T>
			bool HasComponent()
			{
				return GetComponent<T>() != nullptr;
			}

		protected:
			std::vector<std::shared_ptr<IComponent>> m_Components;
		};

	}
}