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
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	sortingAlgo_->StepArrays[sortingAlgo_->StepArrayIndex][data_.positionA]->GetRenderer()->SetColor(Ugine::Color::Blue());

	waitfor->SetOnCompleted(std::bind(&InsertionStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void InsertionStep::OnElementSelect()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);

	sortingAlgo_->StepArrays[sortingAlgo_->StepArrayIndex][data_.positionA]->GetRenderer()->SetColor(Ugine::Color::Red());
	waitfor->SetOnCompleted(std::bind(&InsertionStep::OnCompleted, this));

	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void InsertionStep::OnInsert()
{
	InsertRoutine* insertRoutine = DBG_NEW InsertRoutine(data_.positionA, data_.positionB, 
		sortingAlgo_->StepArrays[sortingAlgo_->StepArrayIndex], 10.0f);

	sortingAlgo_->StepArrayIndex++;
	insertRoutine->SetOnCompleted(std::bind(&InsertionStep::OnCompleted, this));

	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)insertRoutine);
}
