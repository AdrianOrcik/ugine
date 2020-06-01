#pragma once
#include "ugine.h"
#include "../pf_scripts/node_element.h"

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
	NodeElement* BoxGenerator(int index, glm::vec2 position);

public:
	Ugine::OrthographicCameraController cameraController_;
	const int gridX_ = 35;
	const int gridY_ = 20;
	NodeElement grid_[35][20];
};