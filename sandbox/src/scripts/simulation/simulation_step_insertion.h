#pragma once

#include "ugine/coroutines/routines/wait_seconds.h"

#include "../simulation/simulation_step.h"
#include "../routines/swap_routine.h"
#include "../routines/insert_routine.h"

enum InsertionStepType
{
	SelectPivot,
	SelectElement,
	Insert
};

//TODO: introduce new color for actual transforming element instead of red
class InsertionStep : public SimulationStep
{
public:
	InsertionStep(SortingAlgo* algo, StepData data, InsertionStepType stepType);
	~InsertionStep();

	// Inherited via SimulationStep
	virtual void Execute() override;

private:
	void PivotSelect();
	void ElementSelect();
	void Insertion();

private:
	InsertionStepType stepType_;
};