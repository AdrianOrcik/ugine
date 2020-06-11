#include "insertion_sort.h"

InsertionSort::InsertionSort()
{
}

InsertionSort::~InsertionSort()
{
}

void InsertionSort::Sort()
{
	OnSimulationStart();

	AddStepArray(Elements);
	for (int i = 0; i < Elements.size() - 1; i++)
	{
		AddStep(StepData(i), InsertionStep::Type::SelectPivot);
		int j = i + 1;

		SortingElement* tmp = Elements[j];
		int tmp_position = j;
		
		AddStep(StepData(j), InsertionStep::Type::SelectElement);
		while (j > 0 && tmp->Value < Elements[j - 1]->Value) {
			Elements[j] = Elements[j - 1];
			AddStep(StepData(j-1), InsertionStep::Type::SelectElement);
			j--;
		}

		if (j != tmp_position) 
		{
			AddStep(StepData(j, tmp_position), InsertionStep::Type::Insert);
			Elements[j] = tmp;
			AddStepArray(Elements);
		}
		else 
		{
			Elements[j] = tmp;
		}
	}

	Run();
}

void InsertionSort::AddStep(StepData data, InsertionStep::Type stepType)
{
	simulationSteps_.push_back(InsertionStep(this, data, stepType));
}

void InsertionSort::Run()
{
	if (StepIndex >= simulationSteps_.size())
	{
		SetElementsColor(Ugine::Color::SortedElement());
		OnSimulationDone();
		return;
	}

	simulationSteps_[StepIndex].OnCompletedCallback = std::bind(&InsertionSort::Run, this);
	simulationSteps_[StepIndex].Execute();
	StepIndex++;
}
