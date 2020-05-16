#pragma once

#include "ugine.h"
#include "../layers/sandbox_2d.h"
#include "../scripts/sorting_element.h"

#include "../scripts/algos/bubble_sort.h"
#include "../scripts/algos/selection_sort.h"
#include "../scripts/algos/sorting_algo.h"

#include <functional>
#include <map>

class SwapRoutine;
class SortingAlgo;
class SortingManager : public Ugine::ScriptComponent
{

public:
	enum SortingType{Bubble, Selection};

	SortingManager()
	{
		bubbleSort_ = DBG_NEW BubbleSort();
		selectionSort_ = DBG_NEW Selectionsort();
	}

	~SortingManager()
	{
		LOG_INFO("Delete SortingManager - ScriptComponent");
		delete bubbleSort_;
		delete selectionSort_;
	}

	void SetElements(std::vector<SortingElement*> elements)
	{
		bubbleSort_->SetElements(elements);
		selectionSort_->SetElements(elements);
	}

	void SortBy(SortingType type)
	{
		switch (type)
		{
			case SortingType::Bubble:
				bubbleSort_->Sort();
				break;
			case SortingType::Selection:
				selectionSort_->Sort();
				break;
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
	SortingAlgo* bubbleSort_ = nullptr;
	SortingAlgo* selectionSort_ = nullptr;


};