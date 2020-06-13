#pragma once
#include "../algos/pathfinding_algo.h"
#include "../node_element.h"
#include "../simulation/dijkstra_step.h"

#include <iostream>

class AStar : public PathfindingAlgo
{
public:
	AStar()
	{
	}

	~AStar()
	{
	}


	void SetStartNode(NodeElement* node) { startNode_ = node; }
	void SetFinalNode(NodeElement* node) { finalNode_ = node; }
	void SetGrid(std::vector<std::vector<NodeElement*>> grid) { grid_ = grid; }

	void InitData()
	{
		int rowSize = grid_.size();
		int colSize = grid_[0].size();

		for (int x = 0; x < colSize; x++)
		{
			for (int y = 0; y < rowSize; y++)
			{
				//down
				if (y > 0)
					grid_[y][x]->Neighbours.push_back(grid_[y - 1][x + 0]);

				//up
				if (y < rowSize - 1)
					grid_[y][x]->Neighbours.push_back(grid_[y + 1][x + 0]);

				//left
				if (x > 0)
					grid_[y][x]->Neighbours.push_back(grid_[y + 0][x - 1]);

				//right
				if (x < colSize - 1)
					grid_[y][x]->Neighbours.push_back(grid_[y + 0][x + 1]);
			}
		}
	}


	void SolveAStar()
	{
		//TODO: check calculation
		auto distance = [](NodeElement* a, NodeElement* b) // For convenience
		{
			return sqrtf((a->Row - b->Row)*(a->Row - b->Row) + (a->Col - b->Col)*(a->Col - b->Col));
		};

		auto heuristic = [distance](NodeElement* a, NodeElement* b) // So we can experiment with heuristic
		{
			return distance(a, b);
		};

		//setup starting condition
		NodeElement* currentNode = startNode_;
		startNode_->LocalDistance = 0;
		startNode_->GlobalDistance = heuristic(startNode_, finalNode_);

		AddStep(StepData(startNode_), DijkstraStep::Type::SelectNode);

		//add start node to not tested list yet
		std::vector<NodeElement*>* listNotTestedNodes = new std::vector<NodeElement*>();
		listNotTestedNodes->push_back(startNode_);

		//pokial mam nejake objavene a netestovane nody v liste, je sanca ze existuje este kratsia cesta
		while (!listNotTestedNodes->empty() && currentNode != finalNode_) // Find absolutely shortest path // && currentNode != finalNode_
		{
			//sort untested notes by global distance
			std::sort(listNotTestedNodes->begin(), listNotTestedNodes->end(), [](NodeElement* a, NodeElement*b)
			{
				return a->GlobalDistance < b->GlobalDistance;
			});

			//na zaciatku listu je potencionalne s najkratsou vzdialenostou 
			while (!listNotTestedNodes->empty() && listNotTestedNodes->front()->IsVisited)
			{
				//ak uz som navstivil node tak ho vyhodim z listu
				listNotTestedNodes->front() = std::move(listNotTestedNodes->back());
				listNotTestedNodes->pop_back();
			}

			//ak neostal v liste ziaden node tak vyskocime z loopu
			if (listNotTestedNodes->empty())
				break;

			//ak nieco ostalo tak zoberem zo zaciatku a oznacim node ako navstiveny
			currentNode = listNotTestedNodes->front();
			currentNode->IsVisited = true;

			//pozrem kazdy susedny node
			for (auto neighbour : currentNode->Neighbours)
			{
				//ak sused este neni navstiveny a neni ani obstacle 
				if (!neighbour->IsWall() && !neighbour->IsVisited)
				{
					AddStep(StepData(neighbour), DijkstraStep::Type::SelectNode);
					listNotTestedNodes->push_back(neighbour);
				}

				// kalkulacia susedov aby som nasiel potencionalne najkratsiu cestu
				float possiblyLowerDistance = currentNode->LocalDistance + distance(currentNode, neighbour);

				//ak sme vybrali cestu s najkratsou vzdialenostou, suset nastavi hodnoty prepoctu 
				//ako je localdistance a globalDistance
				if (possiblyLowerDistance < neighbour->LocalDistance)
				{
					neighbour->parent = currentNode;
					neighbour->LocalDistance = possiblyLowerDistance;

					//prepocita sa najkratsia cesta k cielu
					neighbour->GlobalDistance = neighbour->LocalDistance + heuristic(neighbour, finalNode_);
				}
			}
		}
	}

	void RunAstar()
	{
		InitData();
		SolveAStar();

		NodeElement* currNode = finalNode_;
		while(currNode != startNode_)
		{
			AddStep(StepData(currNode), DijkstraStep::Type::FinalRoute);
			currNode = currNode->parent;
		}

		RunSimulation();
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

		simulationSteps_[stepIndex_].OnCompletedCallback = std::bind(&AStar::RunSimulation, this);
		simulationSteps_[stepIndex_].Execute();
		stepIndex_++;
	}

	void AddStep(StepData data, DijkstraStep::Type stepType)
	{
		simulationSteps_.push_back(DijkstraStep(data, stepType));
	}


private:
	int stepIndex_ = 0;

	NodeElement* startNode_ = nullptr;
	NodeElement* finalNode_ = nullptr;
	std::vector<std::vector<NodeElement*>> grid_;


	std::vector<DijkstraStep> simulationSteps_;
};