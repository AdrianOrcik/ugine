#pragma once

#include "ugine/log.h"
#include "ugine/coroutines/routine_manager.h"

#include <functional>

namespace Ugine
{
	class WaitSeconds : public IEnumerator<void>
	{
	public:
		WaitSeconds(float time);
		~WaitSeconds();

		void SetOnCompleted(std::function<void()>f) { onCompleted = f; }

		// Inherited via IEnumerator
		virtual bool HasMore() override;
		virtual void Next(float Timestep) override;
		virtual void OnCompleted() override;

	private:
		float time_ = 0;
		float currentTime_ = 0;

		std::function<void()> onCompleted = NULL;
	};
}