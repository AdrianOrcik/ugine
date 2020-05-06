#pragma once

#include "ugine/log.h"
#include "ugine/ecs/ecs.h"
#include "ugine/ecs/component.h"
#include "ugine/ecs/components/transform_component.h"
#include "ugine/coroutines/routine_manager.h"
#include <glm/glm.hpp>

namespace Ugine
{
	class Movement : public IEnumerator<void>
	{
	public:
		//TransformComponent* transformComponent_ = nullptr;
		glm::vec2 startValue_ = { 0.0f,0.0f };
		glm::vec2 endValue_ = { 0.0f,0.0f };

		float time_ = 0;
		float currentTime_ = 0;

		////Movement(Entity* owner , glm::vec2 endValue, float time)
		////	: endValue_(endValue), time_(time)
		////{
		////	//transformComponent_ = (TransformComponent*)owner->GetComponent<TransformComponent>();
		////	//startValue_ = transformComponent_->GetLocalPosition();
		////}

		Movement(glm::vec2 endValue, float time)
			: endValue_(endValue), time_(time)
		{
			//startValue_ = transform->GetLocalPosition();
		}

		float GetInterpolation2(float a, float b, float t)
		{
			return a + (b - a) * t;
		}

		// Inherited via IEnumerator
		virtual bool HasMore() override 
		{
			return currentTime_ < time_;
		}

		virtual void next(float Timestep) override
		{
			LOG_INFO("Next");
			//float x = GetInterpolation2(startValue_.x, endValue_.x, (float)currentTime_);
			//transformComponent_->SetLocalX(x);
			//currentTime_ += 0.1f;
		}
	};
}