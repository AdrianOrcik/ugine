#include "sorting_manager.h"
#include <utility>

void SortingManager::StepMove()
{
	//if (index_ < BubbleElements.size()) {
	//	SortingElementData* data = BubbleElements[index_];

	//	data->GetRenderA()->SetColor(Ugine::Color::Red());
	//	data->GetRenderB()->SetColor(Ugine::Color::Red());

	//	Ugine::SwapRoutine* swapRoutine = new Ugine::SwapRoutine(data->GetTransformA(), data->GetTransformB(), 1.0f);
	//	
	//	std::function<void(void)> function = std::bind(&SortingManager::SwapRoutineCompleted, this);
	//	swapRoutine->SetOnCompleted(function);

	//	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)swapRoutine);
	//}
	//else {
	//	LOG_ERROR("No More Steps!");
	//	index_ = 0;
	//}

	SelectElements();
}

void SortingManager::SelectElements()
{
	if (!HasElements())
	{
		LOG_ERROR("No More Steps!");
		index_ = 0;
		return;
	}

	SortingElementData* data = BubbleElements[index_];

	data->GetRenderA()->SetColor(Ugine::Color::Blue());
	data->GetRenderB()->SetColor(Ugine::Color::Blue());

	Ugine::WaitSeconds* waitfor = new Ugine::WaitSeconds(1.0f);
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);

	if (data->IsSwaped)
		waitfor->SetOnCompleted(std::bind(&SortingManager::SwapElements, this));
	else
		waitfor->SetOnCompleted(std::bind(&SortingManager::UnselectElements, this));
}

void SortingManager::SwapElements()
{
	if (HasElements()) {
		SortingElementData* data = BubbleElements[index_];

		data->GetRenderA()->SetColor(Ugine::Color::Red());
		data->GetRenderB()->SetColor(Ugine::Color::Red());

		//todo: implement some logic operation into sorting elements data
		int currentA = data->GetSortingElementA()->CurrentPosition;
		int currentB = data->GetSortingElementB()->CurrentPosition;
		
		//LOG_TRACE("Value: {0} | CurrentPosition: {1} | SortedPosition: {2}", data->GetSortingElementA()->Value, data->GetSortingElementA()->CurrentPosition, data->GetSortingElementA()->CurrentPosition);
		//LOG_TRACE("Value: {0} | CurrentPosition: {1} | SortedPosition: {2}", data->GetSortingElementB()->Value, data->GetSortingElementB()->CurrentPosition, data->GetSortingElementB()->CurrentPosition);
		//
		data->GetSortingElementA()->CurrentPosition = currentB;
		data->GetSortingElementB()->CurrentPosition = currentA;

		Ugine::SwapRoutine* swapRoutine = new Ugine::SwapRoutine(data->GetTransformA(), data->GetTransformB(), 1.0f);
		std::function<void(void)> function = std::bind(&SortingManager::UnselectElements, this);
		swapRoutine->SetOnCompleted(function);

		Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)swapRoutine);
	}
	else {
		
		for (int i = 0; i < Elements.size(); i++)
		{
			Elements[i]->GetRenderer()->SetColor(Ugine::Color::Yellow());
		}

		LOG_ERROR("No More Steps!");
		index_ = 0;
	}
}

void SortingManager::UnselectElements()
{
	if (!HasElements()) 
	{
		LOG_ERROR("No More Steps!");
		index_ = 0;
		return;
	}

	SortingElementData* data = BubbleElements[index_];
	data->GetRenderA()->SetColor(Ugine::Color::White());
	data->GetRenderB()->SetColor(Ugine::Color::White());

	//check if elementA or elementB is on the sorted position

	//TODO: mark as finnish on the end of array if was main element, on change mark as sorted
	//TODO: more polish, now marked final also element which is on final position just by accident

	//if(data->GetSortingElementA()->CurrentPosition == data->GetSortingElementA()->SortedPosition)
	//	data->GetRenderA()->SetColor(Ugine::Color::Yellow());

	//if (data->GetSortingElementB()->CurrentPosition == data->GetSortingElementB()->SortedPosition)
	//	data->GetRenderB()->SetColor(Ugine::Color::Yellow());

	index_++;
	Ugine::WaitSeconds* waitfor = new Ugine::WaitSeconds(1.0f);
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
	waitfor->SetOnCompleted(std::bind(&SortingManager::StepMove, this));
}

void SortingManager::SwapRoutineCompleted()
{
	//SortingElementData* data = BubbleElements[index_];
	//data->GetRenderA()->SetColor(Ugine::Color::White());
	//data->GetRenderB()->SetColor(Ugine::Color::White());

	//index_++;
	//Ugine::WaitSeconds* waitfor = new Ugine::WaitSeconds(1.0f);
	//Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
	//waitfor->SetOnCompleted(std::bind(&SortingManager::StepMove, this));
}


