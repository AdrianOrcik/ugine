#pragma once

#include "../algos/pathfinding_algo.h"
#include "../node_element.h"

#include <iostream>

class BFS : public PathfindingAlgo
{
public:
	BFS()
	{
	}

	~BFS()
	{}

	// Inherited via PathfindingAlgo
	void Run() override
	{
		OnSimulationStart();
		Init();
		Solve_BFS();
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

				//Left
				if (x > 0)
					grid[y][x]->Neighbours.push_back(grid[y + 0][x - 1]);

				//Right
				if (x < colSize - 1)
					grid[y][x]->Neighbours.push_back(grid[y + 0][x + 1]);
			}
		}
	}

	void Solve_BFS()
	{
		std::queue<NodeElement*> queue;

		// Push startNode into queue
		queue.push(startNode);
		startNode->IsVisited = true;

		// Iterating until queue is empty
		while (!queue.empty())
		{
			NodeElement* node = queue.front();
			queue.pop();

			// Take node from front and iterate throught neighbours
			std::vector<NodeElement*> neighbours = node->Neighbours;

			// If I found final node search is on end
			if (node == finalNode)
				return;

			for (auto neighbor : neighbours)
			{
				// If I found non-visited node I am push into queue and update previous node
				if (!neighbor->IsVisited && !neighbor->IsWall())
				{
					queue.push(neighbor);
					AddStep(StepData(neighbor), NodeStep::Type::SelectNode);
					neighbor->PreviousNode = node;
					neighbor->IsVisited = true;
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