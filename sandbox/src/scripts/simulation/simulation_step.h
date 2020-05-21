#pragma

#include "../algos/sorting_algo.h"

#include <functional>

struct StepData
{
	int positionA;
	int positionB;

	StepData() {}
	StepData(int posA, int posB = -1)
		:positionA(posA), positionB(posB)
	{}
};

class SortingAlgo;
class SimulationStep
{
public:
	SimulationStep() {}
	~SimulationStep() {}

	virtual void Execute() = 0;

public:
	std::function<void()> OnCompletedCallback;

protected:
	void OnCompleted()
	{
		OnCompletedCallback();
	}

protected:
	SortingAlgo* sortingAlgo_;
	StepData data_;

};