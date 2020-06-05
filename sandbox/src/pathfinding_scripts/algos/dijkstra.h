#pragma once
#include "../algos/pathfinding_algo.h"
#include "../node_element.h"
#include "../simulation/dijkstra_step.h"

#include <iostream>

class Dijkstra: public PathfindingAlgo
{
public:
	Dijkstra()
	{}

	~Dijkstra()
	{}

	void SetCostMatrix(int** board)
	{
		valueMatrix_ = board;
		for (int i = 0; i < 9; i++)
		{
			//todo: add default settings
			//default settings 
			visited[i] = 0;
			preD[i] = 0;

			for (int j = 0; j < 9; j++)
			{
				std::cout << valueMatrix_[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	void SetNodeArr(NodeElement grid[3][3])
	{
		//transform data grid into sorting data array
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				arr[i][j] = grid[i][j];
			}
		}
	}

	void DijkstraAlgo()
	{
		// prechadzam tabulku od vrchu na dol
		for (int matrixRowX = 0; matrixRowX < 9; matrixRowX++)
		{
			min = 999;

			//prechadzam tabulku z lava do prava a hladam najkratsiu cestu
			for (int matrixRowY = 0; matrixRowY < 9; matrixRowY++)
			{
				// ak som nasiel najkratsiu cestu a este nebol na tom node tak si ho oznacim
				if (min > distance[matrixRowY] && visited[matrixRowY] != 1)
				{
					// tmp si to poznacim
					min = distance[matrixRowY];
					nextNode = matrixRowY;
				}
			}

			//aktualny node oznacim ako navstiveny
			visited[nextNode] = 1;

			//dijkstra 
			for (int i = 0; i < 9; i++)
			{
				//hladam medzi nodami ktore som este nepozrel
				if (visited[i] != 1)
				{
					//TODO: este to debugnut
					// check if min + distance je menej ako distance zo zaciatocneho bodu
					if (min + valueMatrix_[nextNode][i] < distance[i])
					{
						//ulozit novu vzdialenost
						distance[i] = min + valueMatrix_[nextNode][i];
						//ulozim predchadzajuci node
						preD[i] = nextNode;
					}
				}
			}
		}
	}

	void Init()
	{
		//default settings
		//zobratie distance prvy riadok
		for (int i = 0; i < 9; i++)
		{
			distance[i] = valueMatrix_[0][i];
		}

		//nastavenie ze som navstivil prvy riadok
		visited[0] = 1;
		// nastavit default distance lebo vychadzam zo source nodu
		distance[0] = 0;
	}

	void Output()
	{
		// output
		for (int i = 0; i < 9; i++)
		{
			std::cout << "|" << distance[i];
		}
		std::cout << "|" << std::endl;

		int j = 0;
		for (int i = 0; i < 9; i++)
		{
			if (i != 0)
			{
				std::cout << "Path: " << i + 1;
				j = i;
				do
				{
					j = preD[j];
					std::cout << " <- " << j + 1;
				} while (j != 0);
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}


	void Find(std::vector<int>* parent)
	{
		Init();
		DijkstraAlgo();
		Output();
		//display(parent);
		//Run();
	}

//public:
//	int SourceNode = 0;
//	int DestinationNode = 0;

private:

	//distance matrix
	int** valueMatrix_;
	int min = 999;
	int visited[9];
	int distance[9];

	int nextNode = 0;
	int preD[9];

	//elements arr
	NodeElement arr[3][3];

	void Run() 
	{
		if (StepIndex >= simulationSteps_.size())
		{
			LOG_INFO("Done");
			//SetElementsColor(Ugine::Color::SortedElement());
			//OnSimulationDone();
			return;
		}

		simulationSteps_[StepIndex].OnCompletedCallback = std::bind(&Dijkstra::Run, this);
		simulationSteps_[StepIndex].Execute();
		StepIndex++;
	}

	void AddStep(StepData data, DijkstraStep::Type stepType)
	{
		simulationSteps_.push_back(DijkstraStep(arr, data, stepType));
	}

	int StepIndex = 0;
	std::vector<DijkstraStep> simulationSteps_;


};