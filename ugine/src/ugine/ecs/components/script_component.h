#pragma once

#include "../component.h"
#include "../entity.h"

namespace Ugine
{
	class ScriptComponent : public Component
	{
	public:
		ScriptComponent() = default;
		~ScriptComponent() = default;

		// Inherited via Component
		virtual void Init() override
		{
			OnInit();
		}
		virtual void Update(float Timestep) override
		{
			OnUpdate(Timestep);
		}

		virtual void OnInit() = 0;
		virtual void OnUpdate(float Timestep) = 0;
		virtual void OnActive() = 0;
		virtual void OnDeactive()  = 0;

	public:
		Entity* GetEntity() { return owner; }
	};
}