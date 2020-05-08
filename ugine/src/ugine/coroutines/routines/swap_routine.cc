#include "uepch.h"
#include "swap_routine.h"

namespace Ugine
{
	Ugine::SwapRoutine::SwapRoutine(TransformComponent * transformA, TransformComponent * transformB, float time)
		:transformA_(transformA), transformB_(transformB), time_(time)
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
	float SwapRoutine::GetInterpolation2(float a, float b, float t)
	{
		return a + (b - a) * t;
	}

	bool SwapRoutine::HasMore()
	{
		return currentTime_ < time_;
	}

	void SwapRoutine::Next(float Timestep)
	{
		LOG_INFO("Next");
		float xA = GetInterpolation2(startValueA_.x, endValueA_.x, (float)currentTime_);
		transformA_->SetLocalX(xA);

		float xB = GetInterpolation2(startValueB_.x, endValueB_.x, (float)currentTime_);
		transformB_->SetLocalX(xB);

		currentTime_ += Timestep * 1.0f;
	}

}