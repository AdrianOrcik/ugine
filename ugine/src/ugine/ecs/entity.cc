#include "uepch.h"
#include "entity.h"

Ugine::Entity::Entity(const std::string name)
	: name_(name), isActive_(true)
{
	LOG_INFO("Entity Created - {0}", name_);
}

Ugine::Entity::~Entity()
{
	LOG_INFO("Entity Delete - {0}", name_);
}

void Ugine::Entity::OnUpdate(Timestep dt)
{
	for (auto& component : components_)
	{
		component->Update(dt);
	}
}

void Ugine::Entity::Deactivate()
{
	isActive_ = false;
}

void Ugine::Entity::DestroyComponents()
{
	for (auto component : components_)
	{
		delete component;
	}
}
