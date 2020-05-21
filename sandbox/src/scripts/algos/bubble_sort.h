#pragma once
#include "sorting_algo.h"

#include "ugine/coroutines/routine_manager.h"
#include "ugine/coroutines/routines/wait_seconds.h"

#include "../routines/swap_routine.h"
#include "../simulation/simulation_step_bubble.h"

class BubbleSort : public SortingAlgo
{
public:
	BubbleSort();
	~BubbleSort();

	// Inherited via SortingAlgo
	virtual void Sort() override;

private:
	void Run();
	//void SelectElements();
	//void SwapElements();
	//void UnselectElements();

	void AddStep(StepData data, BubbleStepType stepType);
	std::vector<BubbleStep> simulationSteps_;
};