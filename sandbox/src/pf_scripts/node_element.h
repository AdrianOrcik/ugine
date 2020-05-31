#pragma once

#include "ugine.h"
#include "../layers/sandbox_2d.h"

class Sandbox2D;
class NodeElement : public Ugine::ScriptComponent
{
public:
	NodeElement()
	{}

	~NodeElement()
	{}

	// Inherited via ScriptComponent
	virtual void OnInit() override
	{}
	virtual void OnUpdate(float Timestep) override
	{}
	virtual void OnActive() override
	{}
	virtual void OnDeactive() override
	{}

	int Value;
	bool IsWall = false;
};