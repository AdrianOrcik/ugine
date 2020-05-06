#include "uepch.h"
#include "movement.h"

namespace Ugine
{
	Movement::Movement(TransformComponent * transformComponent, glm::vec2 endValue, float time)
		: transform_(transformComponent), endValue_(endValue), time_(time)
	{
		startValue_ = transform_->GetLocalPosition();
	}

	//Movement::Movement(glm::vec2 endValue, float time)
	//	: endValue_(endValue), time_(time)
	//{
	//}

	float Movement::GetInterpolation2(float a, float b, float t)
	{
		return a + (b - a) * t;
	}

	bool Movement::HasMore()
	{
		return currentTime_ < time_;
	}

	void Movement::next(float Timestep)
	{
		LOG_INFO("Next");
		float x = GetInterpolation2(startValue_.x, endValue_.x, (float)currentTime_);
		transform_->SetLocalX(x);
		currentTime_ += 0.1f;
	}
}