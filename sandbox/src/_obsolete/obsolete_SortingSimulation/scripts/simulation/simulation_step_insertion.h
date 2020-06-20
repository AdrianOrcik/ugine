#pragma once

#include "ugine/coroutines/routines/wait_seconds.h"

#include "../simulation/simulation_step.h"
#include "../routines/swap_routine.h"
#include "../routines/insert_routine.h"

//TODO: introduce new color for actual transforming element instead of red
class InsertionStep : public SimulationStep
{
public:
	enum Type
	{
		SelectPivot,
		SelectElement,
		Insert
	};

	InsertionStep(SortingAlgo* algo, StepData data, InsertionStep::Type stepType);
	~InsertionStep();

	// Inherited via SimulationStep
	virtual void Execute() override;

private:
	void OnPivotSelect();
	void OnElementSelect();
	void OnInsert();

private:
	Type stepType_;
};