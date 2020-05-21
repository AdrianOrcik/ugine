#pragma once

#include "../simulation/simulation_step.h"
#include "../routines/swap_routine.h"
#include "../routines/insert_routine.h"
#include "ugine/coroutines/routines/wait_seconds.h"

enum InsertionStepType
{
	PivotSelection,
	ElementSelection,
	Insertion
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
	void PivotSelection();
	void ElementSelection();
	void Insertion();

private:
	InsertionStepType stepType_;
};