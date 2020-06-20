#pragma once

#include "ugine.h"

#include "ugine/coroutines/routines/wait_seconds.h"
#include "../routines/fade_to_color_routine.h"
#include "../simulation/simulation_step.h"
#include "../node_element.h"

class NodeStep : public SimulationStep
{
public:
	enum Type
	{
		SelectNode,
		FinalRoute,
	};
	NodeStep(StepData data, NodeStep::Type stepType);
	~NodeStep();

	// Inherited via SimulationStep
	virtual void Execute() override;

private:
	Type stepType_;
	void OnSelectNode();
	void OnDrawFinalRoute();
};