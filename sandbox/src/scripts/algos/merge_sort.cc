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
	index_ = 0;
	arrayIndex = 0;

	AddStepArray(Elements);
	Merge(0, Elements.size() - 1);
	//SetElementsTransform();

	Run();
}

void MergeSort::Run()
{
	if (index_ >= simulationSteps_.size())
	{
		SetElementsColor(Ugine::Color::Yellow());
		OnSimulationDone();
		LOG_ERROR("Done!");
		return;
	}

	simulationSteps_[index_].OnCompletedCallback = std::bind(&MergeSort::Run, this);
	simulationSteps_[index_].Execute();
	index_++;
}

void MergeSort::Merge(int low, int high)
{
	int mid = 0;
	if (low < high)
	{
		// find middle of the array
		int mid = (low + high) / 2;

		AddStep(StepData(low, mid), MergeStep::Type::SelectRange);

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
		AddStep(StepData(i, c[i]->Value), MergeStep::Type::OverrideValue);
		Elements[i] = c[i];
		//AddStepArray(Elements);

		//std::vector<SortingElement*>::iterator it = std::find(Elements.begin(), Elements.end(), c[i]);
		//int index = std::distance(Elements.begin(), it);
		//if(index != i){
		//	AddStep(StepData(i, index), MergeStep::Type::Move);
		//	Elements[i] = c[i];
		//	AddStepArray(Elements);
		//}
	}
}

void MergeSort::AddStep(StepData data, MergeStep::Type stepType)
{
	simulationSteps_.push_back(MergeStep(this, data, stepType));
}
