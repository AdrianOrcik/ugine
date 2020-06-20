#pragma once
#include "sorting_algo.h"

#include "ugine/coroutines/routine_manager.h"
#include "ugine/coroutines/routines/wait_seconds.h"

#include "../routines/swap_routine.h"
#include "../simulation/simulation_step_quick.h"

//TODO: polish, coloring simulation
class Quicksort : public SortingAlgo
{
public:
	Quicksort();
	~Quicksort();

	// Inherited via SortingAlgo
	virtual void Sort() override;

private:
	void Run();
	void Quick(int left, int right);
	
	void AddStep(StepData data, QuickStep::Type stepType);
	std::vector<QuickStep> simulationSteps_;
};