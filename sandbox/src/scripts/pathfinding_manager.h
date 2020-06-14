#pragma once
#include "ugine.h"

#include "../scripts/algos/pathfinding_algo.h"
#include "../scripts/node_element.h"
#include "../scripts/algos/dijkstra.h"
#include "../scripts/algos/a_star.h"
#include "../scripts/algos/bfs.h"
#include "../scripts/algos/dfs.h"

#include <iostream>
#include <vector>
#include <algorithm>

class PathfindingManager : public Ugine::ScriptComponent
{
public:
	enum Type { DijkstraType, AStarType, BFSType, DFSType };
	PathfindingManager()
	{}
	
	~PathfindingManager() 
	{
		StopSimulation();
	}

	bool IsRunning() { return isRunning; }

	void StopSimulation()
	{
		isRunning = false;
		if (pfAlgo != nullptr) {
			delete pfAlgo;
			pfAlgo = nullptr;
		}
	}

	void Simulate(std::vector<std::vector<NodeElement*>> grid, NodeElement* startNode, NodeElement* finalNode, Type type)
	{
		switch (type)
		{
		case Type::DijkstraType:
			pfAlgo = DBG_NEW Dijkstra();
			break;
		case Type::AStarType:
			pfAlgo = DBG_NEW AStar();
			break;
		case Type::BFSType:
			pfAlgo = DBG_NEW BFS();
			break;
		case Type::DFSType:
			pfAlgo = DBG_NEW DFS();
			break;
		}

		pfAlgo->SetStartNode(startNode);
		pfAlgo->SetFinalNode(finalNode);
		pfAlgo->OnSimulationStart = std::bind(&PathfindingManager::SetStartRunning, this);
		pfAlgo->OnSimulationDone = std::bind(&PathfindingManager::SetStopRunning, this);
		pfAlgo->SetGrid(grid);
		pfAlgo->Run();
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
	void SetStartRunning() { isRunning = true; }
	void SetStopRunning() { StopSimulation(); }

private:
	PathfindingAlgo* pfAlgo = nullptr;
	bool isRunning = false;
};