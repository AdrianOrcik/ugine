#include "selection_sort.h"
#pragma once

//TODO: make simulation
Selectionsort::Selectionsort()
{
}

Selectionsort::~Selectionsort()
{
}

void Selectionsort::Sort()
{
	OnSimulationStart();
	//TODO: automatic function add into base.sort()
	SingleIndex = 0;
	PairIndex = 0;
	SwapPairClear();
	SelectSingleClear();

	SetElementCurrentPosition();
	for (int i = 0; i < Elements.size() - 1; i++)
	{
		int minIndex = i;
		Select(Elements[i], true, false); //always false
		for (int j = i + 1; j < Elements.size(); j++)
		{
			//current + 1 < current
			if (Elements[j]->Value < Elements[minIndex]->Value) 
			{
				minIndex = j;
				Select(Elements[minIndex], true, j == Elements.size() -1);
			}
			else
			{
				Select(Elements[j], false, j == Elements.size() -1);
			}
		}
		Swap(Elements[i], Elements[minIndex], true);
	}
	SetElementSortedPosition();
	
	//Debug
	//SetElementsTransform();

	SelectElements();
}

void Selectionsort::SelectElements()
{
	if (!HasMoreSingle())
	{
		LOG_ERROR("Single Done");
		SetElementsColor(Ugine::Color::Yellow());
		//todo: reset values on beginning
		SingleIndex = 0;
		PairIndex = 0;
		OnSimulationDone();
		return;
	}

	SortingSingleElement* data = SelectSingle[SingleIndex];
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);

	if (data->IsLast)
	{
		//TODO: ked mam oznacit poslednu tak to nejde modra -> cervena ale rovno skoci na cervenu
		if (!data->IsSelected) 
		{
			data->GetRender()->SetColor(Ugine::Color::Blue());
		}
		else 
		{
			data->GetRender()->SetColor(Ugine::Color::Blue());
		}
		waitfor->SetOnCompleted(std::bind(&Selectionsort::BeforeFindNewSelection, this));
	}
	else if(data->IsSelected)
	{
		if(SingleIndex == 0 || newIteration){
			newIteration = false;
			SingleIndex++;
			SetElementsColor(Ugine::Color::White());
			data->GetRender()->SetColor(Ugine::Color::Red());
			waitfor->SetOnCompleted(std::bind(&Selectionsort::SelectElements, this));
		}
		else
		{
			data->GetRender()->SetColor(Ugine::Color::Blue());
			waitfor->SetOnCompleted(std::bind(&Selectionsort::DelaySelection, this));
		}
	}
	else
	{
		SingleIndex++;
		data->GetRender()->SetColor(Ugine::Color::Blue());
		waitfor->SetOnCompleted(std::bind(&Selectionsort::SelectElements, this));
	}
}

void Selectionsort::DelaySelection()
{
	SortingSingleElement* data = SelectSingle[SingleIndex];
	SingleIndex++;
	SetElementsColor(Ugine::Color::White());
	data->GetRender()->SetColor(Ugine::Color::Red());
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
	waitfor->SetOnCompleted(std::bind(&Selectionsort::SelectElements, this));
}

void Selectionsort::BeforeFindNewSelection()
{
	SortingSingleElement* data = SelectSingle[SingleIndex];
	SingleIndex++;
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
	waitfor->SetOnCompleted(std::bind(&Selectionsort::SwapElements, this));
}

void Selectionsort::SwapElements()
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

	Ugine::SwapRoutine* swapRoutine = DBG_NEW Ugine::SwapRoutine(data->GetTransformA(), data->GetTransformB(), 10.0f);
	std::function<void(void)> function = std::bind(&Selectionsort::AfterSwapElements, this);
	swapRoutine->SetOnCompleted(function);

	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)swapRoutine);
}

void Selectionsort::AfterSwapElements()
{
	SetElementsColor(Ugine::Color::White());
	PairIndex++;
	firstElementIndex_++;

	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
	waitfor->SetOnCompleted(std::bind(&Selectionsort::SelectElements, this));
	newIteration = true;
}

