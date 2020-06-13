#pragma once

#include "ugine.h"
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

	int operator<(const NodeElement& node) const
	{
		return Distance - node.Distance;
	}

	bool IsWall() { return nodeType_ == NodeFlag::Wall; }
	
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
			SetColor(Ugine::Color::Yellow());
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
	NodeElement* parent = nullptr;

	bool IsVisited = false;
	NodeElement* PreviousNode = nullptr;

private:
	NodeFlag nodeType_ = NodeFlag::Regular;
	Ugine::RendererComponent* renderer_ = nullptr;
};