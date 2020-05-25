#include "merge_sort.h"
//
//#include <algorithm>

MergeSort::MergeSort()
{
}

MergeSort::~MergeSort()
{
}

void MergeSort::Sort()
{
	StepIndex = 0;
	ArrayIndex = 0;
	OnSimulationStart();

	AddStepArray(Elements);
	Merge(0, Elements.size() - 1);
	//SetElementsTransform();

	Run();
}

void MergeSort::Run()
{
	if (StepIndex >= simulationSteps_.size())
	{
		SetElementsColor(Ugine::Color::Yellow());
		OnSimulationDone();
		LOG_ERROR("Done!");
		return;
	}

	simulationSteps_[StepIndex].OnCompletedCallback = std::bind(&MergeSort::Run, this);
	simulationSteps_[StepIndex].Execute();
	StepIndex++;
}

void MergeSort::Merge(int low, int high)
{
	int mid = 0;
	if (low < high)
	{
		// find middle of the array
		int mid = (low + high) / 2;

		// sort first half
		Merge(low, mid);
		// sort second half
		Merge(mid + 1, high);

		// merge together 
		MergeHelper(low, high, mid);
	}
}

void MergeSort::MergeHelper(int low, int high, int mid)
{
	int i, j, k;
	SortingElement* c[50];
	i = low;
	k = low;
	j = mid + 1;

	// merge array back into arr[low..high]
	while (i <= mid && j <= high)
	{
		if (Elements[i]->Value < Elements[j]->Value)
		{
			// creating array
			c[k] = Elements[i];
			//AddStepArray(Elements);
			i++;
		}
		else
		{
			// creating array
			c[k] = Elements[j];
			//AddStepArray(Elements);
			j++;
		}
		k++;
	}

	while (i <= mid)
	{
		// creating arrays
		c[k] = Elements[i];
		k++;
		i++;
	}

	while (j <= high)
	{
		// creating arrays
		c[k] = Elements[j];
		k++;
		j++;
	}

	for (i = low; i < k; i++)
	{
		// final array movement
		AddStep(StepData(low, k-1), MergeStep::Type::SelectRange);

		AddStep(StepData(i), MergeStep::Type::BeforeOverride);
		AddStep(StepData(i, c[i]->Value), MergeStep::Type::OverrideValue);
		AddStep(StepData(i), MergeStep::Type::AfterOverride);
		
		Elements[i] = c[i];
	}
}

void MergeSort::AddStep(StepData data, MergeStep::Type stepType)
{
	simulationSteps_.push_back(MergeStep(this, data, stepType));
}
