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

		//setup starting condition
		NodeElement* currentNode = startNode;
		startNode->LocalDistance = 0;
		startNode->GlobalDistance = heuristic(startNode, finalNode);

		AddStep(StepData(startNode), NodeStep::Type::SelectNode);

		//add start node to not tested list yet
		std::vector<NodeElement*>* listNotTestedNodes = new std::vector<NodeElement*>();
		listNotTestedNodes->push_back(startNode);

		//pokial mam nejake objavene a netestovane nody v liste, je sanca ze existuje este kratsia cesta
		while (!listNotTestedNodes->empty() && currentNode != finalNode) // Find absolutely shortest path // && currentNode != finalNode_
		{
			//sort untested notes by global distance
			std::sort(listNotTestedNodes->begin(), listNotTestedNodes->end(), [](NodeElement* a, NodeElement*b)
			{
				return a->GlobalDistance < b->GlobalDistance;
			});

			//na zaciatku listu je potencionalne s najkratsou vzdialenostou 
			while (!listNotTestedNodes->empty() && listNotTestedNodes->front()->IsVisited)
			{
				//ak uz som navstivil node tak ho vyhodim z listu
				listNotTestedNodes->front() = std::move(listNotTestedNodes->back());
				listNotTestedNodes->pop_back();
			}

			//ak neostal v liste ziaden node tak vyskocime z loopu
			if (listNotTestedNodes->empty())
				break;

			//ak nieco ostalo tak zoberem zo zaciatku a oznacim node ako navstiveny
			currentNode = listNotTestedNodes->front();
			currentNode->IsVisited = true;

			//pozrem kazdy susedny node
			for (auto neighbour : currentNode->Neighbours)
			{
				//ak sused este neni navstiveny a neni ani obstacle 
				if (!neighbour->IsWall() && !neighbour->IsVisited)
				{
					AddStep(StepData(neighbour), NodeStep::Type::SelectNode);
					listNotTestedNodes->push_back(neighbour);
				}

				// kalkulacia susedov aby som nasiel potencionalne najkratsiu cestu
				float possiblyLowerDistance = currentNode->LocalDistance + distance(currentNode, neighbour);

				//ak sme vybrali cestu s najkratsou vzdialenostou, suset nastavi hodnoty prepoctu 
				//ako je localdistance a globalDistance
				if (possiblyLowerDistance < neighbour->LocalDistance)
				{
					neighbour->Parent = currentNode;
					neighbour->LocalDistance = possiblyLowerDistance;

					//prepocita sa najkratsia cesta k cielu
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