#include "insertion_sort.h"

#include <iostream>
#include <chrono>
#include <thread>



InsertionSort::InsertionSort()
{
}

InsertionSort::~InsertionSort()
{
}

void InsertionSort::Sort()
{
	//OnSimulationStart();
	SingleIndex = 0;
	PairIndex = 0;
	SelectSingleClear();
	SetElementCurrentPosition();

	index_ = 0;
	arrayIndex = 0;

	BaseElements = Elements;
	StepArrays.push_back(Elements);
	for (int i = 0; i < Elements.size() - 1; i++)
	{
		steps.push_back(SimulationStep(this, StepData(i), SimulationStepType::Pivot));
		int j = i + 1;
		SortingElement* tmp = Elements[j];
		int tmp_int = j;
		steps.push_back(SimulationStep(this, StepData(j), SimulationStepType::Select));
		while (j > 0 && tmp->Value < Elements[j - 1]->Value) {
			Elements[j] = Elements[j - 1];
			steps.push_back(SimulationStep(this, StepData(j - 1), SimulationStepType::Select));
			j--;
		}

		if (j != tmp_int) {
			steps.push_back(SimulationStep(this, StepData(j, tmp_int), SimulationStepType::Insert));
			Elements[j] = tmp;
			StepArrays.push_back(Elements);
		}
		else {
			Elements[j] = tmp;
		}

		
		
	}

	//SetElementSortedPosition();
	//OnSimulationDone();
	
	//Debug
	//SetElementsTransform();
	//SwapElements();

	//simulation
	//SelectElements();
	
	Run();
}


void InsertionSort::Run()
{
	if (index_ >= steps.size())
	{
		SetElementsColor(Ugine::Color::Yellow());
		LOG_ERROR("Done!");
		return;
	}

	steps[index_].OnCompleted = std::bind(&InsertionSort::Run, this);
	steps[index_].Execute();
	index_++;
}


void InsertionSort::SelectElements()
{
	if (!(SingleIndex < SelectSingle.size()))
	{
		LOG_ERROR("Single Done");
		SetElementsColor(Ugine::Color::Yellow());
		SingleIndex = 0;
		PairIndex = 0;
		OnSimulationDone();
		return;
	}

	SortingSingleElement* data = SelectSingle[SingleIndex];
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.5f);
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
	SingleIndex++;
	if (data->IsSelected) {
		data->GetRender()->SetColor(Ugine::Color::Blue());
	}
	else {
		data->GetRender()->SetColor(Ugine::Color::Red());
	}
	waitfor->SetOnCompleted(std::bind(&InsertionSort::SelectElements, this));
}

void InsertionSort::SwapElements()
{
	if (!HasMorePair())
	{
		LOG_ERROR("Pair Done");
		return;
	}

	SortingPairElement* data = SwapPair[PairIndex];

	data->GetRenderA()->SetColor(Ugine::Color::Purple());
	data->GetRenderB()->SetColor(Ugine::Color::Purple());

	//todo: implement some logic operation into sorting elements data
	int currentA = data->GetSortingElementA()->CurrentPosition;
	int currentB = data->GetSortingElementB()->CurrentPosition;

	data->GetSortingElementA()->CurrentPosition = currentB;
	data->GetSortingElementB()->CurrentPosition = currentA;

	Ugine::SwapRoutine* swapRoutine = DBG_NEW Ugine::SwapRoutine(data->GetTransformA(), data->GetTransformB(), 5.0f);
	std::function<void(void)> function = std::bind(&InsertionSort::SwapElements, this);
	swapRoutine->SetOnCompleted(function);
	PairIndex++;
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)swapRoutine);
}

