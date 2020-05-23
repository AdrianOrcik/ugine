#include "simulation_step_bubble.h"

BubbleStep::BubbleStep(SortingAlgo * algo, StepData data, BubbleStepType stepType)
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
	case BubbleStepType::S_Select:
		ElementSelect();
		break;
	case BubbleStepType::S_BeforeSwap:
		BeforeSwap();
		break;
	case BubbleStepType::S_Swap:
		Swap();
		break;
	case BubbleStepType::S_AfterSwap:
		AfterSwap();
		break;
	}
}

void BubbleStep::ElementSelect()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->arrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::Blue());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->arrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::Blue());

	waitfor->SetOnCompleted(std::bind(&BubbleStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void BubbleStep::BeforeSwap()
{
	ElementSelect();
}

void BubbleStep::Swap()
{
	Ugine::SwapRoutine* swapRoutine = DBG_NEW Ugine::SwapRoutine(data_.positionA, data_.positionB,
		sortingAlgo_->StepArrays[sortingAlgo_->arrayIndex], 10.0f);

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->arrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::Red());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->arrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::Red());
	sortingAlgo_->arrayIndex++;
	swapRoutine->SetOnCompleted(std::bind(&BubbleStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)swapRoutine);
}

void BubbleStep::AfterSwap()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);
	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	waitfor->SetOnCompleted(std::bind(&BubbleStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}
