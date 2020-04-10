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
		static Entity* GetEntity(const std::string name);
		static void Update(Timestep dt);
	
	private:
		static EntityManager entityManager_;
	};
}