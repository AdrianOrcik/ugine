#pragma once
#include "ugine.h"

#include "../pathfinding_scripts/algos/pathfinding_algo.h"
#include "../pathfinding_scripts/node_element.h"

#include "../pathfinding_scripts/algos/dijkstra.h"

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

	void AssignNeighbourgs(int** board, NodeElement grid[35][20], int i, int j)
	{
		std::vector<std::pair<int, int>> distances;
		distances.emplace_back(std::make_pair(1, 0));
		distances.emplace_back(std::make_pair(0, 1));
		distances.emplace_back(std::make_pair(-1, 0));
		distances.emplace_back(std::make_pair(0, -1));

		for (int distIndex = 0; distIndex < 4; distIndex++)
		{
			std::pair<int, int> distance = distances[distIndex];
			bool iCorrect = i + distance.first >= 0 && i + distance.first < gridX_;
			bool jCorrect = j + distance.second >= 0 && j + distance.second < gridY_;

			if (iCorrect && jCorrect)
			{
				int yIndex = grid[i][j].Value - 1;
				int xIndex = grid[i + distance.first][j + distance.second].Value - 1;
				board[yIndex][xIndex] = 1;
			}
		}
	}

	void Find(NodeElement arr[35][20], int gridX, int gridY)
	{
		gridX_ = gridX;
		gridY_ = gridY;
		valueMatrixSize_ = gridX * gridY;
		int *board[700];
		for (int i = 0; i < valueMatrixSize_; ++i) {
			board[i] = new int[700];
		}

		// Fill valueMatrix
		for (int i = 0; i < valueMatrixSize_; i++)
		{
			for (int j = 0; j < valueMatrixSize_; j++)
			{
				board[i][j] = INT_MAX;
				if (i == j)
					board[i][j] = 0;
			}
		}

		for (int i = 0; i < gridX_; i++)
		{
			for (int j = 0; j < gridY_; j++)
			{
				if(!arr[i][j].IsWall)
					AssignNeighbourgs(board, arr, i, j);
			}
		}

		if (pfAlgo != nullptr) {
			delete pfAlgo;
			pfAlgo = nullptr;
		}

		pfAlgo = DBG_NEW Dijkstra();
		pfAlgo->SetCostMatrix(board);
		pfAlgo->SetNodeArr(arr);
		pfAlgo->DestinationNode = 24;
		pfAlgo->SourceNode = 0;
		std::vector<int>* parent = new std::vector<int>();
		pfAlgo->Find(parent);

		int nodeIndex = 0;
		for(int i = 0; i< gridX_; i++){
			for (int j = 0; j < gridY_; j++)
			{
				bool isOnPath = std::find(parent->begin(), parent->end(), nodeIndex) != parent->end();
				if (nodeIndex == pfAlgo->SourceNode ||
					nodeIndex == pfAlgo->DestinationNode)
				{
					Ugine::RendererComponent* renderer = 
						(Ugine::RendererComponent*)arr[i][j].owner->GetComponent<Ugine::RendererComponent>();
					renderer->SetColor(Ugine::Color::Yellow());
				}

				if (isOnPath)
				{
					Ugine::RendererComponent* renderer =
						(Ugine::RendererComponent*)arr[i][j].owner->GetComponent<Ugine::RendererComponent>();
					renderer->SetColor(Ugine::Color::Yellow());
				}

				nodeIndex++;
			}
		}

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
	Dijkstra* pfAlgo = nullptr;
	int gridX_;
	int gridY_;
	int valueMatrixSize_;
	NodeElement grid_[35][20];
};