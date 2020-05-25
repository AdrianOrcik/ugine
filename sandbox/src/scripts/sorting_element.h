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
	}

	Ugine::TransformComponent* GetTransform() { return (Ugine::TransformComponent*)GetEntity()->GetComponent<Ugine::TransformComponent>(); }
	Ugine::RendererComponent* GetRenderer() { return (Ugine::RendererComponent*)GetEntity()->GetComponent<Ugine::RendererComponent>(); }

	// Inherited via ScriptComponent
	virtual void OnInit() override
	{}

	virtual void OnUpdate(float Timestep) override
	{}

	virtual void OnActive() override
	{}

	virtual void OnDeactive() override
	{}

public:
	int Value = 0;

	//DEBUG
	int CurrentPosition = 0;
	int SortedPosition = 0;
};