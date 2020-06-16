#pragma once
#include "../algos/pathfinding_algo.h"
#include "../node_element.h"
#include "../definition.h"

#include <iostream>

class Dijkstra : public PathfindingAlgo
{
public:
	Dijkstra()
	{

	}

	~Dijkstra()
	{
		delete visitedNodesInOrder;
		delete nodesInShortestPathOrder;
	}

	// Inherited via PathfindingAlgo
	virtual void Run() override
	{
		OnSimulationStart();

		visitedNodesInOrder = DBG_NEW std::vector<NodeElement*>();
		Solve_Dijkstra(visitedNodesInOrder);

		// Add searching nodes into steps
		for (auto node : *visitedNodesInOrder)
		{
			if(node != startNode && node != finalNode)
				AddStep(StepData(node), NodeStep::Type::SelectNode);
		}

		// Add shortest path into steps
		nodesInShortestPathOrder = DBG_NEW std::vector<NodeElement*>();
		GetNodesInShortestPathOrder(nodesInShortestPathOrder);
		for (auto node : *nodesInShortestPathOrder)
		{
			AddStep(StepData(node), NodeStep::Type::FinalRoute);
		}

		RunSimulation();
	}

private:
	void Solve_Dijkstra(std::vector<NodeElement*>* visitedNodesInOrder)
	{
		startNode->Distance = 0;
		std::vector<NodeElement*> unvisitedNodes = GetAllNodes(grid);
		while(unvisitedNodes.size() > 0)
		{
			SortNodesByDistance(&unvisitedNodes);
			NodeElement* closestNode = unvisitedNodes[0];
			unvisitedNodes.erase(unvisitedNodes.begin());

			// If there is wall or no closer node continue
			if (closestNode->IsWall() || closestNode->Distance == MAX_DISTANCE)continue;

			// Visit node and check if its final node
			closestNode->IsVisited = true;
			visitedNodesInOrder->push_back(closestNode);
			if (closestNode->Index == finalNode->Index)
				return;

			// Update unvisited neighbours by distance
			UpdateUnvisitedNeighbors(closestNode, grid);
		}
	}

	void UpdateUnvisitedNeighbors(NodeElement* node, std::vector<std::vector<NodeElement*>> grid)
	{
		std::vector<NodeElement*>* unvisitedNeighbors = DBG_NEW std::vector<NodeElement*>();
		GetUnvisitedNeighbors(unvisitedNeighbors, node, grid);
		for (auto neighbor : *unvisitedNeighbors)
		{
			if (neighbor->IsWall())continue;
			neighbor->Distance = node->Distance + 1;
			neighbor->PreviousNode = node;
		}
		delete unvisitedNeighbors;
	}

	void GetUnvisitedNeighbors(std::vector<NodeElement*>* unvisitedNeighboards, NodeElement* node, std::vector<std::vector<NodeElement*>> grid)
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

	void SortNodesByDistance(std::vector<NodeElement*>* nodes)
	{
		std::sort(nodes->begin(), nodes->end(), [](NodeElement* a, NodeElement* b) 
		{
			return a->Distance < b->Distance;
		});
	}

	std::vector<NodeElement*> GetAllNodes(std::vector<std::vector<NodeElement*>> grid)
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

	void GetNodesInShortestPathOrder(std::vector<NodeElement*>* nodesInShortestPathOrder)
	{
		NodeElement* currentNode = finalNode;
		while (currentNode != nullptr) {
			nodesInShortestPathOrder->push_back(currentNode);
			currentNode = currentNode->PreviousNode;
		}
	}

private:
	std::vector<NodeElement*>* visitedNodesInOrder = nullptr;
	std::vector<NodeElement*>* nodesInShortestPathOrder = nullptr;
};