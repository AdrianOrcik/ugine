#include "uepch.h"
#include "entity.h"

Ugine::Entity::Entity(EntityManager & entityManager)
	:entityManager_(entityManager)
{
	isActive_ = true;
}


Ugine::Entity::Entity(EntityManager & entityManager, std::string name)
	: entityManager_(entityManager), name_(name)
{
	isActive_ = true;
}

void Ugine::Entity::OnUpdate(Timestep dt)
{
	for (auto& component : components_)
	{
		component->Update(dt);
	}
}

void Ugine::Entity::Destroy()
{
	isActive_ = false;
}
