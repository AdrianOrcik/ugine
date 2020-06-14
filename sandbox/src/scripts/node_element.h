#pragma once

#include "ugine.h"
#include "definition.h"

class Sandbox2D;

enum NodeFlag
{
	Regular,
	Wall,
	Start,
	Target
};

class NodeElement : public Ugine::ScriptComponent
{
public:
	NodeElement()
	{}

	NodeElement(int col, int row, int index)
		: Col(col), Row(row), Index(index)
	{
		Value = index + 1;
	}

	~NodeElement()
	{}

	void DefaultState()
	{
		IsVisited = false;
		Distance = INFINITY;
		GlobalDistance = INFINITY;
		LocalDistance = INFINITY;
		Neighbours.clear();
		Parent = nullptr;
		PreviousNode = nullptr;
		nodeType_ = NodeFlag::Regular;
	}

	int operator<(const NodeElement& node) const
	{
		return Distance - node.Distance;
	}

	bool IsWall() { return nodeType_ == NodeFlag::Wall; }
	bool IsStart() { return nodeType_ == NodeFlag::Start; }
	bool IsEnd() { return nodeType_ == NodeFlag::Target; }
	bool IsStartOrEnd() { return IsStart() || IsEnd(); }

	void SetColor(glm::vec4 color)
	{
		renderer_->SetColor(color);
	}

	void SetType(NodeFlag nodeType)
	{
		nodeType_ = nodeType;
		switch (nodeType)
		{
		case Regular:
			SetColor(Ugine::Color::White());
			break;
		case Wall:
			SetColor(Ugine::Color::Red());
			break;
		case Start:
			SetColor(Ugine::Color::Green());
			break;
		case Target:
			SetColor(Ugine::Color::Purple());
			break;
		default:
			break;
		}
	}

	// Inherited via ScriptComponent
	virtual void OnInit() override
	{
		renderer_ = ECS_GET_COMPONENT(owner, Ugine::RendererComponent)
	}
	
	virtual void OnUpdate(float Timestep) override
	{}
	virtual void OnActive() override
	{}
	virtual void OnDeactive() override
	{}

public:
	int Value = 0;
	int Index = 0;
	int Row = 0;
	int Col = 0;
	int Distance = 999;

	float GlobalDistance = 999;
	float LocalDistance = 999;
	std::vector<NodeElement*> Neighbours;
	NodeElement* Parent = nullptr;

	bool IsVisited = false;
	NodeElement* PreviousNode = nullptr;

private:
	NodeFlag nodeType_ = NodeFlag::Regular;
	Ugine::RendererComponent* renderer_ = nullptr;
};