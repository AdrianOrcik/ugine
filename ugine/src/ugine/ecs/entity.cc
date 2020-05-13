#include "uepch.h"
#include "entity.h"
#include "ecs.h"

Ugine::Entity::Entity( const std::string name)
	: name_(name), isActive_(false)
{
	LOG_INFO("Entity Created - {0}", name_);
}

Ugine::Entity::Entity(Entity & entity)
{
	name_ = entity.GetName() + "_copy";
	isActive_ = entity.isActive_;

	//TODO: copy components 
	//get component and create copy

	LOG_INFO("Entity Copied - {0}", name_);
}

Ugine::Entity::~Entity()
{
	DestroyComponents();
	LOG_INFO("Entity Delete - {0}", name_);
}

void Ugine::Entity::OnUpdate(Timestep dt)
{
	for (auto& component : components_)
	{
		component->Update(dt);
	}
}

void Ugine::Entity::SetActive(bool isActive)
{
	isActive_ = isActive;
}

void Ugine::Entity::DestroyComponents()
{
	for (auto component : components_)
	{
		delete component;
	}
}

void Ugine::Entity::Destroy()
{
	ECS::DestroyEntity(this);
}
