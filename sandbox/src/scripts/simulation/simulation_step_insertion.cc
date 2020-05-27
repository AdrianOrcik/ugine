#include "simulation_step_insertion.h"

InsertionStep::InsertionStep(SortingAlgo * algo, StepData data, Type stepType)
{
	sortingAlgo_ = algo;
	data_ = data;
	stepType_ = stepType;
}

InsertionStep::~InsertionStep()
{
}

void InsertionStep::Execute()
{
	switch (stepType_)
	{
		case Type::SelectElement:
			OnElementSelect();
		break;
		case Type::SelectPivot:
			OnPivotSelect();
			break;
		case Type::Insert:
			OnInsert();
			break;
	}
}

void InsertionStep::OnPivotSelect()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(Formulas::GetRoutineWaitTime());

	sortingAlgo_->SetElementsColor(Ugine::Color::DefaultElement());
	sortingAlgo_->StepArrays[sortingAlgo_->StepArrayIndex][data_.positionA]->GetRenderer()->SetColor(Ugine::Color::SelectElement());

	waitfor->SetOnCompleted(std::bind(&InsertionStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void InsertionStep::OnElementSelect()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(Formulas::GetRoutineWaitTime());

	sortingAlgo_->StepArrays[sortingAlgo_->StepArrayIndex][data_.positionA]->GetRenderer()->SetColor(Ugine::Color::MoveElement());
	waitfor->SetOnCompleted(std::bind(&InsertionStep::OnCompleted, this));

	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void InsertionStep::OnInsert()
{
	InsertRoutine* insertRoutine = DBG_NEW InsertRoutine(data_.positionA, data_.positionB, 
		sortingAlgo_->StepArrays[sortingAlgo_->StepArrayIndex], Formulas::GetRoutineWaitTime());

	sortingAlgo_->StepArrayIndex++;
	insertRoutine->SetOnCompleted(std::bind(&InsertionStep::OnCompleted, this));

	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)insertRoutine);
}
