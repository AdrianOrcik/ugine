#pragma once

#include "ugine.h"
#include "../layers/sandbox_2d.h"

class Sandbox2D;
class SortingElement : public Ugine::ScriptComponent
{

public:
	SortingElement()
		:Value(-1), CurrentPosition(-1), SortedPosition(-1)
	{}

	~SortingElement()
	{
		LOG_INFO("Delete SortingElement - ScriptComponent");
	}

	Ugine::TransformComponent* GetTransform() { return (Ugine::TransformComponent*)GetEntity()->GetComponent<Ugine::TransformComponent>(); }
	Ugine::RendererComponent* GetRenderer() { return (Ugine::RendererComponent*)GetEntity()->GetComponent<Ugine::RendererComponent>(); }

	// Inherited via ScriptComponent
	virtual void OnInit() override
	{}

	virtual void OnUpdate(float Timestep) override
	{}

public:
	int Value;
	int CurrentPosition;
	int SortedPosition;

};