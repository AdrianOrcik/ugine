#include "uepch.h"
#include "entity_manager.h"
#include <vector>
#include "ugine/log.h"

//class Entity;
//void Ugine::EntityManager::ClearData()
//{
//	for (auto& entity : entities_) 
//	{
//		entity->Destroy();
//	}
//}
//
//void Ugine::EntityManager::OnUpdate(Timestep dt)
//{
//	for(auto& entity: entities_)
//	{
//		entity->OnUpdate(dt);
//	}
//}
//
//bool Ugine::EntityManager::HasEntities() const
//{
//	return entities_.size() > 0;
//}
//
//Ugine::Entity& Ugine::EntityManager::AddEntity(std::string entityName)
//{
//	Entity *entity = new Entity(*this, entityName);
//	entities_.emplace_back(entity);
//	return *entity;
//}
//
//unsigned int Ugine::EntityManager::GetEntityCount()
//{
//	return 0;
//}

namespace Ugine
{
	void Ugine::EntityManager::OnUpdate(Timestep dt)
	{
		for(auto& entity: entities_)
		{
			entity->OnUpdate(dt);
		}
	}

	void Ugine::EntityManager::AddEntity(Entity* entity)
	{
		entities_.emplace_back(entity);
	}
}
