#pragma once
#include "ugine.h"
#include "../scripts/node_element.h"
#include "../scripts/definition.h"

class Pathfind_2d : public Ugine::Layer
{
public:
	Pathfind_2d();
	virtual ~Pathfind_2d();

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Ugine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Ugine::Event& e) override;

private:
	int GetNodePosition(bool isEven, int end);
	
	bool IsWallNode(glm::vec2 position);

	void ResetGridStates();
	void RegenerateGrid();
	void GenerateGrid();
	void GenerateStartEndNode();

	NodeElement* CreateNode(int index, glm::vec2 position);

private:
	Ugine::OrthographicCameraController cameraController_;
	NodeElement* startNode_ = nullptr;
	NodeElement* finalNode_ = nullptr;
	std::vector<std::vector<NodeElement*>> grid_;
};