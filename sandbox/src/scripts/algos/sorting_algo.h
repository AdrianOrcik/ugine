#pragma once
#include <vector>
#include <functional>
#include <glm/glm.hpp>

#include "../sorting_element.h"
#include "../sorting_element_data.h"
#include "ugine/ecs/components/transform_component.h"


//todo: check factory pattern for algos building
class SortingAlgo
{
public:
	virtual void Sort() = 0;
	//TODO: make default settings during thesort begin 

	std::vector<SortingElement*> Elements;
	std::vector<SortingElement*>* ElementsPtr; //TODO: need it??
	void SetElements(std::vector<SortingElement*> elements) { Elements = elements; }

	//int PairIndex = 0;
	//std::vector<SortingPairElement*> SwapPair;
	//bool HasMorePair() { return PairIndex < SwapPair.size(); }
	//
	//int SingleIndex = 0;
	//std::vector<SortingSingleElement*> SelectSingle;

	//TODO: fix for selection sort
	//SingleIndex < SelectSingle.size()
	//bool HasMoreSingle() { return PairIndex < SwapPair.size(); }

	std::function<void()> OnSimulationStart;
	std::function<void()> OnSimulationDone;
	std::function<void()> OnSimulationInterrupt;

	int StepIndex = 0;
	int ArrayIndex = 0;

	//todo: need both?
	std::vector< std::vector<SortingElement*> > StepArrays;
	std::vector< std::vector<SortingElement> > StepArraysCopy;

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


	void Swap(SortingElement * elementA, SortingElement * elementB, bool isSwaped)
	{
		if (isSwaped) 
		{
			SortingElement temp = *elementA;
			*elementA = *elementB;
			*elementB = temp;
		}

		//SwapPair.push_back(DBG_NEW SortingPairElement(elementA->GetEntity(), elementB->GetEntity(), isSwaped));
	}

	//void Select(SortingElement * element, bool isSelected, bool isLastElement)
	//{
	//	SelectSingle.push_back(DBG_NEW SortingSingleElement(element->GetEntity(), isSelected, isLastElement));
	//}

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

	//void SwapPairClear()
	//{
	//	for (auto pair : SwapPair)
	//	{
	//		delete pair;
	//	}

	//	SwapPair.clear();
	//}

	//void SelectSingleClear()
	//{
	//	for (auto single : SelectSingle)
	//	{
	//		delete single;
	//	}

	//	SelectSingle.clear();
	//}

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

};