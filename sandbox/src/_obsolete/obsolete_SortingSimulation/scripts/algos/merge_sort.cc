#include "merge_sort.h"

MergeSort::MergeSort()
{
}

MergeSort::~MergeSort()
{
}

void MergeSort::Sort()
{
	OnSimulationStart();

	AddStepArray(Elements);
	Merge(0, Elements.size() - 1);

	Run();
}

void MergeSort::Run()
{
	if (StepIndex >= simulationSteps_.size())
	{
		SetElementsColor(Ugine::Color::SortedElement());
		OnSimulationDone();
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
		int mid = (low + high) / 2;
		Merge(low, mid);
		Merge(mid + 1, high);
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

	while (i <= mid && j <= high)
	{
		if (Elements[i]->Value < Elements[j]->Value)
		{
			c[k] = Elements[i];
			i++;
		}
		else
		{
			c[k] = Elements[j];
			j++;
		}
		k++;
	}

	while (i <= mid)
	{
		c[k] = Elements[i];
		k++;
		i++;
	}

	while (j <= high)
	{
		c[k] = Elements[j];
		k++;
		j++;
	}

	for (i = low; i < k; i++)
	{
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
