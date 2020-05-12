#include "uepch.h"
#include "ecs.h"


namespace Ugine
{
	EntityManager ECS::entityManager_;
	Entity* ECS::CreateEntity(const std::string name)
	{
		//TODO: memory leak
		Entity* entity = DBG_NEW Ugine::Entity(&entityManager_, name);
		entityManager_.AddEntity(entity);
		return entity;
	}

	Entity * ECS::GetEntity(const std::string name)
	{
		return entityManager_.GetEntity(name);
	}

	void ECS::Update(Timestep dt)
	{
		entityManager_.OnUpdate(dt);
	}

	void ECS::DestroyEntities()
	{
		auto entities = entityManager_.GetEntities();
		for (auto entity : entities)
		{
			entity->Destroy();
		}
	}
}