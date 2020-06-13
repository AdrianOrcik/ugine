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

	void SetStartNode(NodeElement* node) { startNode_ = node; }
	void SetFinalNode(NodeElement* node) { finalNode_ = node; }
	void SetGrid(std::vector<std::vector<NodeElement*>> grid) { grid_ = grid; }

	void InitData()
	{
		int rowSize = grid_.size();
		int colSize = grid_[0].size();

		for (int x = 0; x < colSize; x++)
		{
			for (int y = 0; y < rowSize; y++)
			{
				//down
				if (y > 0)
					grid_[y][x]->Neighbours.push_back(grid_[y - 1][x + 0]);

				//up
				if (y < rowSize - 1)
					grid_[y][x]->Neighbours.push_back(grid_[y + 1][x + 0]);

				//left
				if (x > 0)
					grid_[y][x]->Neighbours.push_back(grid_[y + 0][x - 1]);

				//right
				if (x < colSize - 1)
					grid_[y][x]->Neighbours.push_back(grid_[y + 0][x + 1]);
			}
		}
	}

	void Solve()
	{
		std::queue<NodeElement*> q;

		q.push(startNode_);
		startNode_->IsVisited = true;

		while (!q.empty())
		{
			NodeElement* node = q.front();
			q.pop();
			std::vector<NodeElement*> neighbours = node->Neighbours;

			for (auto neighbor : neighbours)
			{
				if (!neighbor->IsVisited && !neighbor->IsWall())
				{
					q.push(neighbor);
					//neighbor->Distance = node->Distance + 1;
					AddStep(StepData(neighbor), DijkstraStep::Type::SelectNode);
					neighbor->PreviousNode = node;
					neighbor->IsVisited = true;
				}
			}

			if (node == finalNode_)
				return;
		}
	}

	void RunBFS()
	{
		InitData();
		Solve();

		NodeElement* currentNode = finalNode_;
		while (currentNode != nullptr) {
			//nodesInShortestPathOrder->push_back(currentNode);
			AddStep(StepData(currentNode), DijkstraStep::Type::FinalRoute);
			currentNode = currentNode->PreviousNode;
		}

		RunSimulation();
	}

	//Inherited via SortingAlgo
	void RunSimulation()
	{
		if (stepIndex_ >= simulationSteps_.size())
		{
			LOG_INFO("Done");
			//SetElementsColor(Ugine::Color::SortedElement());
			//OnSimulationDone();

			auto renderer = (Ugine::RendererComponent*)startNode_->owner->GetComponent<Ugine::RendererComponent>();
			renderer->SetColor(Ugine::Color::Yellow());

			auto renderer2 = (Ugine::RendererComponent*)finalNode_->owner->GetComponent<Ugine::RendererComponent>();
			renderer2->SetColor(Ugine::Color::Yellow());
			return;
		}

		simulationSteps_[stepIndex_].OnCompletedCallback = std::bind(&BFS::RunSimulation, this);
		simulationSteps_[stepIndex_].Execute();
		stepIndex_++;
	}

	void AddStep(StepData data, DijkstraStep::Type stepType)
	{
		simulationSteps_.push_back(DijkstraStep(data, stepType));
	}

private:
	int stepIndex_ = 0;

	NodeElement* startNode_;
	NodeElement* finalNode_;

	std::vector<DijkstraStep> simulationSteps_;
	std::vector<std::vector<NodeElement*>> grid_;
};