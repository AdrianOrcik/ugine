#pragma once
#include "sorting_algo.h"

#include "ugine/coroutines/routine_manager.h"
#include "ugine/coroutines/routines/wait_seconds.h"

#include "../routines/swap_routine.h"
#include "../simulation/simulation_step_bubble.h"

class Quicksort : public SortingAlgo
{
public:
	Quicksort();
	~Quicksort();

	// Inherited via SortingAlgo
	virtual void Sort() override;

private:
	void Run();
	void Quick(std::vector<SortingElement*>  elements, int left, int right);
	
	void AddStep(StepData data, BubbleStepType stepType);
	std::vector<BubbleStep> simulationSteps_;
};