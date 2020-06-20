#include "simulation_step_merge.h"

MergeStep::MergeStep(SortingAlgo * algo, StepData data, Type stepType)
{
	sortingAlgo_ = algo;
	data_ = data;
	stepType_ = stepType;
}

MergeStep::~MergeStep()
{
}

void MergeStep::Execute()
{
	switch (stepType_)
	{
	case Type::SelectRange:
		OnSelectRange();
		break;
	case Type::OverrideValue:
		OnOverrideValue();
		break;
	case Type::BeforeOverride:
		OnBeforeOverride();
		break;
	case Type::AfterOverride:
		OnAfterOverride();
		break;
	}
}

void MergeStep::OnSelectRange()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(Formulas::GetRoutineWaitTime());

	sortingAlgo_->SetElementsColor(Ugine::Color::DefaultElement());
	sortingAlgo_->ElementsCopy[data_.positionA].GetRenderer()->SetColor(Ugine::Color::MoveElement());
	sortingAlgo_->ElementsCopy[data_.positionB].GetRenderer()->SetColor(Ugine::Color::MoveElement());

	waitfor->SetOnCompleted(std::bind(&MergeStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void MergeStep::OnBeforeOverride()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(Formulas::GetRoutineWaitTime());

	sortingAlgo_->ElementsCopy[data_.positionA].GetRenderer()->SetColor(Ugine::Color::SelectRange());

	waitfor->SetOnCompleted(std::bind(&MergeStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void MergeStep::OnOverrideValue()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(Formulas::GetRoutineWaitTime());

	float value = ((float)(data_.positionB / 10.0f));
	sortingAlgo_->ElementsCopy[data_.positionA].GetTransform()->SetScaleY(value);
	sortingAlgo_->StepArrayIndex++;

	waitfor->SetOnCompleted(std::bind(&MergeStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void MergeStep::OnAfterOverride()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(Formulas::GetRoutineWaitTime());

	sortingAlgo_->ElementsCopy[data_.positionA].GetRenderer()->SetColor(Ugine::Color::DefaultElement());

	waitfor->SetOnCompleted(std::bind(&MergeStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}
