#pragma once

#include "sorting_algo.h"

#include "ugine/coroutines/routine_manager.h"
#include "ugine/coroutines/routines/wait_seconds.h"

#include "../routines/swap_routine.h"
#include "../simulation/simulation_step_selection.h"

class SelectionSort : public SortingAlgo
{
public:
	SelectionSort();
	~SelectionSort();

	// Inherited via SortingAlgo
	virtual void Sort() override;

private:

	void Run();
	//void SelectElements();
	//void BeforeFindNewSelection();
	//void SwapElements();
	//void AfterSwapElements();
	//void DelaySelection();

	////TODO: refactor
	//int firstElementIndex_ = 0;
	//bool newIteration = false;
	void AddStep(StepData data, SelectionStep::Type stepType);
	std::vector<SelectionStep> simulationSteps_;
};