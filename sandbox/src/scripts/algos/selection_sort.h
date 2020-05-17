#pragma once
#include "sorting_algo.h"

#include "ugine/coroutines/routine_manager.h"
#include "ugine/coroutines/routines/swap_routine.h"
#include "ugine/coroutines/routines/wait_seconds.h"

class Selectionsort : public SortingAlgo
{
public:
	Selectionsort();
	~Selectionsort();

	// Inherited via SortingAlgo
	virtual void Sort() override;

private:
	void SelectElements();
	void BeforeFindNewSelection();
	void SwapElements();
	void AfterSwapElements();
	int firstElementIndex_ = 0;
};