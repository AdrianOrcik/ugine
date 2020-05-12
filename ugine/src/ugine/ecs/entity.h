#pragma once

#include <vector>
#include <string>

#include "component.h"
#include "entity_manager.h"
#include "ugine/core/timestep.h"
#include "ugine/ecs/components/transform_component.h"

namespace Ugine
{
	class Component;
	class TransformComponent;
	class EntityManager;
	class Entity
	{
	public:
		Entity(EntityManager* entityManager_, const std::string name);
		virtual ~Entity();
		std::string GetName() const { return name_; }

		void SetActive(bool isActive);
		bool IsActive() const { return isActive_; }

		void OnUpdate(Timestep dt);
		void Destroy();

	private:
		void DestroyComponents();

	public:
        template <typename T, typename... TArgs>
	    Component* AddComponent(TArgs&&... args)
		{
			//todo: memory leak
            T* newComponent(DBG_NEW T(std::forward<TArgs>(args)...));
            newComponent->owner = this;
			components_.emplace_back(newComponent);
            newComponent->Init();
            return newComponent;
        }

		template <typename T>
		Component* GetComponent()
		{
			for (auto& component : components_)
			{
				T* t = dynamic_cast<T*>(component);
				if (t != nullptr)
					return t;
			}
		}

	private:
		std::vector<Component*> components_;
		std::string name_;
		bool isActive_;
		EntityManager* entityManager_;
	};
}
