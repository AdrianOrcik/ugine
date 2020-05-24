#pragma once
#include "sorting_algo.h"

#include "ugine/coroutines/routine_manager.h"
#include "ugine/coroutines/routines/wait_seconds.h"

#include "../routines/swap_routine.h"
#include "../simulation/simulation_step_heap.h"

class MergeSort : public SortingAlgo
{
public:
	MergeSort();
	~MergeSort();

	// Inherited via SortingAlgo
	virtual void Sort() override;

private:
	void Merge(int low, int high);
	void MergeHelper(int low, int high, int mid);

	void AddStep(StepData data, HeapStep::Type stepType);
	std::vector<HeapStep> simulationSteps_;
};