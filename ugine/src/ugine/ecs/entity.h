#pragma once

#include <vector>
#include <string>

#include "component.h"
#include "entity_manager.h"
#include "ugine/core/timestep.h"
#include "ugine/log.h"

namespace Ugine
{
	class Component;
	class Entity
	{
	public:
		Entity(const std::string name);
		Entity(Entity& entity);

		virtual ~Entity();
		std::string GetName() const { return name_; }

		void SetActive(bool isActive);
		bool IsActive() const { return isActive_; }

		void OnUpdate(Timestep dt);
		void Destroy();
		void OnActive();
		void OnDeactive();

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
		void DestroyComponent()
		{
			////Version 1
			//int componentID = 0;
			//for (int i = 0; i < components_.size(); i++)
			//{
			//	T* t = dynamic_cast<T*>(components_[i]);
			//	if (t != nullptr) 
			//	{
			//		delete t;
			//		components_.erase(components_.begin() + i);
			//		return;
			//	}
			//}

			//Version 2
			int componentID = 0;
			for (auto& component : components_)
			{
				T* t = dynamic_cast<T*>(component);
				if (t != nullptr){
					delete t;
					break;
				}
				componentID++;
			}

			components_.erase(components_.begin() + componentID);
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

		template <typename T>
		bool HasComponent()
		{
			for (auto& component : components_)
			{
				T* t = dynamic_cast<T*>(component);
				if (t != nullptr)
					return true;
			}
			return false;
		}

	private:
		std::vector<Component*> components_;
		std::string name_;
		bool isActive_;
	};
}
