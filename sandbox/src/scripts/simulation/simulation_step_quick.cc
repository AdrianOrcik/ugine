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
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(Formulas::GetRoutineWaitTime());

	sortingAlgo_->SetElementsColor(Ugine::Color::DefaultElement());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::SortedElement());

	waitfor->SetOnCompleted(std::bind(&QuickStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void QuickStep::OnSelectElement()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(Formulas::GetRoutineWaitTime());

	sortingAlgo_->SetElementsColor(Ugine::Color::DefaultElement());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::SelectElement());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::SelectElement());

	waitfor->SetOnCompleted(std::bind(&QuickStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void QuickStep::OnSelectRange()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(Formulas::GetRoutineWaitTime());

	sortingAlgo_->SetElementsColor(Ugine::Color::DefaultElement());
	
	if(data_.positionB != -1)
	{
		sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::SelectRange());
		sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::SelectRange());
	}
	else
	{
		sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::SelectRange());
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
		sortingAlgo_->StepArrays[sortingAlgo_->StepArrayIndex], Formulas::GetRoutineWaitTime());

	sortingAlgo_->SetElementsColor(Ugine::Color::DefaultElement());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionA].GetRenderer()->SetColor(Ugine::Color::MoveElement());
	sortingAlgo_->StepArraysCopy[sortingAlgo_->StepArrayIndex][data_.positionB].GetRenderer()->SetColor(Ugine::Color::MoveElement());
	sortingAlgo_->StepArrayIndex++;
	swapRoutine->SetOnCompleted(std::bind(&QuickStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)swapRoutine);
}

void QuickStep::OnAfterSwap()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(Formulas::GetRoutineWaitTime());
	sortingAlgo_->SetElementsColor(Ugine::Color::DefaultElement());
	waitfor->SetOnCompleted(std::bind(&QuickStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}
