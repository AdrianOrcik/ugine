#include "uepch.h"
#include "swap_routine.h"

namespace Ugine
{
	Ugine::SwapRoutine::SwapRoutine(TransformComponent * transformA, TransformComponent * transformB, float speed)
		:transformA_(transformA), transformB_(transformB), speed_(speed)
	{
		startValueA_ = transformA_->GetLocalPosition();
		endValueA_ = transformB_->GetLocalPosition();

		startValueB_ = transformB_->GetLocalPosition();
		endValueB_ = transformA_->GetLocalPosition();
	}
	SwapRoutine::~SwapRoutine()
	{
		delete this;
	}

	//todo: define as utility (math)
	float SwapRoutine::GetInterpolation2(float a, float b, float t)
	{
		return a + (b - a) * t;
	}

	bool SwapRoutine::HasMore()
	{
		//todo: define constants 
		bool hasTime = currentTime_ < 1.0f;
		if (!hasTime)
			OnCompleted();
		return hasTime;
	}

	void SwapRoutine::Next(float Timestep)
	{
		currentTime_ += Timestep * speed_;

		//todo: (math) define as maximum and minimum
		float value = currentTime_ > 1.0f ? 1.0f : currentTime_;

		float xA = GetInterpolation2(startValueA_.x, endValueA_.x, value);
		transformA_->SetLocalX(xA);

		float xB = GetInterpolation2(startValueB_.x, endValueB_.x, value);
		transformB_->SetLocalX(xB);
	}

	float SwapRoutine::MapValue(float x, float in_min, float in_max, float out_min, float out_max)
	{
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}

	void SwapRoutine::OnCompleted()
	{
		onCompleted();
		onCompleted = NULL;
	}

}