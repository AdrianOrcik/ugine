#pragma once

#include <glm/glm.hpp>

#include "ugine/log.h"
#include "ugine/ecs/components/transform_component.h"
#include "ugine/coroutines/routine_manager.h"

#include "../sorting_element.h"

#include <functional>

namespace Ugine
{
	class TransformComponent;
	class SwapRoutine : public IEnumerator<void>
	{
	public:
		SwapRoutine(int originPosition, int insertPosition, std::vector<SortingElement*> Elements, float time);
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
		glm::vec2 startValueA_ = { 0.0f,0.0f };
		glm::vec2 endValueA_ = { 0.0f,0.0f };

		glm::vec2 startValueB_ = { 0.0f,0.0f };
		glm::vec2 endValueB_ = { 0.0f,0.0f };
		

		int positionA_ = 0;
		int positionB_ = 0;
		std::vector<SortingElement*> elements_;

		float time_ = 0;
		float frameTime_ = 0;
		float currentTime_ = 0;

		std::function<void()> onCompleted = NULL;
	};
}