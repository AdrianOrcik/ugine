#include "simulation_step_quick.h"

QuickStep::QuickStep(SortingAlgo * algo, StepData data, Type stepType)
{
	sortingAlgo_ = algo;
	data_ = data;
	stepType_ = stepType;
}

QuickStep::~QuickStep()
{
}

void QuickStep::Execute()
{
	switch (stepType_)
	{
	case Type::SelectPivot:
		OnSelectPivot();
		break;
	case Type::SelectElement:
		OnSelectElement();
		break;
	case Type::SelectRange:
		OnSelectRange();
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

void QuickStep::OnSelectPivot()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->arrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::Yellow());

	waitfor->SetOnCompleted(std::bind(&QuickStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void QuickStep::OnSelectElement()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->arrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::Blue());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->arrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::Blue());

	waitfor->SetOnCompleted(std::bind(&QuickStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void QuickStep::OnSelectRange()
{
	LOG_INFO("OnSelectRange");
	LOG_INFO("RANGE: {0} - {1}", data_.positionA, data_.positionB);

	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	if(data_.positionB != -1)
	{
		sortingAlgo_->StepArraysCopy[sortingAlgo_->arrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::Green());
		sortingAlgo_->StepArraysCopy[sortingAlgo_->arrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::Green());
	}
	else
	{
		sortingAlgo_->StepArraysCopy[sortingAlgo_->arrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::Green());
	}
	waitfor->SetOnCompleted(std::bind(&QuickStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void QuickStep::OnBeforeSwap()
{
	OnSelectElement();
}

void QuickStep::OnSwap()
{
	Ugine::SwapRoutine* swapRoutine = DBG_NEW Ugine::SwapRoutine(data_.positionA, data_.positionB,
		sortingAlgo_->StepArrays[sortingAlgo_->arrayIndex], 10.0f);

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->arrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::Red());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->arrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::Red());
	sortingAlgo_->arrayIndex++;
	swapRoutine->SetOnCompleted(std::bind(&QuickStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)swapRoutine);
}

void QuickStep::OnAfterSwap()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);
	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	waitfor->SetOnCompleted(std::bind(&QuickStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}
