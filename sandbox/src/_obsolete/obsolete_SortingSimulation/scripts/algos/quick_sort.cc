#include "quick_sort.h"

Quicksort::Quicksort()
{
}

Quicksort::~Quicksort()
{
}

void Quicksort::Sort()
{
	OnSimulationStart();

	AddStepArray(Elements);
	Quick(0, Elements.size());

	Run();
}

void Quicksort::Run()
{
	if (StepIndex >= simulationSteps_.size())
	{
		SetElementsColor(Ugine::Color::SortedElement());
		OnSimulationDone();
		return;
	}

	simulationSteps_[StepIndex].OnCompletedCallback = std::bind(&Quicksort::Run, this);
	simulationSteps_[StepIndex].Execute();
	StepIndex++;
}

void Quicksort::Quick( int left, int right)
{
	if (left < right) {
		if(left != right -1){
			AddStep(StepData(left,right-1), QuickStep::Type::SelectRange);
		}
		else
		{
			AddStep(StepData(left), QuickStep::Type::SelectRange);
		}

		int boundary = left;
		for (int i = left + 1; i < right; i++) 
		{
			AddStep(StepData(i, left), QuickStep::Type::SelectElement);
			if (Elements[i]->Value < Elements[left]->Value) 
			{
				if(i != boundary){
					AddStep(StepData(i, ++boundary), QuickStep::Type::BeforeSwap);
					AddStep(StepData(i, boundary), QuickStep::Type::Swap);
					AddStep(StepData(i, boundary), QuickStep::Type::AfterSwap);

					SortingElement* tmp = Elements[i];
					Elements[i] = Elements[boundary];
					Elements[boundary] = tmp;

					AddStepArray(Elements);
				}
			}
		}

		if(left != boundary) {
			AddStep(StepData(left, boundary), QuickStep::Type::BeforeSwap);
			AddStep(StepData(left, boundary), QuickStep::Type::Swap);
			AddStep(StepData(left, boundary), QuickStep::Type::AfterSwap);

			SortingElement* tmp = Elements[left];
			Elements[left] = Elements[boundary];
			Elements[boundary] = tmp;
			AddStepArray(Elements);
		}

		Quick(left, boundary);
		Quick(boundary + 1, right);
	}
}

void Quicksort::AddStep(StepData data, QuickStep::Type stepType)
{
	simulationSteps_.push_back(QuickStep(this, data, stepType));
}
