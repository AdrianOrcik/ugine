#include "simulation_step_selection.h"

SelectionStep::SelectionStep(SortingAlgo * algo, StepData data, Type stepType)
{
	sortingAlgo_ = algo;
	data_ = data;
	stepType_ = stepType;
}

SelectionStep::~SelectionStep()
{
}

void SelectionStep::Execute()
{
	switch (stepType_)
	{
	case Type::SelectPivot:
		OnSelectPivot();
		break;
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

void SelectionStep::OnSelectPivot()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(Formulas::GetRoutineWaitTime());

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::Red());

	waitfor->SetOnCompleted(std::bind(&SelectionStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void SelectionStep::OnSelect()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(Formulas::GetRoutineWaitTime());

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::Red());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::Blue());

	waitfor->SetOnCompleted(std::bind(&SelectionStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void SelectionStep::OnBeforeSwap()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(Formulas::GetRoutineWaitTime());

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::Red());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::Red());

	waitfor->SetOnCompleted(std::bind(&SelectionStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void SelectionStep::OnSwap()
{
	Ugine::SwapRoutine* swapRoutine = DBG_NEW Ugine::SwapRoutine(data_.positionA, data_.positionB,
		sortingAlgo_->StepArrays[sortingAlgo_->StepArrayIndex], Formulas::GetRoutineWaitTime());

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::Purple());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::Purple());
	sortingAlgo_->StepArrayIndex++;

	swapRoutine->SetOnCompleted(std::bind(&SelectionStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)swapRoutine);
}

void SelectionStep::OnAfterSwap()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(Formulas::GetRoutineWaitTime());

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	
	waitfor->SetOnCompleted(std::bind(&SelectionStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}
