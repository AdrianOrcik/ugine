#pragma once
#include "ugine.h"

#include "../scripts/algos/pathfinding_algo.h"
#include "../scripts/node_element.h"
#include "../scripts/algos/dijkstra.h"
#include "../scripts/algos/a_star.h"
#include "../scripts/algos/bfs.h"

#include <iostream>
#include <vector>
#include <algorithm>

class PathfindingManager : public Ugine::ScriptComponent
{
public:
	PathfindingManager()
	{}
	
	~PathfindingManager() 
	{
		delete pfAlgo;
	}

	void Sorting(std::vector<std::vector<NodeElement*>> grid, NodeElement* startNode, NodeElement* finalNode)
	{
		if (pfAlgo != nullptr) {
			delete pfAlgo;
			pfAlgo = nullptr;
		}

		pfAlgo = DBG_NEW BFS();
		pfAlgo->SetStartNode(startNode);
		pfAlgo->SetFinalNode(finalNode);
		pfAlgo->SetGrid(grid);
		pfAlgo->RunBFS();
	}

	// Inherited via ScriptComponent
	virtual void OnInit() override
	{}

	virtual void OnUpdate(float Timestep) override 
	{}

	virtual void OnActive() override 
	{}

	virtual void OnDeactive() override 
	{}

private:
	BFS* pfAlgo = nullptr;
};