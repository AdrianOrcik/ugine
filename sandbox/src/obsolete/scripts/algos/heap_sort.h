#pragma once
#include "sorting_algo.h"

#include "ugine/coroutines/routine_manager.h"
#include "ugine/coroutines/routines/wait_seconds.h"

#include "../routines/swap_routine.h"
#include "../simulation/simulation_step_heap.h"

class HeapSort : public SortingAlgo
{
public:
	HeapSort();
	~HeapSort();

	// Inherited via SortingAlgo
	virtual void Sort() override;

private:
	void Run();
	void Heap(int size);
	void Heapify(int bottom, int topIndex);
	void AddStep(StepData data, HeapStep::Type stepType);
	std::vector<HeapStep> simulationSteps_;
};