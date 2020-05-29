#pragma once
#include "../algos/pathfinding_algo.h"

class Dijkstra: public PathfindingAlgo
{
public:
	Dijkstra()
	{}

	~Dijkstra()
	{}

	// Inherited via PathfindingAlgo
	virtual void Find() override
	{
		LOG_INFO("finding ...");
	}

};