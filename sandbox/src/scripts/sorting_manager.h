#pragma once

#include "ugine.h"
#include "../layers/sandbox_2d.h"
#include "../scripts/sorting_element.h"

#include "../scripts/algos/bubble_sort.h"
#include "../scripts/algos/sorting_algo.h"

#include <functional>
#include <map>

class SwapRoutine;
class SortingAlgo;
class SortingManager : public Ugine::ScriptComponent
{

public:

	SortingManager()
	{
		bubbleSort_ = DBG_NEW BubbleSort();
	}

	~SortingManager()
	{
		LOG_INFO("Delete SortingManager - ScriptComponent");
		delete bubbleSort_;
	}

	void SetElements(std::vector<SortingElement*> elements)
	{
		//elements_ = elements;
		bubbleSort_->BubbleElements.clear();
		bubbleSort_->SetElements(elements);
	}

	void SortBy()
	{
		bubbleSort_->Sort();
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
	//std::vector<SortingElement*> elements_;
	SortingAlgo* bubbleSort_ = nullptr;


};