#pragma once

#include "sorting_algo.h"

#include "ugine/coroutines/routine_manager.h"
#include "ugine/coroutines/routines/swap_routine.h"
#include "ugine/coroutines/routines/wait_seconds.h"

class InsertionSort : public SortingAlgo
{
public:
	InsertionSort();
	~InsertionSort();

	// Inherited via SortingAlgo
	virtual void Sort() override;

private:
	void SelectElements();
	void SwapElements();

	//nonsorted base array
	std::vector<SortingElement*> BaseElements;
};