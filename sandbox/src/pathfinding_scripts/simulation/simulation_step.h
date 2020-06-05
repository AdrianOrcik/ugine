#pragma once
#include <functional>
#include "../node_element.h"
struct StepData
{
	int positionX;
	int positionY;
	int nodePosition;

	StepData() 
		:positionX(0), positionY(0)
	{}

	StepData(int posX, int posY, int nodePosition)
		:positionX(posX), positionY(posY), nodePosition(nodePosition)
	{}
};

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

	void CopyToGrid(NodeElement grid[5][5])
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				grid_[i][j] = grid[i][j];
			}
		}
	}

public:
	StepData data_;
	NodeElement grid_[5][5];
};