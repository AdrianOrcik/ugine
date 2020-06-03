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
	}

	void SetNodeArr(NodeElement grid[35][20])
	{
		for (int i = 0; i < 35; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				arr[i][j] = grid[i][j];
			}
		}
	
	}

	void Init()
	{
		for (int i = 0; i < nodeCount_; i++)
		{
			path_[i] = i;
			distanceArr_[i] = INT_MAX;
		}
		distanceArr_[SourceNode] = 0;
	}

	void DijkstraAlgo()
	{
		for (int i = 0; i < nodeCount_; i++)
		{
			int nearest = GetNearst();
			isVisitedNodes[nearest] = true;
			for (int adj = 0; adj < nodeCount_; adj++)
			{
				if(nearest < 35 && adj < 20)
				{
					//Ugine::RendererComponent* rednerer = 
					//	(Ugine::RendererComponent*)arr[nearest][adj].owner->GetComponent<Ugine::RendererComponent>();
					//rednerer->SetColor(Ugine::Color::Blue());

					AddStep(StepData(nearest, adj), DijkstraStep::Type::Coloring);
				}

				if (valueMatrix_[nearest][adj] != INT_MAX &&
					distanceArr_[adj] > (distanceArr_[nearest] + valueMatrix_[nearest][adj]))
				{
					distanceArr_[adj] = distanceArr_[nearest] + valueMatrix_[nearest][adj];
					path_[adj] = nearest;
				}
			}
		}
	}

	int GetNearst()
	{
		int minValue = INT_MAX;
		int minNode = 0;
		for (int i = 0; i < nodeCount_; i++)
		{
			if (!isVisitedNodes[i] && distanceArr_[i] < minValue)
			{
				minValue = distanceArr_[i];
				minNode = i;
			}
		}

		return minNode;
	}

	//Debug
	void display(std::vector<int>* parents)
	{
		std::cout << "Node:\t\t\tCost:\t\t\tPath:";
		std::cout << std::endl;
		for (int i = 0; i < nodeCount_; i++)
		{
			std::cout << i << "\t\t\t" << distanceArr_[i] << "\t\t\t" << " ";
			std::cout << i << " ";
			int parnode = path_[i];

			while (parnode != SourceNode)
			{
				if (i == DestinationNode)
				{
					parents->push_back(parnode);
				}

				std::cout << " <- " << parnode << " ";
				parnode = path_[parnode];
			}
			std::cout << std::endl;
		}
	}

	void Find(std::vector<int>* parent)
	{
		Init();
		DijkstraAlgo();
		//display(parent);
		Run();
	}

public:
	int SourceNode = 0;
	int DestinationNode = 0;

private:

	int** valueMatrix_;
	int distanceArr_[700];
	bool isVisitedNodes[700] = { 0 };
	int path_[700];
	int nodeCount_ = 700;
	NodeElement arr[35][20];

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