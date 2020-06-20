#pragma once
#include "ugine.h"

class Sandbox2D : public Ugine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D();

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Ugine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Ugine::Event& e) override;

public:
	Ugine::OrthographicCameraController cameraController_;

private:

};