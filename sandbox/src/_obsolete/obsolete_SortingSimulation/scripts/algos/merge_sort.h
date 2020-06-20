#pragma once

#include <algorithm>

#include "sorting_algo.h"

#include "ugine/coroutines/routine_manager.h"
#include "ugine/coroutines/routines/wait_seconds.h"

#include "../routines/swap_routine.h"
#include "../simulation/simulation_step_merge.h"

class MergeSort : public SortingAlgo
{
public:
	MergeSort();
	~MergeSort();

	// Inherited via SortingAlgo
	virtual void Sort() override;

private:
	void Run();
	void Merge(int low, int high);
	void MergeHelper(int low, int high, int mid);

	void AddStep(StepData data, MergeStep::Type stepType);
	std::vector<MergeStep> simulationSteps_;
};