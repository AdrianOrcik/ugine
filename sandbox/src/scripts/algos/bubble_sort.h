#pragma once
#include "sorting_algo.h"

#include "ugine/coroutines/routine_manager.h"
#include "ugine/coroutines/routines/swap_routine.h"
#include "ugine/coroutines/routines/wait_seconds.h"

class BubbleSort : public SortingAlgo
{
public:
	BubbleSort(std::vector<SortingElement*> elements);
	~BubbleSort();

	// Inherited via SortingAlgo
	virtual void Sort() override;
private:
	void SelectElements();
	void SwapElements();
	void UnselectElements();
};