#include "sorting_manager.h"


void SortingManager::StepMove()
{
	if (index_ < BubbleElements.size()) {
		SortingElementData* data = BubbleElements[index_];
		swapRoutine = new Ugine::SwapRoutine(data->ElementA, data->ElementB, 1.0f);
		Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)swapRoutine);
		index_++;
	}
	else {
		LOG_ERROR("No More Steps!");
		index_ = 0;
	}
}

