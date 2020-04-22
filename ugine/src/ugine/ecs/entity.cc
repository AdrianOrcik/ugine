#include "uepch.h"
#include "entity.h"
#include "ecs.h"

Ugine::Entity::Entity(EntityManager* entityManager, const std::string name)
	:entityManager_(entityManager), name_(name), isActive_(true)
{
	LOG_INFO("Entity Created - {0}", name_);
}

Ugine::Entity::~Entity()
{
	DestroyComponents();
	SetActive(false);
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
	entityManager_->DestroyEntity(this);
	delete this;
}
