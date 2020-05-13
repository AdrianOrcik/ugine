#include "uepch.h"
#include "entity_manager.h"

#include <vector>
#include <iterator>  

#include "ugine/log.h"
namespace Ugine
{
	void Ugine::EntityManager::OnUpdate(Timestep dt)
	{
		for(auto& entity: entities_)
		{
			if(entity->IsActive())
				entity->OnUpdate(dt);
		}
	}

	void Ugine::EntityManager::AddEntity(Entity* entity)
	{
		entities_.emplace_back(entity);
	}

	Entity * EntityManager::GetEntity(const std::string name)
	{
		for (auto& entity : entities_)
		{
			if (entity->GetName().compare(name))
				return entity;
		}

		LOG_ERROR("EntityManager::GetEntity::EntityIsNULL");
		LOG_ERROR("name '{0}' does not exist!");
		return nullptr;
	}

	void Ugine::EntityManager::DestroyEntity(Entity * entity)
	{
		//todo: make template erase function
		//std::vector<Entity*>::iterator it = std::find(entities_.begin(), entities_.end(), entity);
		//std::vector<Entity*>::iterator first = entities_.begin();
		//int index = std::distance(first, it);
		//entities_.erase(entities_.begin() + index);

		//entities_.erase(std::remove(entities_.begin(), entities_.end(), entity), entities_.end());
		//delete entity;
		//for (auto entity : entities_)
		//{
		//	delete entity;
		//}
		//entities_.clear();
	}
}
