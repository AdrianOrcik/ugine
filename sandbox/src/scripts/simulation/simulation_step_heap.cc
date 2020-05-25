#include "simulation_step_heap.h"

HeapStep::HeapStep(SortingAlgo * algo, StepData data, Type stepType)
{
	sortingAlgo_ = algo;
	data_ = data;
	stepType_ = stepType;
}

HeapStep::~HeapStep()
{
}

void HeapStep::Execute()
{
	switch (stepType_)
	{
	case Type::BeforeSwap:
		OnBeforeSwap();
		break;
	case Type::Swap:
		OnSwap();
		break;
	case Type::AfterSwap:
		OnAfterSwap();
		break;
	}
}

void HeapStep::OnBeforeSwap()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->ArrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::Red());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->ArrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::Red());

	waitfor->SetOnCompleted(std::bind(&HeapStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void HeapStep::OnSwap()
{
	Ugine::SwapRoutine* swapRoutine = DBG_NEW Ugine::SwapRoutine(data_.positionA, data_.positionB,
		sortingAlgo_->StepArrays[sortingAlgo_->ArrayIndex], 10.0f);

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->ArrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::Purple());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->ArrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::Purple());
	sortingAlgo_->ArrayIndex++;

	swapRoutine->SetOnCompleted(std::bind(&HeapStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)swapRoutine);
}

void HeapStep::OnAfterSwap()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);

	sortingAlgo_->SetElementsColor(Ugine::Color::White());

	waitfor->SetOnCompleted(std::bind(&HeapStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}
