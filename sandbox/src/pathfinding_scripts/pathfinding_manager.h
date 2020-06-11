#pragma once
#include "ugine.h"

#include "../pathfinding_scripts/algos/pathfinding_algo.h"
#include "../pathfinding_scripts/node_element.h"
#include "../pathfinding_scripts/algos/dijkstra_simulation.h"

#include <iostream>
#include <vector>
#include <algorithm>

class PathfindingManager : public Ugine::ScriptComponent
{
public:
	PathfindingManager()
	{}
	
	~PathfindingManager() 
	{}

	void Sorting(std::vector<std::vector<NodeElement*>> grid, NodeElement* startNode, NodeElement* finalNode)
	{
		if (pfAlgo != nullptr) {
			delete pfAlgo;
			pfAlgo = nullptr;
		}

		pfAlgo = DBG_NEW DijkstraSimulation();
		pfAlgo->SetStartNode(startNode);
		pfAlgo->SetFinalNode(finalNode);
		pfAlgo->SetGrid(grid);
		pfAlgo->RunDijkstra();
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
	DijkstraSimulation* pfAlgo = nullptr;
};