#pragma once

#include "ugine/coroutines/routines/wait_seconds.h"

#include "../simulation/simulation_step.h"
#include "../routines/swap_routine.h"

class BubbleStep : public SimulationStep
{
public:
	enum Type
	{
		Select,
		BeforeSwap,
		Swap,
		AfterSwap
	};

	BubbleStep(SortingAlgo* algo, StepData data, BubbleStep::Type stepType);
	~BubbleStep();

	// Inherited via SimulationStep
	virtual void Execute() override;

private:
	Type stepType_;

	void OnSelect();
	void OnBeforeSwap();
	void OnSwap();
	void OnAfterSwap();
};