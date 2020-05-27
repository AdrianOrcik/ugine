#include "bubble_sort.h"

BubbleSort::BubbleSort()
{}

BubbleSort::~BubbleSort()
{}

void BubbleSort::Sort()
{
	OnSimulationStart();

	AddStepArray(Elements);
	for (int i = 0; i < Elements.size() - 1; i++)
	{
		for (int j = 0; j < Elements.size() - i - 1; j++)
		{
			if (Elements[j]->Value > Elements[j + 1]->Value)
			{
				AddStep(StepData(j, j + 1), BubbleStep::Type::BeforeSwap);
				AddStep(StepData(j, j + 1), BubbleStep::Type::Swap);
				AddStep(StepData(), BubbleStep::Type::AfterSwap);

				SortingElement* tmp = Elements[j];
				Elements[j] = Elements[j + 1];
				Elements[j + 1] = tmp;

				AddStepArray(Elements);
			}
			else 
			{
				AddStep(StepData(j, j + 1), BubbleStep::Type::Select);
			}
		}
	}

	Run();
}

void BubbleSort::Run()
{
	if (StepIndex >= simulationSteps_.size())
	{
		SetElementsColor(Ugine::Color::SortedElement());
		OnSimulationDone();
		return;
	}

	simulationSteps_[StepIndex].OnCompletedCallback = std::bind(&BubbleSort::Run, this);
	simulationSteps_[StepIndex].Execute();
	StepIndex++;
}

void BubbleSort::AddStep(StepData data, BubbleStep::Type stepType)
{
	simulationSteps_.push_back(BubbleStep(this, data, stepType));
}
