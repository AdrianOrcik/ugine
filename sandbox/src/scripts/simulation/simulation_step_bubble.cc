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
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->ArrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::Blue());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->ArrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::Blue());

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
		sortingAlgo_->StepArrays[sortingAlgo_->ArrayIndex], 10.0f);

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->ArrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::Red());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->ArrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::Red());
	sortingAlgo_->ArrayIndex++;
	swapRoutine->SetOnCompleted(std::bind(&BubbleStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)swapRoutine);
}

void BubbleStep::OnAfterSwap()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);
	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	waitfor->SetOnCompleted(std::bind(&BubbleStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}
