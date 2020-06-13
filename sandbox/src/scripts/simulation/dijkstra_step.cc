#include "dijkstra_step.h"

NodeStep::NodeStep(StepData data, NodeStep::Type stepType)
{
	data_ = data;
	stepType_ = stepType;
}

NodeStep::~NodeStep()
{
}

void NodeStep::Execute()
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

void NodeStep::OnSelectNode()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.02f);
	
	auto renderer = (Ugine::RendererComponent*)data_.Node->owner->GetComponent<Ugine::RendererComponent>();
	renderer->SetColor(Ugine::Color::Blue());

	waitfor->SetOnCompleted(std::bind(&NodeStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

void NodeStep::OnDrawFinalRoute()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.02f);

	auto renderer = (Ugine::RendererComponent*)data_.Node->owner->GetComponent<Ugine::RendererComponent>();
	renderer->SetColor(Ugine::Color::Yellow());

	waitfor->SetOnCompleted(std::bind(&NodeStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

