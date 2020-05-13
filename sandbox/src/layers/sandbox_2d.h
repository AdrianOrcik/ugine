#pragma once
#include "ugine.h"
#include "../scripts/sorting_element.h"

class SortingElement;
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

private:
	void CreateObject(int index, int generatedValue);
	void GenerateObjects();
public:
	Ugine::OrthographicCameraController cameraController_;
	static bool OnNext;
private:

	std::vector<Ugine::Entity*> gameObjects_;
	std::vector<SortingElement*> elements_;
	int elementCount_ = 3;
};