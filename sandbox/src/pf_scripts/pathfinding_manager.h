#pragma once
#include "ugine.h"

#include "../pf_scripts/algos/pathfinding_algo.h"
#include "../pf_scripts/node_element.h"

#include "../pf_scripts/algos/dijkstra.h"

class PathfindingManager : public Ugine::ScriptComponent
{
public:
	PathfindingManager()
	{}
	
	~PathfindingManager() 
	{}

	void Find(NodeElement arr[35][20])
	{
		if (pfAlgo != nullptr) {
			delete pfAlgo;
			pfAlgo = nullptr;
		}

		pfAlgo = DBG_NEW Dijkstra();
		pfAlgo->Find();
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
	PathfindingAlgo* pfAlgo = nullptr;
	NodeElement grid_[35][20];
};