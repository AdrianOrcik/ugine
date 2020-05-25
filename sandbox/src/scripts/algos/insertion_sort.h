#pragma once

#include "sorting_algo.h"

#include <algorithm>


#include "ugine/coroutines/routine_manager.h"
#include "ugine/coroutines/routines/wait_seconds.h"

#include "../routines/swap_routine.h"
#include "../routines/insert_routine.h"
#include "../simulation/simulation_step_insertion.h"


class InsertionStep;
class InsertionSort : public SortingAlgo
{
public:
	InsertionSort();
	~InsertionSort();

	// Inherited via SortingAlgo
	virtual void Sort() override;

private:
	void Run();
	void AddStep(StepData data, InsertionStep::Type stepType);
	std::vector<InsertionStep> simulationSteps_;

};
