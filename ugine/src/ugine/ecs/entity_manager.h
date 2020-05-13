#pragma once

#include <vector>

#include "entity.h"
#include "ugine/core/timestep.h"

namespace Ugine
{
	class Entity;
	class EntityManager
	{
	public:
		EntityManager() = default;
		virtual ~EntityManager() = default;

		void OnUpdate(Timestep dt);
		void AddEntity(Entity* entity);

		Entity* GetEntity(const std::string name);
		std::vector<Entity*>* GetEntities() { return &entities_; }

		void DestroyEntity(Entity* entity);
	private:
		std::vector<Entity*> entities_;
	};
}
