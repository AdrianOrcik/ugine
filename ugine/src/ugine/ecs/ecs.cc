#include "uepch.h"
#include "ecs.h"


namespace Ugine
{
	EntityManager* ECS::entityManager_ = DBG_NEW EntityManager();
	Entity* ECS::CreateEntity(const std::string name)
	{
		Entity* entity = DBG_NEW Ugine::Entity(name);
		entityManager_->AddEntity(entity);
		return entity;
	}

	Entity* ECS::CreateCopy(Entity& entity)
	{
		Entity* copiedEntity = DBG_NEW Ugine::Entity(entity);
		entityManager_->AddEntity(copiedEntity);
		return copiedEntity;
	}

	Entity * ECS::CreatePrefab(const std::string name)
	{
		Entity* entity = DBG_NEW Ugine::Entity(name);
		return entity;
	}

	Entity * ECS::GetEntity(const std::string name)
	{
		return entityManager_->GetEntity(name);
	}

	void ECS::Update(Timestep dt)
	{
		entityManager_->OnUpdate(dt);
	}

	void ECS::DestroyEntities()
	{
		auto entities = entityManager_->GetEntities();
		for (auto entity : *entities)
		{
			delete entity;
		}

		entities->clear();
	}

	void ECS::DestroyEntity(Entity * entity)
	{
		std::vector<Entity*>* entities = entityManager_->GetEntities();
		entities->erase(std::remove(entities->begin(), entities->end(), entity), entities->end());
		delete entity;
	}
}