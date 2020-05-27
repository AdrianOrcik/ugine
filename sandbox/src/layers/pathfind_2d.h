#pragma once
#include "ugine.h"

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

public:
	Ugine::OrthographicCameraController cameraController_;

};