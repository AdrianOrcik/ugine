#pragma once
#include <vector>
#include <functional>
#include <glm/glm.hpp>

#include "../sorting_element.h"
#include "ugine/ecs/components/transform_component.h"


//todo: check factory pattern for algos building
class SortingAlgo
{
public:
	virtual void Sort() = 0;

	std::vector<SortingElement*> Elements;
	std::vector<SortingElement> ElementsCopy;

	std::vector< std::vector<SortingElement*> > StepArrays;
	std::vector< std::vector<SortingElement> > StepArraysCopy;

	std::function<void()> OnSimulationStart;
	std::function<void()> OnSimulationDone;
	std::function<void()> OnSimulationInterrupt;

	int StepIndex = 0;
	int StepArrayIndex = 0;

	void SetElements(std::vector<SortingElement*> elements) 
	{ 
		Elements = elements;
		for (auto e : Elements)
		{
			ElementsCopy.push_back(*e);
		}
	}

	void AddStepArray(std::vector<SortingElement*> data)
	{
		std::vector<SortingElement> arr;
		for (auto d : data)
		{
			arr.push_back(*d);
		}

		StepArrays.push_back(data);
		StepArraysCopy.push_back(arr);
	}

	void SetElementsColor(glm::vec4 color)
	{
		for (int i = 0; i < Elements.size(); i++)
		{
			Ugine::RendererComponent* renderer =
				(Ugine::RendererComponent*)Elements[i]->owner->GetComponent<Ugine::RendererComponent>();
			renderer->SetColor(color);
		}
	}

	void SetElementColor(int index, glm::vec4 color)
	{
		Ugine::RendererComponent* renderer =
			(Ugine::RendererComponent*)Elements[index]->owner->GetComponent<Ugine::RendererComponent>();
		renderer->SetColor(color);
	}

	void SetElementsTransform()
	{
		for (int i = 0; i < Elements.size(); i++)
		{
			Ugine::TransformComponent* transform =
				(Ugine::TransformComponent*)Elements[i]->owner->GetComponent<Ugine::TransformComponent>();
			transform->SetLocalPosition(glm::vec2((float)i / 10.0f , 0.0f));
		}
	}

	//DEBUG
	void SetElementSortedPosition()
	{
		for (int i = 0; i < Elements.size(); i++)
		{
			Elements[i]->SortedPosition = i;
		}
	}

	//DEBUG
	void SetElementCurrentPosition()
	{
		for (int i = 0; i < Elements.size(); i++)
		{
			Elements[i]->CurrentPosition = i;
		}
	}


};