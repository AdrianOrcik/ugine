#pragma once
#include "ugine.h"
#include "../pathfinding_scripts/node_element.h"

enum NodeType { Regular, Wall, Start, Final };

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
	void GridGenerator();
	NodeElement* NodeGenerator(int index, glm::vec2 position);
public:
	Ugine::OrthographicCameraController cameraController_;
	//const int gridX_ = 5;
	//const int gridY_ = 5;
	//NodeElement grid_[5][5];
	const int rowSize_ = 20;
	const int colSize_ = 35;
	NodeElement* startNode_;
	NodeElement* finalNode_;
	std::vector<std::vector<NodeElement*>> grid_;
};