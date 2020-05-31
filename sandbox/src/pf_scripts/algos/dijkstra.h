#pragma once
#include "../algos/pathfinding_algo.h"
#include <iostream>

class Dijkstra: public PathfindingAlgo
{
public:
	Dijkstra()
	{}

	~Dijkstra()
	{}

	int src_ = 0;
	int destination_ = 0;
	int** cost_;
	int dist[100];
	bool visited[100] = { 0 };
	int parent[100];
	int NodeCount = 9;

	void SetCostMatrix(int** board)
	{
		cost_ = board;
	}

	void SetSrc(int src)
	{
		src_ = src;
	}

	void SetDestination(int destination)
	{
		destination_ = destination;
	}

	void Init()
	{
		for (int i = 0; i < NodeCount; i++)
		{
			parent[i] = i;
			dist[i] = INT_MAX;
		}
		dist[src_] = 0;
	}

	void DijkstraAlgo()
	{
		for (int i = 0; i < NodeCount; i++)
		{
			int nearest = GetNearst();
			visited[nearest] = true;
			for (int adj = 0; adj < NodeCount; adj++)
			{
				if (cost_[nearest][adj] != INT_MAX &&
					dist[adj] > (dist[nearest] + cost_[nearest][adj]))
				{
					dist[adj] = dist[nearest] + cost_[nearest][adj];
					parent[adj] = nearest;
				}
			}
		}
	}

	int GetNearst()
	{
		int minValue = INT_MAX;
		int minNode = 0;
		for (int i = 0; i < NodeCount; i++)
		{
			if (!visited[i] && dist[i] < minValue)
			{
				minValue = dist[i];
				minNode = i;
			}
		}

		return minNode;
	}

	void display(std::vector<int>* parents)
	{
		std::cout << "Node:\t\t\tCost:\t\t\tPath:";
		std::cout << std::endl;
		for (int i = 0; i < NodeCount; i++)
		{
			std::cout << i << "\t\t\t" << dist[i] << "\t\t\t" << " ";
			std::cout << i << " ";
			int parnode = parent[i];
			
			while (parnode != src_)
			{
				if (i == destination_)
				{
					parents->push_back(parnode);
				}

				std::cout << " <- " << parnode << " ";
				parnode = parent[parnode];
			}
			std::cout << std::endl;
		}


	}

	void Find(std::vector<int>* parent)
	{
		Init();
		DijkstraAlgo();
		display(parent);
	}



};