#pragma once
#include "../algos/pathfinding_algo.h"
#include "../node_element.h"

#include <stack>

class DFS : public PathfindingAlgo
{
public:
	DFS()
	{}

	~DFS()
	{}

	// Inherited via PathfindingAlgo
	virtual void Run() override
	{
		OnSimulationStart();
		Init();
		Solve_DFS();
		SetShortPath();
		RunSimulation();
	}

private:
	void Init()
	{
		int rowSize = grid.size();
		int colSize = grid[0].size();

		for (int x = 0; x < colSize; x++)
		{
			for (int y = 0; y < rowSize; y++)
			{
				//down
				if (y > 0)
					grid[y][x]->Neighbours.push_back(grid[y - 1][x + 0]);

				//up
				if (y < rowSize - 1)
					grid[y][x]->Neighbours.push_back(grid[y + 1][x + 0]);

				//left
				if (x > 0)
					grid[y][x]->Neighbours.push_back(grid[y + 0][x - 1]);

				//right
				if (x < colSize - 1)
					grid[y][x]->Neighbours.push_back(grid[y + 0][x + 1]);
			}
		}
	}

	void Solve_DFS()
	{
		std::stack<NodeElement*> stack;
		stack.push(startNode);
		while (!stack.empty())
		{
			NodeElement* node = stack.top();
			node->IsVisited = true;
			stack.pop();

			for (auto neighbor : node->Neighbours)
			{
				if (!neighbor->IsVisited && !neighbor->IsWall())
				{
					stack.push(neighbor);
					AddStep(StepData(neighbor), NodeStep::Type::SelectNode);
					neighbor->PreviousNode = node;
					if (node == finalNode)
					{
						return;
					}
				}
			}
		}
	}

	void SetShortPath()
	{
		NodeElement* currentNode = finalNode;
		while (currentNode != nullptr) {
			AddStep(StepData(currentNode), NodeStep::Type::FinalRoute);
			currentNode = currentNode->PreviousNode;
		}
	}
};