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
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(Formulas::GetRoutineWaitTime());

	sortingAlgo_->SetElementsColor(Ugine::Color::DefaultElement());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::MoveElement());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::MoveElement());

	waitfor->SetOnCompleted(std::bind(&HeapStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void HeapStep::OnSwap()
{
	Ugine::SwapRoutine* swapRoutine = DBG_NEW Ugine::SwapRoutine(data_.positionA, data_.positionB,
		sortingAlgo_->StepArrays[sortingAlgo_->StepArrayIndex], Formulas::GetRoutineWaitTime());

	sortingAlgo_->SetElementsColor(Ugine::Color::DefaultElement());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::MoveElement());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::MoveElement());
	sortingAlgo_->StepArrayIndex++;

	swapRoutine->SetOnCompleted(std::bind(&HeapStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)swapRoutine);
}

void HeapStep::OnAfterSwap()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(Formulas::GetRoutineWaitTime());

	sortingAlgo_->SetElementsColor(Ugine::Color::DefaultElement());

	waitfor->SetOnCompleted(std::bind(&HeapStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}
