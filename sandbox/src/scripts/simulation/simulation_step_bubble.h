#pragma once

#include "ugine/coroutines/routines/wait_seconds.h"

#include "../simulation/simulation_step.h"
#include "../routines/swap_routine.h"

enum BubbleStepType
{
	S_Select,
	S_BeforeSwap,
	S_Swap,
	S_AfterSwap
};

class BubbleStep : public SimulationStep
{
public:
	BubbleStep(SortingAlgo* algo, StepData data, BubbleStepType stepType);
	~BubbleStep();

	// Inherited via SimulationStep
	virtual void Execute() override;

private:
	BubbleStepType stepType_;

	void ElementSelect();
	void BeforeSwap();
	void Swap();
	void AfterSwap();
};