#include "selection_sort.h"

//TODO: make simulation
SelectionSort::SelectionSort()
{
}

SelectionSort::~SelectionSort()
{
}

void SelectionSort::Sort()
{

	OnSimulationStart();

	//TODO: make as default settings
	StepIndex = 0;
	ArrayIndex = 0;

	AddStepArray(Elements);
	for (int i = 0; i < Elements.size() - 1; i++)
	{
		int minIndex = i;
		AddStep(StepData(i), SelectionStep::Type::SelectPivot);
		for (int j = i + 1; j < Elements.size(); j++)
		{
			//current + 1 < current
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
		
		//TODO: add as swap function
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
	//TODO: make check function in base class
	if (StepIndex >= simulationSteps_.size())
	{
		SetElementsColor(Ugine::Color::Yellow());
		OnSimulationDone();
		return;
	}

	simulationSteps_[StepIndex].OnCompletedCallback = std::bind(&SelectionSort::Run, this);
	simulationSteps_[StepIndex].Execute();
	StepIndex++;
}
