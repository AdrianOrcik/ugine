#pragma once

class PathfindingAlgo
{
public:
	void SetStartNode(NodeElement* _node) { startNode = _node; }
	void SetFinalNode(NodeElement* _node) { finalNode = _node; }
	void SetGrid(std::vector<std::vector<NodeElement*>> _grid) 
	{ 
		grid = _grid; 
	}

	std::function<void()> OnSimulationStart;
	std::function<void()> OnSimulationDone;
	std::function<void()> OnSimulationInterrupt;

	virtual void Run() = 0;

protected:
	NodeElement* startNode = nullptr;
	NodeElement* finalNode = nullptr;
	std::vector<std::vector<NodeElement*>> grid;
};