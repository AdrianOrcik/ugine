#pragma once
#include "ugine.h"

class ExampleLayer : public Ugine::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Ugine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Ugine::Event& e) override;

private:

	Ugine::ShaderLibrary sharedLibrary_;
	Ugine::Ref<Ugine::VertexArray> squareVA_;
	Ugine::Ref<Ugine::VertexArray> textureVA_;
	Ugine::Ref<Ugine::Texture2D> texture_;

	glm::vec3 cameraPosition_;
	float cameraMoveSpeed_ = 5.0f;

	float cameraRotation_ = 0.0f;
	float cameraRotationSpeed_ = 180.0f;

	Ugine::OrthographicCameraController cameraController_;
	glm::vec3 squareColor_ = { 1.0f, 1.0f, 1.0f };
};