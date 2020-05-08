#pragma once

#include <glm/glm.hpp>

#include "ugine/log.h"
#include "ugine/ecs/components/transform_component.h"
#include "ugine/coroutines/routine_manager.h"

namespace Ugine
{
	class TransformComponent;
	class Movement : public IEnumerator<void>
	{
	public:
		TransformComponent* transform_ = nullptr;
		glm::vec2 startValue_ = { 0.0f,0.0f };
		glm::vec2 endValue_ = { 0.0f,0.0f };

		float time_ = 0;
		float currentTime_ = 0;

		Movement(TransformComponent* transformComponent, glm::vec2 endValue, float time);
		~Movement();
		float GetInterpolation2(float a, float b, float t);

		// Inherited via IEnumerator
		virtual bool HasMore() override;
		virtual void Next(float Timestep) override;
	};
}