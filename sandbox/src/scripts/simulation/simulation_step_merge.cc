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
	std::cout << "OnSelectRange" << std::endl;
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	sortingAlgo_->StepArraysCopy[0][data_.positionA].GetRenderer()->SetColor(Ugine::Color::Red());
	sortingAlgo_->StepArraysCopy[0][data_.positionB].GetRenderer()->SetColor(Ugine::Color::Red());

	waitfor->SetOnCompleted(std::bind(&MergeStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void MergeStep::OnBeforeOverride()
{
	std::cout << "OnBeforeOverride" << std::endl;
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	sortingAlgo_->StepArraysCopy[0][data_.positionA].GetRenderer()->SetColor(Ugine::Color::Blue());
	sortingAlgo_->StepArraysCopy[0][data_.positionB].GetRenderer()->SetColor(Ugine::Color::Blue());

	waitfor->SetOnCompleted(std::bind(&MergeStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void MergeStep::OnOverrideValue()
{
	std::cout << "OnOverrideValue" << std::endl;
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.2f);

	sortingAlgo_->SetElementsColor(Ugine::Color::White());
	//need to setup which value where 
	float value = ((float)(data_.positionB / 10.0f));
	sortingAlgo_->StepArraysCopy[0][data_.positionA].GetTransform()->SetScale(glm::vec2(0.05f, value));
	sortingAlgo_->arrayIndex++;

	waitfor->SetOnCompleted(std::bind(&MergeStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void MergeStep::OnAfterOverride()
{
	std::cout << "OnAfterOverride" << std::endl;
	OnSelectRange();
}
