#pragma once

#include "ugine.h"
#include "../layers/sandbox_2d.h"

class Sandbox2D;
class SortingElement : public Ugine::ScriptComponent
{

public:
	SortingElement()
	{}

	// Inherited via ScriptComponent
	virtual void OnInit() override
	{
		//LOG_INFO("INIT");
	}

	virtual void OnUpdate(float Timestep) override
	{
		//LOG_INFO("update");
	}

public:
	int Value;

private:


};