#include "pathfind_2d.h"

Pathfind_2d::Pathfind_2d()
	:Layer("Pathfind"), cameraController_(1280.0f / 720.0f, false, false, false)
{
}

Pathfind_2d::~Pathfind_2d()
{
}

void Pathfind_2d::OnAttach()
{
}

void Pathfind_2d::OnDetach()
{
}

void Pathfind_2d::OnUpdate(Ugine::Timestep ts)
{
}

void Pathfind_2d::OnImGuiRender()
{
}

void Pathfind_2d::OnEvent(Ugine::Event & e)
{
	cameraController_.OnEvent(e);
}
