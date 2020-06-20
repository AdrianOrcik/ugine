#pragma once
#include "ugine/coroutines/routines/wait_seconds.h"

#include "../simulation/simulation_step.h"
#include "../routines/swap_routine.h"

class MergeStep : public SimulationStep
{
public:
	enum Type
	{
		SelectRange,
		BeforeOverride,
		OverrideValue,
		AfterOverride,
	};

	MergeStep(SortingAlgo* algo, StepData data, Type stepType);
	~MergeStep();

	// Inherited via SimulationStep
	virtual void Execute() override;

private:
	Type stepType_;

	void OnSelectRange();
	void OnBeforeOverride();
	void OnOverrideValue();
	void OnAfterOverride();
};