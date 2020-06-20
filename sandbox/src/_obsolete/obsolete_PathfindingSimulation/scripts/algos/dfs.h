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

		// Iterate through neighbours and making connections
		for (int x = 0; x < colSize; x++)
		{
			for (int y = 0; y < rowSize; y++)
			{
				// Down
				if (y > 0)
					grid[y][x]->Neighbours.push_back(grid[y - 1][x + 0]);

				// Up
				if (y < rowSize - 1)
					grid[y][x]->Neighbours.push_back(grid[y + 1][x + 0]);

				// Left
				if (x > 0)
					grid[y][x]->Neighbours.push_back(grid[y + 0][x - 1]);

				// Right
				if (x < colSize - 1)
					grid[y][x]->Neighbours.push_back(grid[y + 0][x + 1]);
			}
		}
	}

	void Solve_DFS()
	{
		// Push startNode into stack
		std::stack<NodeElement*> stack;
		stack.push(startNode);

		// Iterating until stack is empty
		while (!stack.empty())
		{
			NodeElement* node = stack.top();
			node->IsVisited = true;
			stack.pop();

			// If I found final node search is on end
			if (node == finalNode)
			{
				return;
			}

			// Take node from front and iterate throught neighbours
			for (auto neighbor : node->Neighbours)
			{
				// If I found non-visited node I am push into stack and update previous node
				if (!neighbor->IsVisited && !neighbor->IsWall())
				{
					stack.push(neighbor);
					AddStep(StepData(neighbor), NodeStep::Type::SelectNode);
					neighbor->PreviousNode = node;
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