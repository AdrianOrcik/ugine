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
	index_ = 0;
	arrayIndex = 0;
	//SetElementCurrentPosition();
	//AddStepArray(Elements);

	AddStepArray(Elements);
	Quick(0, Elements.size());

	//SetElementsTransform();
	Run();
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
		for (int i = left + 1; i < right; i++) {
			//AddStep(StepData(boundary), QuickStep::Type::SelectPivot);
			AddStep(StepData(i, left), QuickStep::Type::SelectElement);
			if (Elements[i]->Value > Elements[left]->Value) 
			{
				if(i != boundary){
					AddStep(StepData(i, ++boundary), QuickStep::Type::BeforeSwap);
					AddStep(StepData(i, boundary), QuickStep::Type::Swap);
					AddStep(StepData(i, boundary), QuickStep::Type::AfterSwap);

					//Swap(Elements[i], Elements[boundary], true);
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
		
			//Swap(Elements[left], Elements[boundary], true);

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
