#include "bubble_sort.h"

BubbleSort::BubbleSort()
{}

BubbleSort::~BubbleSort()
{}

void BubbleSort::Sort()
{
	SetElementTransform();

	for (int i = 0; i < Elements.size() - 1; i++)
	{
		for (int j = 0; j < Elements.size() - i - 1; j++)
		{
			if (Elements[j]->Value > Elements[j + 1]->Value)
			{
				Swap(Elements[j], Elements[j + 1], true);
			}
			else {
				Swap(Elements[j], Elements[j + 1], false);
			}
		}
	}

	SetElementSortedPosition();
	SelectElements();
}


void BubbleSort::SetElementsColor()
{
	for (int i = 0; i < Elements.size(); i++)
	{
		Ugine::RendererComponent* renderer = 
			(Ugine::RendererComponent*)Elements[i]->owner->GetComponent<Ugine::RendererComponent>();
		renderer->SetColor(Ugine::Color::White());
	}
}


void BubbleSort::SelectElements()
{
	if (!HasElements())
	{
		LOG_ERROR("No More Steps!");

		for (int i = 0; i < Elements.size(); i++)
		{
			Elements[i]->GetRenderer()->SetColor(Ugine::Color::Yellow());
		}

		ElementIndex = 0;
		return;
	}

	SortingElementData* data = BubbleElements[ElementIndex];

	data->GetRenderA()->SetColor(Ugine::Color::Blue());
	data->GetRenderB()->SetColor(Ugine::Color::Blue());

	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);

	if (data->IsSwaped)
		waitfor->SetOnCompleted(std::bind(&BubbleSort::SwapElements, this));
	else
		waitfor->SetOnCompleted(std::bind(&BubbleSort::UnselectElements, this));
}

void BubbleSort::SwapElements()
{
		if (HasElements()) {
		SortingElementData* data = BubbleElements[ElementIndex];

		data->GetRenderA()->SetColor(Ugine::Color::Red());
		data->GetRenderB()->SetColor(Ugine::Color::Red());

		//todo: implement some logic operation into sorting elements data
		int currentA = data->GetSortingElementA()->CurrentPosition;
		int currentB = data->GetSortingElementB()->CurrentPosition;
		
		data->GetSortingElementA()->CurrentPosition = currentB;
		data->GetSortingElementB()->CurrentPosition = currentA;

		Ugine::SwapRoutine* swapRoutine = DBG_NEW Ugine::SwapRoutine(data->GetTransformA(), data->GetTransformB(), 10.0f);
		std::function<void(void)> function = std::bind(&BubbleSort::UnselectElements, this);
		swapRoutine->SetOnCompleted(function);

		Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)swapRoutine);
	}
	else {
		
		for (int i = 0; i < Elements.size(); i++)
		{
			Elements[i]->GetRenderer()->SetColor(Ugine::Color::Yellow());
		}

		LOG_ERROR("No More Steps!");
		ElementIndex = 0;
	}
}

void BubbleSort::UnselectElements()
{
	if (!HasElements()) 
	{
		LOG_ERROR("No More Steps!");

		for (int i = 0; i < Elements.size(); i++)
		{
			Elements[i]->GetRenderer()->SetColor(Ugine::Color::Yellow());
		}

		ElementIndex = 0;
		return;
	}

	SortingElementData* data = BubbleElements[ElementIndex];
	data->GetRenderA()->SetColor(Ugine::Color::White());
	data->GetRenderB()->SetColor(Ugine::Color::White());

	//check if elementA or elementB is on the sorted position

	//TODO: mark as finnish on the end of array if was main element, on change mark as sorted
	//TODO: more polish, now marked final also element which is on final position just by accident
	//if(data->GetSortingElementA()->CurrentPosition == data->GetSortingElementA()->SortedPosition)
	//	data->GetRenderA()->SetColor(Ugine::Color::Yellow());

	//if (data->GetSortingElementB()->CurrentPosition == data->GetSortingElementB()->SortedPosition)
	//	data->GetRenderB()->SetColor(Ugine::Color::Yellow());

	ElementIndex++;
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
	waitfor->SetOnCompleted(std::bind(&BubbleSort::SelectElements, this));
}
