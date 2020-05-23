#pragma once

#include "ugine/coroutines/routines/wait_seconds.h"

#include "../simulation/simulation_step.h"
#include "../routines/swap_routine.h"



class SelectionStep : public SimulationStep
{
public:
	enum Type
	{
		Select,
		SelectPivot,
		BeforeSwap,
		Swap,
		AfterSwap,
	};

	SelectionStep(SortingAlgo* algo, StepData data, Type stepType);
	~SelectionStep();

	// Inherited via SimulationStep
	virtual void Execute() override;

private:
	Type stepType_;

	void OnSelectPivot();
	void OnSelect();
	void OnBeforeSwap();
	void OnSwap();
	void OnAfterSwap();
};