#include "insertion_sort.h"

#include <iostream>
#include <chrono>
#include <thread>



InsertionSort::InsertionSort()
{
}

InsertionSort::~InsertionSort()
{
}

void InsertionSort::Sort()
{
	OnSimulationStart();
	SingleIndex = 0;
	PairIndex = 0;
	SelectSingleClear();
	SetElementCurrentPosition();

	index_ = 0;
	arrayIndex = 0;

	StepArrays.push_back(Elements);
	for (int i = 0; i < Elements.size() - 1; i++)
	{
		AddStep(StepData(i), InsertionStepType::PivotSelection);

		int j = i + 1;
		SortingElement* tmp = Elements[j];
		int tmp_position = j;
		
		AddStep(StepData(j), InsertionStepType::ElementSelection);
		while (j > 0 && tmp->Value < Elements[j - 1]->Value) {
			Elements[j] = Elements[j - 1];
			AddStep(StepData(j-1), InsertionStepType::ElementSelection);
			j--;
		}

		if (j != tmp_position) 
		{
			AddStep(StepData(j, tmp_position), InsertionStepType::Insertion);
			Elements[j] = tmp;
			StepArrays.push_back(Elements);
		}
		else 
		{
			Elements[j] = tmp;
		}
	}

	//SetElementSortedPosition();
	//OnSimulationDone();
	
	//Debug
	//SetElementsTransform();
	//SwapElements();

	//simulation
	//SelectElements();
	
	Run();
}

void InsertionSort::AddStep(StepData data, InsertionStepType stepType)
{
	simulationSteps_.push_back(InsertionStep(this, data, stepType));
}

void InsertionSort::Run()
{
	if (index_ >= simulationSteps_.size())
	{
		SetElementsColor(Ugine::Color::Yellow());
		OnSimulationDone();
		LOG_ERROR("Done!");
		return;
	}

	simulationSteps_[index_].OnCompletedCallback = std::bind(&InsertionSort::Run, this);
	simulationSteps_[index_].Execute();
	index_++;
}
