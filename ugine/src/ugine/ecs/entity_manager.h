#pragma once

#include <vector>

#include "entity.h"
#include "ugine/core/timestep.h"

namespace Ugine
{
	//class EntityManager
	//{
	//public:
	//	EntityManager() = default;
	//	virtual ~EntityManager() = default;

	//	void ClearData();
	//	void OnUpdate(Timestep dt);
	//	bool HasEntities() const;

	//	Entity& AddEntity(std::string entityName);
	//	std::vector<Entity*> GetEntities() const { return entities_; }
	//	unsigned int GetEntityCount();

	//	//void Render(); todo: implement
	//private:
	//	std::vector<Entity*> entities_;
	//};

	class Entity;
	class EntityManager
	{
	public:
		EntityManager() = default;
		virtual ~EntityManager() = default;

		void OnUpdate(Timestep dt);
		void AddEntity(Entity* entity);
		Entity* GetEntity(const std::string name);

	private:
		std::vector<Entity*> entities_;
	};
}
