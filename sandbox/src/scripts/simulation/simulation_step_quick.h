#pragma once

#include "ugine/coroutines/routines/wait_seconds.h"

#include "../simulation/simulation_step.h"
#include "../routines/swap_routine.h"

class QuickStep : public SimulationStep
{
public:
	enum Type
	{
		SelectElement,
		SelectPivot,
		SelectRange,
		BeforeSwap,
		Swap,
		AfterSwap,
	};

	QuickStep(SortingAlgo* algo, StepData data, Type stepType);
	~QuickStep();

	// Inherited via SimulationStep
	virtual void Execute() override;

private:
	Type stepType_;

	void OnSelectPivot();
	void OnSelectElement();
	void OnSelectRange();
	void OnBeforeSwap();
	void OnSwap();
	void OnAfterSwap();
};