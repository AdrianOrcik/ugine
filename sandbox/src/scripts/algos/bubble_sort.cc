#include "bubble_sort.h"

BubbleSort::BubbleSort()
{}

BubbleSort::~BubbleSort()
{}

void BubbleSort::Sort()
{
	OnSimulationStart();

	index_ = 0;
	arrayIndex = 0;

	SetElementCurrentPosition();
	AddStepArray(Elements);
	for (int i = 0; i < Elements.size() - 1; i++)
	{
		for (int j = 0; j < Elements.size() - i - 1; j++)
		{
			if (Elements[j]->Value > Elements[j + 1]->Value)
			{
				AddStep(StepData(j, j + 1), BubbleStepType::S_BeforeSwap);
				AddStep(StepData(j, j + 1), BubbleStepType::S_Swap);
				AddStep(StepData(), BubbleStepType::S_AfterSwap);

				SortingElement* tmp = Elements[j];
				Elements[j] = Elements[j + 1];
				Elements[j + 1] = tmp;				
				AddStepArray(Elements);
			}
			else 
			{
				AddStep(StepData(j, j + 1), BubbleStepType::S_Select);
			}
		}
	}

	Run();
}

void BubbleSort::Run()
{
	if (index_ >= simulationSteps_.size())
	{
		SetElementsColor(Ugine::Color::Yellow());
		OnSimulationDone();
		LOG_ERROR("Done!");
		return;
	}

	simulationSteps_[index_].OnCompletedCallback = std::bind(&BubbleSort::Run, this);
	simulationSteps_[index_].Execute();
	index_++;
}

void BubbleSort::AddStep(StepData data, BubbleStepType stepType)
{
	simulationSteps_.push_back(BubbleStep(this, data, stepType));
}
