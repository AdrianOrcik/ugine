#include "example_layer.h"

ExampleLayer::ExampleLayer()
	: Layer("ExampleLayer"), cameraController_(1280.0f / 720.0f)
{

}

void ExampleLayer::OnAttach()
{
}

void ExampleLayer::OnDetach()
{
}

void ExampleLayer::OnUpdate(Ugine::Timestep ts)
{
}

void ExampleLayer::OnImGuiRender()
{
}

void ExampleLayer::OnEvent(Ugine::Event & e)
{
}
