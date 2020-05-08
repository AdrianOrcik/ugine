#pragma once

#include <glm/glm.hpp>

#include "ugine/log.h"
#include "ugine/ecs/components/transform_component.h"
#include "ugine/coroutines/routine_manager.h"

namespace Ugine
{
	class TransformComponent;
	class SwapRoutine : public IEnumerator<void>
	{
	public:
		TransformComponent* transformA_ = nullptr;
		glm::vec2 startValueA_ = { 0.0f,0.0f };
		glm::vec2 endValueA_ = { 0.0f,0.0f };

		TransformComponent* transformB_ = nullptr;
		glm::vec2 startValueB_ = { 0.0f,0.0f };
		glm::vec2 endValueB_ = { 0.0f,0.0f };

		float time_ = 0;
		float currentTime_ = 0;

		SwapRoutine(TransformComponent* transformA, TransformComponent* transformB, float time);
		~SwapRoutine();
		float GetInterpolation2(float a, float b, float t);

		//// Inherited via IEnumerator
		virtual bool HasMore() override;
		virtual void Next(float Timestep) override;
	};
}