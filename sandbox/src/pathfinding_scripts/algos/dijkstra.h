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

	int x = 5;
	int y = 5;
	int xy = 25;
	void SetCostMatrix(int** board)
	{
		valueMatrix_ = board;
		for (int i = 0; i < xy; i++)
		{
			//todo: add default settings
			//default settings 
			visited[i] = 0;
			preD[i] = 0;

			for (int j = 0; j < xy; j++)
			{
				std::cout << valueMatrix_[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	void SetNodeArr(NodeElement grid[5][5])
	{
		//transform data grid into sorting data array
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				arr[i][j] = grid[i][j];
			}
		}
	}

	void DijkstraAlgo()
	{
		// prechadzam tabulku od vrchu na dol
		for (int matrixRowX = 0; matrixRowX < xy; matrixRowX++)
		{
			min = 999;

			//prechadzam tabulku z lava do prava a hladam najkratsiu cestu
			for (int matrixRowY = 0; matrixRowY < xy; matrixRowY++)
			{
	/*			if(valueMatrix_[matrixRowX][matrixRowY] < 999)
				{
					int value = valueMatrix_[matrixRowX][matrixRowY];
					AddStep(StepData(matrixRowX, matrixRowY, matrixRowY), DijkstraStep::Type::Coloring);
					std::cout << "NodeNumber: " << matrixRowY << std::endl;
				}*/

				//AddStep(StepData(matrixRowX, matrixRowY, matrixRowY), DijkstraStep::Type::Coloring);

				if(valueMatrix_[matrixRowX][matrixRowY] == 1){
					std::cout << "NodeNumber: " << matrixRowY << std::endl;
					//AddStep(StepData(matrixRowX, matrixRowY, matrixRowY), DijkstraStep::Type::Coloring);
				}
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
			for (int i = 0; i < xy; i++)
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
		for (int i = 0; i < xy; i++)
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
		for (int i = 0; i < xy; i++)
		{
			std::cout << "|" << distance[i];
		}
		std::cout << "|" << std::endl;

		int j = 0;
		for (int i = 0; i < xy; i++)
		{
			if (i != 0)
			{
				std::cout << "DestinationNode: " << i;
				j = i;
				//if (arr[i][j].IsWall)
				//{
				//	std::cout << " WALL " << std::endl;
				//	continue;
				//}
				//else
				{
					do
					{
						j = preD[j];
						std::cout << " <- " << j;
					} while (j != 0);
				}

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

		int j = DestinationNode;
		do
		{
			j = preD[j];
			std::cout << " <- " << j;
			
			if(j!= SourceNode)
				parent->push_back(j);

		} while (j != 0 );

		//display(parent);
		Run();
	}

public:
	int SourceNode = 0;
	int DestinationNode = 0;

private:

	//distance matrix
	int** valueMatrix_;
	int min = 999;
	int visited[25];
	int distance[25];

	int nextNode = 0;
	int preD[25];

	//elements arr
	NodeElement arr[5][5];

	void Run() 
	{
		//if (StepIndex >= simulationSteps_.size())
		//{
		//	LOG_INFO("Done");
		//	//SetElementsColor(Ugine::Color::SortedElement());
		//	//OnSimulationDone();
		//	return;
		//}

		//simulationSteps_[StepIndex].OnCompletedCallback = std::bind(&Dijkstra::Run, this);
		//simulationSteps_[StepIndex].Execute();
		//StepIndex++;
	}

	void AddStep(StepData data, DijkstraStep::Type stepType)
	{
		//simulationSteps_.push_back(DijkstraStep(arr, data, stepType));
	}

	int StepIndex = 0;
	//std::vector<DijkstraStep> simulationSteps_;


};