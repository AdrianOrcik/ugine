#include "simulation_step_bubble.h"

BubbleStep::BubbleStep(SortingAlgo * algo, StepData data, BubbleStep::Type stepType)
{
	sortingAlgo_ = algo;
	data_ = data;
	stepType_ = stepType;
}

BubbleStep::~BubbleStep()
{
}

void BubbleStep::Execute()
{
	switch (stepType_)
	{
	case Type::Select:
		OnSelect();
		break;
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

void BubbleStep::OnSelect()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(Formulas::GetRoutineWaitTime());

	sortingAlgo_->SetElementsColor(Ugine::Color::DefaultElement());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::SelectElement());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::SelectElement());

	waitfor->SetOnCompleted(std::bind(&BubbleStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void BubbleStep::OnBeforeSwap()
{
	OnSelect();
}

void BubbleStep::OnSwap()
{
	Ugine::SwapRoutine* swapRoutine = DBG_NEW Ugine::SwapRoutine(data_.positionA, data_.positionB,
		sortingAlgo_->StepArrays[sortingAlgo_->StepArrayIndex], Formulas::GetRoutineWaitTime());

	sortingAlgo_->SetElementsColor(Ugine::Color::DefaultElement());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::MoveElement());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::MoveElement());
	sortingAlgo_->StepArrayIndex++;
	swapRoutine->SetOnCompleted(std::bind(&BubbleStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)swapRoutine);
}

void BubbleStep::OnAfterSwap()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(Formulas::GetRoutineWaitTime());
	sortingAlgo_->SetElementsColor(Ugine::Color::DefaultElement());
	waitfor->SetOnCompleted(std::bind(&BubbleStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}
