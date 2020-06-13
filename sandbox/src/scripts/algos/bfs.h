#pragma once

#include "../algos/pathfinding_algo.h"
#include "../node_element.h"
#include "../simulation/dijkstra_step.h"

#include <iostream>

class BFS : public PathfindingAlgo
{
public:
	BFS()
	{
	}

	~BFS()
	{}

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

	void Solve_BFS()
	{
		std::queue<NodeElement*> queue;

		queue.push(startNode);
		startNode->IsVisited = true;

		while (!queue.empty())
		{
			NodeElement* node = queue.front();
			queue.pop();

			std::vector<NodeElement*> neighbours = node->Neighbours;
			for (auto neighbor : neighbours)
			{
				if (!neighbor->IsVisited && !neighbor->IsWall())
				{
					queue.push(neighbor);
					AddStep(StepData(neighbor), NodeStep::Type::SelectNode);
					neighbor->PreviousNode = node;
					neighbor->IsVisited = true;
				}
			}

			if (node == finalNode)
				return;
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

	//Inherited via SortingAlgo
	void RunSimulation()
	{
		if (stepIndex_ >= simulationSteps_.size())
		{
			LOG_INFO("Done");

			auto renderer = (Ugine::RendererComponent*)startNode->owner->GetComponent<Ugine::RendererComponent>();
			renderer->SetColor(Ugine::Color::Yellow());

			auto renderer2 = (Ugine::RendererComponent*)finalNode->owner->GetComponent<Ugine::RendererComponent>();
			renderer2->SetColor(Ugine::Color::Yellow());
			
			OnSimulationDone();
			return;
		}

		simulationSteps_[stepIndex_].OnCompletedCallback = std::bind(&BFS::RunSimulation, this);
		simulationSteps_[stepIndex_].Execute();
		stepIndex_++;
	}

	void AddStep(StepData data, NodeStep::Type stepType)
	{
		simulationSteps_.push_back(NodeStep(data, stepType));
	}

private:
	int stepIndex_ = 0;
	std::vector<NodeStep> simulationSteps_;
};