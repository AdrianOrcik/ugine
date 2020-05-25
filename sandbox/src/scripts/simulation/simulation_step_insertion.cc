#include "simulation_step_insertion.h"

InsertionStep::InsertionStep(SortingAlgo * algo, StepData data, InsertionStepType stepType)
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
		case InsertionStepType::SelectElement:
			ElementSelect();
		break;
		case InsertionStepType::SelectPivot:
			PivotSelect();
			break;
		case InsertionStepType::Insert:
			Insertion();
			break;
	}
}

void InsertionStep::PivotSelect()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	sortingAlgo_->StepArrays[sortingAlgo_->ArrayIndex][data_.positionA]->GetRenderer()->SetColor(Ugine::Color::Blue());

	waitfor->SetOnCompleted(std::bind(&InsertionStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void InsertionStep::ElementSelect()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);

	sortingAlgo_->StepArrays[sortingAlgo_->ArrayIndex][data_.positionA]->GetRenderer()->SetColor(Ugine::Color::Red());
	waitfor->SetOnCompleted(std::bind(&InsertionStep::OnCompleted, this));

	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void InsertionStep::Insertion()
{
	InsertRoutine* insertRoutine = DBG_NEW InsertRoutine(data_.positionA, data_.positionB, 
		sortingAlgo_->StepArrays[sortingAlgo_->ArrayIndex], 10.0f);

	sortingAlgo_->ArrayIndex++;
	insertRoutine->SetOnCompleted(std::bind(&InsertionStep::OnCompleted, this));

	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)insertRoutine);
}
