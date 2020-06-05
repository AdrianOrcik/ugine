#pragma once

#include "ugine.h"

#include "ugine/coroutines/routines/wait_seconds.h"

#include "../simulation/simulation_step.h"
#include "../node_element.h"

class DijkstraStep : public SimulationStep
{
public:
	enum Type
	{
		Coloring,
	};

	DijkstraStep(NodeElement grid[3][3], StepData data, DijkstraStep::Type stepType);
	~DijkstraStep();

	// Inherited via SimulationStep
	virtual void Execute() override;

private:
	Type stepType_;

	void OnColoring();
};