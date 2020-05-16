#include "uepch.h"
#include "entity.h"
#include "ecs.h"

#include "ugine/ecs/components/transform_component.h"
#include "ugine/ecs/components/renderer_component.h"
#include "ugine/ecs/components/script_component.h"

Ugine::Entity::Entity( const std::string name)
	: name_(name), isActive_(false)
{
	//LOG_INFO("Entity Created - {0}", name_);
}

Ugine::Entity::Entity(Entity & entity)
{
	name_ = entity.GetName() + "_copy";
	isActive_ = entity.isActive_;

	//TODO: implement reflection lib
	//TODO: copy components 
	//get component and create copy
	if (entity.HasComponent<TransformComponent>())
	{
		this->AddComponent<TransformComponent>();
	}

	if (entity.HasComponent<RendererComponent>())
	{
		this->AddComponent<RendererComponent>();
	}

	//if (entity.HasComponent<ScriptComponent>())
	//{
	//	//AddComponent<ScriptComponent>();
	//}

	//LOG_INFO("Entity Copied - {0}", name_);
}

Ugine::Entity::~Entity()
{
	DestroyComponents();
	//LOG_INFO("Entity Delete - {0}", name_);
}

void Ugine::Entity::OnUpdate(Timestep dt)
{
	for (auto& component : components_)
	{
		component->Update(dt);
	}
}

void Ugine::Entity::DestroyComponents()
{
	for (auto component : components_)
	{
		delete component;
	}
}

void Ugine::Entity::OnActive()
{
	for (auto& component : components_)
	{
		component->OnActive();
	}
}

void Ugine::Entity::OnDeactive()
{
	for (auto& component : components_)
	{
		component->OnDeactive();
	}
}

void Ugine::Entity::SetActive(bool isActive)
{
	isActive_ = isActive;

	if (isActive_) 
	{
		OnActive();
	}
	else
	{
		OnDeactive();
	}
}

void Ugine::Entity::Destroy()
{
	ECS::DestroyEntity(this);
}
