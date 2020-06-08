#pragma once

#include "../algos/pathfinding_algo.h"
#include "../node_element.h"
#include "../simulation/dijkstra_step.h"

#include <iostream>

class DijkstraSimulation : public PathfindingAlgo
{
public:
	DijkstraSimulation()
	{

	}

	~DijkstraSimulation()
	{

	}

	void SetStartNode(NodeElement* node){startNode_ = node;}
	void SetFinalNode(NodeElement* node){finalNode_ = node;}
	void SetGrid(std::vector<std::vector<NodeElement*>> grid){grid_ = grid;}

	void RunDijkstra()
	{
		std::vector<NodeElement*>* visitedNodesInOrder = DBG_NEW std::vector<NodeElement*>();
		dijkstra(visitedNodesInOrder);

		// Add searching nodes int osteps
		for (auto node : *visitedNodesInOrder)
		{
			if(node != startNode_ && node != finalNode_)
				AddStep(StepData(node), DijkstraStep::Type::SelectNode);
		}

		// Add shortest path into steps
		std::vector<NodeElement*>* nodesInShortestPathOrder = DBG_NEW std::vector<NodeElement*>();
		getNodesInShortestPathOrder(nodesInShortestPathOrder);
		for (auto node : *nodesInShortestPathOrder)
		{
			AddStep(StepData(node), DijkstraStep::Type::FinalRoute);
		}

		delete visitedNodesInOrder;
		delete nodesInShortestPathOrder;

		RunSimulation();
	}

private:
	void dijkstra(std::vector<NodeElement*>* visitedNodesInOrder)
	{
		startNode_->Distance = 0;
		std::vector<NodeElement*> unvisitedNodes = getAllNodes(grid_);
		while(unvisitedNodes.size() > 0)
		{
			sortNodesByDistance(&unvisitedNodes);
			NodeElement* closestNode = unvisitedNodes[0];
			unvisitedNodes.erase(unvisitedNodes.begin());

			//if its there wall we will skip
			if (closestNode->IsWall)continue;

			if (closestNode->Distance == 999)
				continue;
			
			closestNode->IsVisited = true;
			visitedNodesInOrder->push_back(closestNode);

			if (closestNode->Index == finalNode_->Index)
				return;

			updateUnvisitedNeighbors(closestNode, grid_);
		}
	}

	void updateUnvisitedNeighbors(NodeElement* node, std::vector<std::vector<NodeElement*>> grid)
	{
		std::vector<NodeElement*>* unvisitedNeighbors = DBG_NEW std::vector<NodeElement*>();
		getUnvisitedNeighbors(unvisitedNeighbors, node, grid);
		for (auto neighbor : *unvisitedNeighbors)
		{
			if (neighbor->IsWall)continue;
			neighbor->Distance = node->Distance + 1;
			neighbor->PreviousNode = node;
		}
		delete unvisitedNeighbors;
	}

	void getUnvisitedNeighbors(std::vector<NodeElement*>* unvisitedNeighboards, NodeElement* node, std::vector<std::vector<NodeElement*>> grid)
	{
		std::vector<NodeElement*> neighbors;
		int col = node->Col;
		int row = node->Row;

		if (row > 0) neighbors.push_back(grid[row - 1][col]);
		if (row < grid.size() -1 )neighbors.push_back(grid[row + 1][col]);
		if (col > 0)neighbors.push_back(grid[row][col - 1]);
		if (col < grid[0].size() - 1)neighbors.push_back(grid[row][col + 1]);

		for (const auto & n : neighbors) {
			if (!n->IsVisited)
			{
				unvisitedNeighboards->push_back(n);
			}
		}
	}

	void sortNodesByDistance(std::vector<NodeElement*>* nodes)
	{
		std::sort(nodes->begin(), nodes->end(), [](NodeElement* a, NodeElement* b) 
		{
			return a->Distance < b->Distance;
		});
	}

	std::vector<NodeElement*> getAllNodes(std::vector<std::vector<NodeElement*>> grid)
	{
		std::vector<NodeElement*> nodes;
		for (auto row : grid)
		{
			for (auto column : row)
			{
				nodes.push_back(column);
			}
		}
		return nodes;
	}

	void getNodesInShortestPathOrder(std::vector<NodeElement*>* nodesInShortestPathOrder)
	{
		NodeElement* currentNode = finalNode_;
		while (currentNode != nullptr) {
			nodesInShortestPathOrder->push_back(currentNode);
			currentNode = currentNode->PreviousNode;
		}
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

		simulationSteps_[stepIndex_].OnCompletedCallback = std::bind(&DijkstraSimulation::RunSimulation, this);
		simulationSteps_[stepIndex_].Execute();
		stepIndex_++;
	}

	void AddStep(StepData data, DijkstraStep::Type stepType)
	{
		simulationSteps_.push_back(DijkstraStep(data, stepType));
	}

private:
	int stepIndex_ = 0;
	std::vector<DijkstraStep> simulationSteps_;
	NodeElement* startNode_;
	NodeElement* finalNode_;
	std::vector<std::vector<NodeElement*>> grid_;
	const int rowSize_ = 20;
	const int colSize_ = 35;
};