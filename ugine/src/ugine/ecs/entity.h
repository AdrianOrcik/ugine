#pragma once

#include <vector>
#include <string>

#include "component.h"
#include "entity_manager.h"
#include "ugine/core/timestep.h"
#include "ugine/ecs/components/transform.h"
//namespace Ugine
//{
//	//class EntityManager;
//	//class Component;
//	//class Entity
//	//{
//	//public:
//	//	Entity(EntityManager& entityManager);
//	//	Entity(EntityManager& entityManager, std::string name);
//	//	
//	//	std::string GetName() const { return name_; }
//	//	bool IsActive() const { return isActive_; }
//
//	//	void OnUpdate(Timestep dt);
//	//	void Destroy();
//
//	//	//void Render(); todo: implemented
//	//public:
// //      template <typename T, typename... TArgs>
// //       T& AddComponent(TArgs&&... args) 
//	//	{
// //           T* newComponent(new T(std::forward<TArgs>(args)...));
// //           newComponent->owner = this;
//	//		components_.emplace_back(newComponent);
// //           newComponent->Init();
// //           return *newComponent;
// //       }
//
//	//private:
//	//	EntityManager& entityManager_;
//	//	std::vector<Component*> components_;
//
//	//	std::string name_;
//	//	bool isActive_;
//	//};
//}

namespace Ugine
{
	class Component;
	class Transform;
	class Entity
	{
	public:
		Entity(const std::string name);
		virtual ~Entity() = default;
		std::string GetName() const { return name_; }
		bool IsActive() const { return isActive_; }

		void OnUpdate(Timestep dt);
		void Destroy();

	public:
       template <typename T, typename... TArgs>
	   Component* AddComponent(TArgs&&... args)
		{
            T* newComponent(new T(std::forward<TArgs>(args)...));
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
	};
}
