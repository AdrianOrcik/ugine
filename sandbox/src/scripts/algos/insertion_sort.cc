#include "insertion_sort.h"

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

	BaseElements = Elements;
	for (int i = 0; i < Elements.size() - 1; i++) 
	{
		Select(BaseElements[i],true, false);
		int j = i + 1;
		SortingElement* tmp = Elements[j];
		Select(BaseElements[i], false, false);
		while (j > 0 && tmp->Value < Elements[j - 1]->Value) {
			Elements[j] = Elements[j - 1];
			j--;
		}
		Elements[j] = tmp;
		Swap(Elements[j], tmp, true);
	}

	SetElementSortedPosition();
	//OnSimulationDone();
	
	//Debug
	//SetElementsTransform();
	//SwapElements();
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

