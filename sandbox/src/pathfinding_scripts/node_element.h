#pragma once

#include "ugine.h"
#include "../layers/sandbox_2d.h"
class Sandbox2D;
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

	void SetType(int number)
	{
		auto renderer = (Ugine::RendererComponent*) owner->GetComponent<Ugine::RendererComponent>();
		switch (number)
		{
		case 1:
			renderer->SetColor(Ugine::Color::White());
			break;
		case 2:
			renderer->SetColor(Ugine::Color::Red());
			IsWall = true;
			break;
		case 3:
			renderer->SetColor(Ugine::Color::Yellow());
			break;
		case 4:
			renderer->SetColor(Ugine::Color::Purple());
			break;
		default:
			break;
		}
	}

	// Inherited via ScriptComponent
	virtual void OnInit() override
	{}
	virtual void OnUpdate(float Timestep) override
	{}
	virtual void OnActive() override
	{}
	virtual void OnDeactive() override
	{}

	int Value = 0;
	int Index = 0;
	int Row = 0;
	int Col = 0;
	int Distance = 999;

	bool IsVisited = false;
	bool IsWall = false;
	
	NodeElement* PreviousNode = nullptr;
};