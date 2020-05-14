#pragma once

#include "ugine/core/timestep.h"
#include "entity.h"

namespace Ugine
{
	class Entity;
	class Component {
	public:
		Entity* owner;
		virtual ~Component() = default;
		virtual void Init() = 0;
		virtual void Update(float Timestep) = 0;
		virtual void OnActive() = 0;
		virtual void OnDeactive() = 0;

		//Move to math.h
		float GetInterpolation2(float a, float b, float t)
		{
			return a + (b - a) * t;
		}
	};
}