#include "selection_sort.h"

SelectionSort::SelectionSort()
{
}

SelectionSort::~SelectionSort()
{
}

void SelectionSort::Sort()
{

	OnSimulationStart();

	AddStepArray(Elements);
	for (int i = 0; i < Elements.size() - 1; i++)
	{
		int minIndex = i;
		AddStep(StepData(i), SelectionStep::Type::SelectPivot);
		for (int j = i + 1; j < Elements.size(); j++)
		{
			//Note: current + 1 < current
			if (Elements[j]->Value < Elements[minIndex]->Value) 
			{
				minIndex = j;
				AddStep(StepData(minIndex), SelectionStep::Type::SelectPivot);
			}
			else
			{
				//Note: minIndex on positionA as pivot
				AddStep(StepData(minIndex, j), SelectionStep::Type::Select);
			}
		}
		AddStep(StepData(i, minIndex), SelectionStep::Type::BeforeSwap);
		AddStep(StepData(i, minIndex), SelectionStep::Type::Swap);
		
		SortingElement* tmp = Elements[i];
		Elements[i] = Elements[minIndex];
		Elements[minIndex] = tmp;

		AddStep(StepData(i, minIndex), SelectionStep::Type::AfterSwap);
		AddStepArray(Elements);
	}

	Run();
}

void SelectionSort::AddStep(StepData data, SelectionStep::Type stepType)
{
	simulationSteps_.push_back(SelectionStep(this, data, stepType));
}

void SelectionSort::Run()
{

	if (StepIndex >= simulationSteps_.size())
	{
		SetElementsColor(Ugine::Color::SortedElement());
		OnSimulationDone();
		return;
	}

	simulationSteps_[StepIndex].OnCompletedCallback = std::bind(&SelectionSort::Run, this);
	simulationSteps_[StepIndex].Execute();
	StepIndex++;
}
