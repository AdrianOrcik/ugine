#include "node_step.h"

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

	Ugine::FadeToColorRoutine* select = DBG_NEW Ugine::FadeToColorRoutine(data_.Node, 0.1f, Ugine::Color::SelectNode());
	select->SetOnCompleted(std::bind(&NodeStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)select);
}

void NodeStep::OnDrawFinalRoute()
{
	Ugine::FadeToColorRoutine* select = DBG_NEW Ugine::FadeToColorRoutine(data_.Node, 0.1f, Ugine::Color::PathNode());
	select->SetOnCompleted(std::bind(&NodeStep::OnCompleted, this));
	Ugine::RoutineManager::StartCoroutine((Ugine::IEnumerator<void>*)select);
}

