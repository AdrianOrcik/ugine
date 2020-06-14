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
		Solve_AStar();
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

	void Solve_AStar()
	{
		//TODO: check calculation
		auto distance = [](NodeElement* a, NodeElement* b) // For convenience
		{
			return sqrtf((a->Row - b->Row)*(a->Row - b->Row) + (a->Col - b->Col)*(a->Col - b->Col));
		};

		auto heuristic = [distance](NodeElement* a, NodeElement* b) // So we can experiment with heuristic
		{
			return distance(a, b);
		};

		// Setup start node
		NodeElement* currentNode = startNode;
		startNode->LocalDistance = 0;
		startNode->GlobalDistance = heuristic(startNode, finalNode);
		AddStep(StepData(startNode), NodeStep::Type::SelectNode);

		//Add start node into list of not tested nodes
		std::vector<NodeElement*>* listNotTestedNodes = new std::vector<NodeElement*>();
		listNotTestedNodes->push_back(startNode);

		// If I have some other discovered but not tested nodes there is chance I can find shorter path
		while (!listNotTestedNodes->empty() && currentNode != finalNode) // Find absolutely shortest path // && currentNode != finalNode_
		{
			// Sort untested nodes by global distance
			std::sort(listNotTestedNodes->begin(), listNotTestedNodes->end(), [](NodeElement* a, NodeElement*b)
			{
				return a->GlobalDistance < b->GlobalDistance;
			});

			// On the beginning is nodes with shortest distance value
			while (!listNotTestedNodes->empty() && listNotTestedNodes->front()->IsVisited)
			{
				// After I visited a node remove it
				listNotTestedNodes->front() = std::move(listNotTestedNodes->back());
				listNotTestedNodes->pop_back();
			}

			// If I dont have more nodes for testing break
			if (listNotTestedNodes->empty())
				break;

			// If I have some node so select and mark as visited
			currentNode = listNotTestedNodes->front();
			currentNode->IsVisited = true;

			// Iterate through neighbours
			for (auto neighbour : currentNode->Neighbours)
			{
				// If I found reguler node add to my not tested structure
				if (!neighbour->IsWall() && !neighbour->IsVisited)
				{
					AddStep(StepData(neighbour), NodeStep::Type::SelectNode);
					listNotTestedNodes->push_back(neighbour);
				}

				// Calculation of potential shortest path
				float possiblyLowerDistance = currentNode->LocalDistance + distance(currentNode, neighbour);

				// If neighbour has higher distance we will calculate neighbour distance
				if (possiblyLowerDistance < neighbour->LocalDistance)
				{
					neighbour->Parent = currentNode;
					neighbour->LocalDistance = possiblyLowerDistance;

					// Recalculation of shortest path into target node
					neighbour->GlobalDistance = neighbour->LocalDistance + heuristic(neighbour, finalNode);
				}
			}
		}
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