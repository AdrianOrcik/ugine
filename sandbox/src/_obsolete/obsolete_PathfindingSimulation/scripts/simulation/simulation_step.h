#pragma once
#include <functional>
#include "../node_element.h"
struct StepData
{
	NodeElement* Node;

	StepData(){}
	StepData(NodeElement* node)
	{
		Node = node;
	}
};

class SimulationStep
{
public:
	SimulationStep(){}
	~SimulationStep() {}
	virtual void Execute() = 0;

public:
	std::function<void()> OnCompletedCallback;

protected:
	void OnCompleted()
	{
		OnCompletedCallback();
	}

public:
	StepData data_;
};