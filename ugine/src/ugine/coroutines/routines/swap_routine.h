#pragma once

#include <glm/glm.hpp>

#include "ugine/log.h"
#include "ugine/ecs/components/transform_component.h"
#include "ugine/coroutines/routine_manager.h"

#include <functional>

namespace Ugine
{
	class TransformComponent;
	class SwapRoutine : public IEnumerator<void>
	{
	public:


		SwapRoutine(TransformComponent* transformA, TransformComponent* transformB, float time);
		~SwapRoutine();
		
		void SetOnCompleted(std::function<void()>f){ onCompleted = f; }

		// Inherited via IEnumerator
		virtual bool HasMore() override;
		virtual void Next(float Timestep) override;
		virtual void OnCompleted() override;

	private:
		float GetInterpolation2(float a, float b, float t);
		float MapValue(float x, float in_min, float in_max, float out_min, float out_max);

	private:
		TransformComponent* transformA_ = nullptr;
		glm::vec2 startValueA_ = { 0.0f,0.0f };
		glm::vec2 endValueA_ = { 0.0f,0.0f };

		TransformComponent* transformB_ = nullptr;
		glm::vec2 startValueB_ = { 0.0f,0.0f };
		glm::vec2 endValueB_ = { 0.0f,0.0f };
		
		///speed is from 1 to infinity
		float speed_ = 0;
		float currentTime_ = 0;

		std::function<void()> onCompleted = NULL;
	};
}