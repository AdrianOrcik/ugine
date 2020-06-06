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

	// Inherited via ScriptComponent
	virtual void OnInit() override
	{}
	virtual void OnUpdate(float Timestep) override
	{}
	virtual void OnActive() override
	{}
	virtual void OnDeactive() override
	{}

	int Value;
	int Index;
	int Row;
	int Col;
	int Distance = 999;

	bool IsVisited = false;
	bool IsWall = false;
	
	NodeElement* PreviousNode;
};