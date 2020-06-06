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

	NodeElement* startNode;
	NodeElement* finalNode;
	std::vector<std::vector<NodeElement*>> grid;
	const int rowSize_ = 20;
	const int colSize_ = 35;

	void RunDijkstra()
	{
		std::vector<NodeElement*> visitedNodesInOrder = Dijkstra();
		//from visited nodes make simulation

		for (auto v : visitedNodesInOrder)
		{
			//std::cout << v->Index + 1 << std::endl;
			if(v != startNode && v != finalNode)
				AddStep(StepData(v), DijkstraStep::Type::SelectNode);
		}

		std::vector<NodeElement*> nodesInShortestPathOrder = getNodesInShortestPathOrder();

		for (auto n : nodesInShortestPathOrder)
		{
			//std::cout << v->Index + 1 << std::endl;
			AddStep(StepData(n), DijkstraStep::Type::FinalRoute);
		}

		Run();
	}

	std::vector<NodeElement*> Dijkstra()
	{
		std::vector<NodeElement*> visitedNodesInOrder;
		startNode->Distance = 0;
		std::vector<NodeElement*> unvisitedNodes = getAllNodes(grid);
		for (int i = 0; i < unvisitedNodes.size(); i++)
		//while(!unvisitedNodes.size())
		{
			sortNodesByDistance(&unvisitedNodes);
			NodeElement* closestNode = unvisitedNodes[i];

			//if its there wall we will skip
			if (closestNode->IsWall)continue;

			if (closestNode->Distance == 999)
				return visitedNodesInOrder;
			
			closestNode->IsVisited = true;
			visitedNodesInOrder.push_back(closestNode);

			if (closestNode->Index == finalNode->Index)
				return visitedNodesInOrder;

			updateUnvisitedNeighbors(closestNode, grid);
		}

		return visitedNodesInOrder;
	}

	void updateUnvisitedNeighbors(NodeElement* node, std::vector<std::vector<NodeElement*>> grid)
	{
		std::vector<NodeElement*> unvisitedNeighbors = getUnvisitedNeighbors(node, grid);
		for (auto neighbor : unvisitedNeighbors)
		{
			neighbor->Distance = node->Distance + 1;
			neighbor->PreviousNode = node;
		}
	}

	std::vector<NodeElement*> getUnvisitedNeighbors(NodeElement* node, std::vector<std::vector<NodeElement*>> grid)
	{
		std::vector<NodeElement*> neighbors;
		int col = node->Col;
		int row = node->Row;

		if (row > 0) neighbors.push_back(grid[row - 1][col]);
		if (row < grid.size() -1 )neighbors.push_back(grid[row + 1][col]);
		if (col > 0)neighbors.push_back(grid[row][col - 1]);
		if (col < grid[0].size() - 1)neighbors.push_back(grid[row][col + 1]);

		std::vector<NodeElement*> filteredNeighbors;
		for (const auto & n : neighbors) {
			if (!n->IsVisited)
			{
				filteredNeighbors.push_back(n);
			}
		}
		return filteredNeighbors;
	}

	void  sortNodesByDistance(std::vector<NodeElement*>* nodes)
	{
		//TODO: need fix to be sorting by distance!
		//std::sort(nodes->begin(), nodes->end());


		//std::sort(nodes->begin(), nodes->end(), compareByDistance);
		std::sort(nodes->begin(), nodes->end(), [](NodeElement* a, NodeElement* b) 
		{

			glm::vec2 vectorOrigin = glm::vec2(10, 15);
			glm::vec2 vectorA = glm::vec2(a->Col, a->Row);
			glm::vec2 vectorB = glm::vec2(b->Col, b->Row);

			glm::vec2 originToA = abs(vectorOrigin - vectorA);
			glm::vec2 originToB = abs(vectorOrigin - vectorB);

			float lengthA = sqrt(pow(originToA.x, 2) + pow(originToA.y, 2));
			float lengthB = sqrt(pow(originToB.x, 2) + pow(originToB.y, 2));

			return lengthA < lengthB;
		});
	}

	bool compareByDistance(const NodeElement& a, const NodeElement& b)
	{
		glm::vec2 vectorOrigin = glm::vec2(startNode->Col, startNode->Row);
		glm::vec2 vectorA = glm::vec2(a.Col, a.Row);
		glm::vec2 vectorB = glm::vec2(b.Col, b.Row);


		return a.Distance < b.Distance;
	}

	std::vector<NodeElement*> getAllNodes(std::vector<std::vector<NodeElement*>> grid)
	{
		std::vector<NodeElement*> nodes;
		/*for (int i = 0; i < rowSize_; i++)
		{
			for (int j = 0; j < colSize_; j++)
			{
				nodes.push_back(grid[j][i]);
			}
		}*/

		for (auto r : grid)
		{
			for (auto n : r)
			{
				nodes.push_back(n);
			}
		}
		return nodes;
	}

	std::vector<NodeElement*> getNodesInShortestPathOrder()
	{
		std::vector<NodeElement*> nodesInShortestPathOrder;
		NodeElement* currentNode = finalNode;
		while (currentNode != nullptr) {
			nodesInShortestPathOrder.push_back(currentNode);
			currentNode = currentNode->PreviousNode;
		}

		return nodesInShortestPathOrder;
	}

	void Run()
	{
		if (StepIndex >= simulationSteps_.size())
		{
			LOG_INFO("Done");
			//SetElementsColor(Ugine::Color::SortedElement());
			//OnSimulationDone();

			auto renderer = (Ugine::RendererComponent*)startNode->owner->GetComponent<Ugine::RendererComponent>();
			renderer->SetColor(Ugine::Color::Yellow());

			auto renderer2 = (Ugine::RendererComponent*)finalNode->owner->GetComponent<Ugine::RendererComponent>();
			renderer2->SetColor(Ugine::Color::Yellow());

			return;
		}

		simulationSteps_[StepIndex].OnCompletedCallback = std::bind(&DijkstraSimulation::Run, this);
		simulationSteps_[StepIndex].Execute();
		StepIndex++;
	}

	void AddStep(StepData data, DijkstraStep::Type stepType)
	{
		simulationSteps_.push_back(DijkstraStep(data, stepType));
	}

	int StepIndex = 0;
	std::vector<DijkstraStep> simulationSteps_;
};