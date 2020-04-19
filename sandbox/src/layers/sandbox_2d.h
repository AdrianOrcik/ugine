#pragma once
#include "ugine.h"
class Sandbox2D : public Ugine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Ugine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Ugine::Event& e) override;

public:
	Ugine::OrthographicCameraController cameraController_;

private:

	std::vector<Ugine::TransformComponent*> elements_;
	glm::vec4 squareColor_ = { 0.2f, 0.3f, 0.8f, 1.0f };
};