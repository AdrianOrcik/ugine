#pragma once
#include <functional>
#include "../node_element.h"
struct StepData
{
	int positionX;
	int positionY;

	StepData() 
		:positionX(0), positionY(0)
	{}

	StepData(int posX, int posY)
		:positionX(posX), positionY(posY)
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

	void CopyToGrid(NodeElement grid[35][20])
	{
		for (int i = 0; i < 35; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				grid_[i][j] = grid[i][j];
			}
		}
	}

public:
	StepData data_;
	NodeElement grid_[35][20];
};