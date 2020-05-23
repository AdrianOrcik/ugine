#include "quick_sort.h"

Quicksort::Quicksort()
{
}

Quicksort::~Quicksort()
{
}

void Quicksort::Sort()
{
	//OnSimulationStart();
	//index_ = 0;
	//arrayIndex = 0;
	//SetElementCurrentPosition();
	//AddStepArray(Elements);

	Quick(Elements, 0, Elements.size());

	SetElementsTransform();
}

void Quicksort::Run()
{
	if (index_ >= simulationSteps_.size())
	{
		SetElementsColor(Ugine::Color::Yellow());
		OnSimulationDone();
		LOG_ERROR("Done!");
		return;
	}

	simulationSteps_[index_].OnCompletedCallback = std::bind(&Quicksort::Run, this);
	simulationSteps_[index_].Execute();
	index_++;
}

void Quicksort::Quick(std::vector<SortingElement*>  elements, int left, int right)
{
	if (left < right) {
		int boundary = left;
		for (int i = left + 1; i < right; i++) {
			if (elements[i]->Value < elements[left]->Value) 
			{
				Swap(Elements[i], Elements[++boundary],true);
		
				//swap(array, i, ++boundary);
				//SortingElement* tmp = Elements[i];
				//Elements[i] = Elements[boundary+1];
				//Elements[boundary+1] = tmp;
			}
		}
		//swap(array, left, boundary);
		Swap(Elements[left], Elements[boundary], true);

		//SortingElement* tmp = Elements[left];
		//Elements[left] = Elements[boundary];
		//Elements[boundary] = tmp;
		Quick(elements, left, boundary);
		Quick(elements, boundary + 1, right);
	}
}

void Quicksort::AddStep(StepData data, BubbleStepType stepType)
{
	simulationSteps_.push_back(BubbleStep(this, data, stepType));
}
