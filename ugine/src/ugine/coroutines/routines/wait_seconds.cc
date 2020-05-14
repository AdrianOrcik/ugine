#include "uepch.h"
#include "wait_seconds.h"

namespace Ugine
{

	Ugine::WaitSeconds::WaitSeconds(float time)
		:time_(time)
	{}

	WaitSeconds::~WaitSeconds()
	{}

	bool WaitSeconds::HasMore()
	{
		bool hasTime = currentTime_ < time_;
		if (!hasTime)OnCompleted();
		return hasTime;
	}

	void WaitSeconds::Next(float Timestep)
	{
		currentTime_ += Timestep;
	}

	void WaitSeconds::OnCompleted()
	{
		onCompleted();
		onCompleted = NULL;
		delete this;
	}

}
