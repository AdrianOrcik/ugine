#pragma once

#include "ugine/ecs/entity_manager.h"
#include "ugine/ecs/entity.h"
#include "ugine/ecs/component.h"

namespace Ugine
{
	class Entity;
	class Component;
	class EntityManager;
	class ECS
	{
	public:
		static Entity* CreateEntity(const std::string name);
		static Entity* CreateCopy(Entity& entity);
		
		static Entity* CreatePrefab(const std::string name);
		static Entity* GetEntity(const std::string name);

		//static EntityManager GetEntityManager() { return entityManager_; }
		
		static void Update(Timestep dt);
		
		static void DestroyEntities();
		static void DestroyEntity(Entity* entity);
	private:
		static EntityManager* entityManager_;
	};
}