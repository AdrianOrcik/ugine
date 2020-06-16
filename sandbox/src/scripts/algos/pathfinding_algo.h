#pragma once
#include "ugine.h"
#include "../simulation/node_step.h"

class PathfindingAlgo
{
public:
	void SetStartNode(NodeElement* _node) { startNode = _node; }
	void SetFinalNode(NodeElement* _node) { finalNode = _node; }
	void SetGrid(std::vector<std::vector<NodeElement*>> _grid) 
	{ 
		grid = _grid; 
	}

	std::function<void()> OnSimulationStart;
	std::function<void()> OnSimulationDone;
	std::function<void()> OnSimulationInterrupt;

	virtual void Run() = 0;

protected:
	void RunSimulation()
	{
		if (stepIndex_ >= simulationSteps_.size())
		{
			OnSimulationDone();
			return;
		}

		simulationSteps_[stepIndex_].OnCompletedCallback = std::bind(&PathfindingAlgo::RunSimulation, this);
		simulationSteps_[stepIndex_].Execute();
		stepIndex_++;
	}

	void AddStep(StepData data, NodeStep::Type stepType)
	{
		if (data.Node->IsStartOrEnd())return;
		simulationSteps_.push_back(NodeStep(data, stepType));
	}

protected:
	int stepIndex_ = 0;
	std::vector<NodeStep> simulationSteps_;

	NodeElement* startNode = nullptr;
	NodeElement* finalNode = nullptr;
	std::vector<std::vector<NodeElement*>> grid;
};