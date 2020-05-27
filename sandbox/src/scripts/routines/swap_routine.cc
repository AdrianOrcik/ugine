#include "uepch.h"
#include "swap_routine.h"

namespace Ugine
{
	Ugine::SwapRoutine::SwapRoutine(int positionA, int positionB, std::vector<SortingElement*> Elements, float time)
		: positionA_(positionA), positionB_(positionB), elements_(Elements), time_(time)
	{
		startValueA_ = elements_[positionA_]->GetTransform()->GetLocalPosition();
		endValueA_ = elements_[positionB_]->GetTransform()->GetLocalPosition();

		startValueB_ = elements_[positionB_]->GetTransform()->GetLocalPosition();
		endValueB_ = elements_[positionA_]->GetTransform()->GetLocalPosition();
	}

	SwapRoutine::~SwapRoutine()
	{
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
		frameTime_ += Timestep;
		
		//NOTE: calculation of duration into range 0 - 1 for interpolation 
		currentTime_ = (frameTime_ / time_);
		float clampValue = currentTime_ > 1.0f ? 1.0f : currentTime_;

		float xA = GetInterpolation2(startValueA_.x, endValueA_.x, clampValue);
		elements_[positionA_]->GetTransform()->SetLocalX(xA);

		float xB = GetInterpolation2(startValueB_.x, endValueB_.x, clampValue);
		elements_[positionB_]->GetTransform()->SetLocalX(xB);
	}

	float SwapRoutine::MapValue(float x, float in_min, float in_max, float out_min, float out_max)
	{
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}

	void SwapRoutine::OnCompleted()
	{
		onCompleted();
		onCompleted = NULL;
		delete this;
	}

}