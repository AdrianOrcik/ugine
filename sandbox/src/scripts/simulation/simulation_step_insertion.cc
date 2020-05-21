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
		case InsertionStepType::ElementSelection:
			ElementSelection();
		break;
		case InsertionStepType::PivotSelection:
			PivotSelection();
			break;
		case InsertionStepType::Insertion:
			Insertion();
			break;
	}
}

void InsertionStep::PivotSelection()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	sortingAlgo_->StepArrays[sortingAlgo_->arrayIndex][data_.positionA]->GetRenderer()->SetColor(Ugine::Color::Blue());

	waitfor->SetOnCompleted(std::bind(&InsertionStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void InsertionStep::ElementSelection()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);

	sortingAlgo_->StepArrays[sortingAlgo_->arrayIndex][data_.positionA]->GetRenderer()->SetColor(Ugine::Color::Red());
	waitfor->SetOnCompleted(std::bind(&InsertionStep::OnCompleted, this));

	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void InsertionStep::Insertion()
{
	InsertRoutine* insertRoutine = DBG_NEW InsertRoutine(data_.positionA, data_.positionB, 
		sortingAlgo_->StepArrays[sortingAlgo_->arrayIndex], 10.0f);

	sortingAlgo_->arrayIndex++;
	insertRoutine->SetOnCompleted(std::bind(&InsertionStep::OnCompleted, this));

	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)insertRoutine);
}
