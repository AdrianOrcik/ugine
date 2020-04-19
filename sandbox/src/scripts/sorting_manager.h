#pragma once

#include "ugine.h"
#include "../layers/sandbox_2d.h"

class Sandbox2D;
class SortingManager : public Ugine::ScriptComponent
{

public:
	SortingManager()
	{}

	std::vector<Ugine::TransformComponent*> Elemets;

	// Inherited via ScriptComponent
	virtual void OnInit() override
	{
		//LOG_INFO("INIT");
	}

	virtual void OnUpdate(float Timestep) override
	{
		//LOG_INFO("update");
	}

private:


};