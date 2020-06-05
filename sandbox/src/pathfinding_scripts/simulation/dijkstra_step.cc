#include "dijkstra_step.h"

DijkstraStep::DijkstraStep(NodeElement grid[3][3], StepData data, DijkstraStep::Type stepType)
{
	CopyToGrid(grid);
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
	Ugine::WaitSeconds* waitfor = DBG_NEW Ugine::WaitSeconds(0.05f);
	
	auto renderer = (Ugine::RendererComponent*)grid_[data_.positionX][data_.positionY].owner->GetComponent<Ugine::RendererComponent>();
	renderer->SetColor(Ugine::Color::Blue());

	waitfor->SetOnCompleted(std::bind(&DijkstraStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)waitfor);
}

