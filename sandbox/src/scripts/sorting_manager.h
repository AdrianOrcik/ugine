#pragma once

#include "ugine.h"
#include "../layers/sandbox_2d.h"
#include "../scripts/sorting_element.h"

#include "../scripts/algos/bubble_sort.h"
#include "../scripts/algos/selection_sort.h"
#include "../scripts/algos/insertion_sort.h"
#include "../scripts/algos/quick_sort.h"
#include "../scripts/algos/heap_sort.h"
#include "../scripts/algos/merge_sort.h"
#include "../scripts/algos/sorting_algo.h"

#include <functional>
#include <map>

class SwapRoutine;
class SortingAlgo;
class SortingManager : public Ugine::ScriptComponent
{

public:
	enum SortingType {Unset, Bubble, Selection, Insertion, Quick, Heap, Merge };

	SortingManager()
		:isRunning(false)
	{
	}

	~SortingManager()
	{
		StopSimulation();
	}

	bool IsRunning() { return isRunning; }

	void SetElements(std::vector<SortingElement*> elements)
	{
		Elements = elements;
	}

	void StopSimulation()
	{
		isRunning = false;
		if (sortAlgorhitm_ != nullptr) {
			delete sortAlgorhitm_;
			sortAlgorhitm_ = nullptr;
		}
	}

	void SortBy(SortingType type)
	{
		switch (type)
		{
		case SortingType::Bubble:
			sortAlgorhitm_ = DBG_NEW BubbleSort();
			break;
		case SortingType::Selection:
			sortAlgorhitm_ = DBG_NEW SelectionSort();
			break;
		case SortingType::Insertion:
			sortAlgorhitm_ = DBG_NEW InsertionSort();
			break;
		case SortingType::Quick:
			sortAlgorhitm_ = DBG_NEW Quicksort();
			break;
		case SortingType::Heap:
			sortAlgorhitm_ = DBG_NEW HeapSort();
			break;
		case SortingType::Merge:
			sortAlgorhitm_ = DBG_NEW MergeSort();
			break;
		}

		sortAlgorhitmType_ = type;
		sortAlgorhitm_->SetElements(Elements);
		sortAlgorhitm_->OnSimulationStart = std::bind(&SortingManager::SetStartRunning, this);
		sortAlgorhitm_->OnSimulationDone = std::bind(&SortingManager::SetStopRunning, this);
		sortAlgorhitm_->Sort();
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
	void SetStartRunning() {isRunning = true;}
	void SetStopRunning() { StopSimulation(); }

private:
	SortingAlgo* sortAlgorhitm_ = nullptr;
	SortingType sortAlgorhitmType_ = SortingType::Unset;

	std::vector<SortingElement*> Elements;
	bool isRunning = false;
};