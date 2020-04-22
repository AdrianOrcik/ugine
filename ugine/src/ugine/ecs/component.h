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
	};
}