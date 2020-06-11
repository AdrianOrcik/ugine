#include "dijkstra_step.h"

DijkstraStep::DijkstraStep(StepData data, DijkstraStep::Type stepType)
{
	data_ = data;
	stepType_ = stepType;
}

DijkstraStep::~DijkstraStep()
{
}

void DijkstraStep::Execute()
{
	switch (stepType_)
	{
	case Type::SelectNode:
		OnSelectNode();
		break;
	case Type::FinalRoute:
		OnDrawFinalRoute();
		break;
	}
}

void DijkstraStep::OnSelectNode()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.02f);
	
	auto renderer = (Ugine::RendererComponent*)data_.Node->owner->GetComponent<Ugine::RendererComponent>();
	renderer->SetColor(Ugine::Color::Blue());

	waitfor->SetOnCompleted(std::bind(&DijkstraStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void DijkstraStep::OnDrawFinalRoute()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.02f);

	auto renderer = (Ugine::RendererComponent*)data_.Node->owner->GetComponent<Ugine::RendererComponent>();
	renderer->SetColor(Ugine::Color::Yellow());

	waitfor->SetOnCompleted(std::bind(&DijkstraStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

