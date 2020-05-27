#include "uepch.h"
#include "movement.h"

namespace Ugine
{
	Movement::Movement(TransformComponent * transformComponent, glm::vec2 endValue, float time)
		: transform_(transformComponent), endValue_(endValue), time_(time)
	{
		startValue_ = transform_->GetLocalPosition();
	}

	Movement::~Movement()
	{
		delete this;
	}

	float Movement::GetInterpolation2(float a, float b, float t)
	{
		//todo: Interpolation class or tween class
		return a + (b - a) * t;
	}

	bool Movement::HasMore()
	{
		return currentTime_ < time_;
	}

	void Movement::Next(float Timestep)
	{
		float x = GetInterpolation2(startValue_.x, endValue_.x, (float)currentTime_);
		transform_->SetLocalX(x);
		currentTime_ += Timestep * 1.0f;
	}
}