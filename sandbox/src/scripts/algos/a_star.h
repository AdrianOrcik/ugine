#pragma once
#include "../algos/pathfinding_algo.h"
#include "../node_element.h"

#include <iostream>

class AStar : public PathfindingAlgo
{
public:
	AStar()
	{
	}

	~AStar()
	{
	}

	void Run() override
	{
		OnSimulationStart();
		Init();
		AStar_Algo();
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
				// down
				if (y > 0)
					grid[y][x]->Neighbours.push_back(grid[y - 1][x + 0]);

				// up
				if (y < rowSize - 1)
					grid[y][x]->Neighbours.push_back(grid[y + 1][x + 0]);

				// left
				if (x > 0)
					grid[y][x]->Neighbours.push_back(grid[y + 0][x - 1]);

				// right
				if (x < colSize - 1)
					grid[y][x]->Neighbours.push_back(grid[y + 0][x + 1]);
			}
		}
	}

	void AStar_Algo()
	{
	
		auto distance = [](NodeElement* a, NodeElement* b) 
		{
			// pythagoras theorem
			return sqrtf((a->Row - b->Row)*(a->Row - b->Row) + (a->Col - b->Col)*(a->Col - b->Col));
		};

		auto heuristic = [distance](NodeElement* a, NodeElement* b)
		{
			return distance(a, b);
		};

		startNode->FCost = 0.0f;
		startNode->GCost = heuristic(startNode, finalNode);

		std::vector<NodeElement*>* testingNodes = new std::vector<NodeElement*>();
		testingNodes->push_back(startNode);

		// loop until testing nodes exist
		while (testingNodes->size() > 0)
		{
			NodeElement* current = *testingNodes->begin();
			current->IsVisited = true;

			// choose new current node if you find closer node
			for (auto testNode : *testingNodes)
			{
				if (testNode->FCost <= current->FCost)
				{
					if (testNode->HCost < current->HCost)
						current = testNode;
				}
			}

			testingNodes->erase(testingNodes->begin());
			if (current->IsEnd())return;

			// iterate throught neighbours by current node
			for (auto neighbour : current->Neighbours)
			{
				if (neighbour->IsWall() || neighbour->IsVisited)
					continue;

				// recalculation of distance based on current node
				int newCostToNeighbour = current->GCost + heuristic(current, neighbour);
				if (newCostToNeighbour < neighbour->GCost)
				{
					neighbour->GCost = newCostToNeighbour;
					neighbour->HCost = heuristic(neighbour, finalNode);
					neighbour->Parent = current;

					testingNodes->push_back(neighbour);
					AddStep(StepData(neighbour), NodeStep::Type::SelectNode);
				}
			}
		}

		delete testingNodes;
	}

	void SetShortPath()
	{
		NodeElement* currNode = finalNode;
		while (currNode != startNode) 
		{
			AddStep(StepData(currNode), NodeStep::Type::FinalRoute);
			currNode = currNode->Parent;
		}
	}
};