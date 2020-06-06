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
	case Type::Coloring:
		OnColoring();
		break;
	}
}

void DijkstraStep::OnColoring()
{
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.5f);
	
	auto renderer = (Ugine::RendererComponent*)data_.Node->owner->GetComponent<Ugine::RendererComponent>();
	renderer->SetColor(Ugine::Color::Blue());

	waitfor->SetOnCompleted(std::bind(&DijkstraStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

