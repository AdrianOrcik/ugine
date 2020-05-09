#include "sorting_manager.h"
#include <utility>

void SortingManager::StepMove()
{
	if (index_ < BubbleElements.size()) {
		SortingElementData* data = BubbleElements[index_];
		Ugine::SwapRoutine* swapRoutine = new Ugine::SwapRoutine(data->ElementA, data->ElementB, 1.0f);
		
		std::function<void(void)> function = std::bind(&SortingManager::SwapRoutineCompleted, this);
		swapRoutine->SetOnCompleted(function);

		Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)swapRoutine);
		index_++;
	}
	else {
		LOG_ERROR("No More Steps!");
		index_ = 0;
	}
}

void SortingManager::SwapRoutineCompleted()
{
	Ugine::WaitSeconds* waitfor = new Ugine::WaitSeconds(1.0f);
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
	waitfor->SetOnCompleted(std::bind(&SortingManager::StepMove, this));
}


