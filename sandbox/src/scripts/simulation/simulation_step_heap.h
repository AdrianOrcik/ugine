#pragma once


#include "ugine/coroutines/routines/wait_seconds.h"

#include "../simulation/simulation_step.h"
#include "../routines/swap_routine.h"

//TODO: add heap sort selection animation 
class HeapStep : public SimulationStep
{
public:
	enum Type
	{
		BeforeSwap,
		Swap,
		AfterSwap,
	};

	HeapStep(SortingAlgo* algo, StepData data, Type stepType);
	~HeapStep();

	// Inherited via SimulationStep
	virtual void Execute() override;

private:
	Type stepType_;

	void OnBeforeSwap();
	void OnSwap();
	void OnAfterSwap();
};