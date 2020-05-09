#pragma once

#include "ugine.h"
#include "../layers/sandbox_2d.h"
#include "../scripts/sorting_element.h"

#include "../scripts/algos/bubble_sort.h"
#include "../scripts/algos/sorting_algo.h"

#include <functional>
#include <map>

class SwapRoutine;
class SortingManager : public Ugine::ScriptComponent
{

public:
	SortingManager()
	{}

	~SortingManager()
	{
		LOG_INFO("Delete SortingManager - ScriptComponent");
	}

	SortingAlgo* sort;
	void SetElements(std::vector<SortingElement*> elements)
	{
		elements_ = elements;
	}

	void SortBy()
	{
		sort = new BubbleSort(elements_);
		sort->Sort();
	}

	// Inherited via ScriptComponent
	virtual void OnInit() override
	{}

	virtual void OnUpdate(float Timestep) override
	{}

private:
	std::vector<SortingElement*> elements_;

};