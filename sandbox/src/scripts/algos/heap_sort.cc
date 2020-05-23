#include "heap_sort.h"

HeapSort::HeapSort()
{
}

HeapSort::~HeapSort()
{
}

void HeapSort::Sort()
{
	//SetElementCurrentPosition();
	Heap(Elements.size());
	//SetElementSortedPosition();
	//SetElementsTransform();

	Run();
}

void HeapSort::Heap(int size)
{

	for (int i = size / 2 - 1; i >= 0; i--)
		Heapify(size, i);

	for (int i = size - 1; i >= 0; i--)
	{
		//Swap(Elements[0], Elements[i], true);

		AddStep(StepData(0, i), HeapStep::Type::BeforeSwap);
		AddStep(StepData(0, i), HeapStep::Type::Swap);
		AddStep(StepData(0, i), HeapStep::Type::AfterSwap);

		SortingElement* tmp = Elements[0];
		Elements[0] = Elements[i];
		Elements[i] = tmp;

		AddStepArray(Elements);
		Heapify(i, 0);
	}
}

void HeapSort::Heapify(int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && Elements[l]->Value > Elements[largest]->Value)
		largest = l;

	if (r < n && Elements[r]->Value > Elements[largest]->Value)
		largest = r;

	if (largest != i)
	{
		//Swap(Elements[0], Elements[i], true);

		AddStep(StepData(i, largest), HeapStep::Type::BeforeSwap);
		AddStep(StepData(i, largest), HeapStep::Type::Swap);
		AddStep(StepData(i, largest), HeapStep::Type::AfterSwap);

		SortingElement* tmp = Elements[i];
		Elements[i] = Elements[largest];
		Elements[largest] = tmp;
		AddStepArray(Elements);

		Heapify(n, largest);
	}
}

void HeapSort::Run()
{
	if (index_ >= simulationSteps_.size())
	{
		SetElementsColor(Ugine::Color::Yellow());
		OnSimulationDone();
		LOG_ERROR("Done!");
		return;
	}

	simulationSteps_[index_].OnCompletedCallback = std::bind(&HeapSort::Run, this);
	simulationSteps_[index_].Execute();
	index_++;
}

void HeapSort::AddStep(StepData data, HeapStep::Type stepType)
{
	simulationSteps_.push_back(HeapStep(this, data, stepType));
}
