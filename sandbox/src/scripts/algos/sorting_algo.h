#pragma once
#include <vector>
#include "../sorting_element.h"
#include "../sorting_element_data.h"
#include "ugine/ecs/components/transform_component.h"

//todo: check factory pattern for algos building
class SortingAlgo
{
public:
	virtual void Sort() = 0;

	std::vector<SortingElement*> Elements;
	void SetElements(std::vector<SortingElement*> elements) { Elements = elements; }

	int PairIndex = 0;
	std::vector<SortingPairElement*> SwapPair;
	bool HasMorePair() { return PairIndex < SwapPair.size(); }
	
	int SingleIndex = 0;
	std::vector<SortingSingleElement*> SelectSingle;
	bool HasMoreSingle() { return PairIndex < SwapPair.size(); }

	void Swap(SortingElement * elementA, SortingElement * elementB, bool isSwaped)
	{
		if (isSwaped) {
			SortingElement temp = *elementA;
			*elementA = *elementB;
			*elementB = temp;
		}

		SwapPair.push_back(DBG_NEW SortingPairElement(elementA->GetEntity(), elementB->GetEntity(), isSwaped));
	}

	void SetElementSortedPosition()
	{
		for (int i = 0; i < Elements.size(); i++)
		{
			Elements[i]->SortedPosition = i;
		}
	}

	void SetElementCurrentPosition()
	{
		for (int i = 0; i < Elements.size(); i++)
		{
			Elements[i]->CurrentPosition = i;
		}
	}

	void StepElementsClear()
	{
		for (auto bubble : SwapPair)
		{
			delete bubble;
		}

		SwapPair.clear();
	}

	void SetElementsColor()
	{
		for (int i = 0; i < Elements.size(); i++)
		{
			Ugine::RendererComponent* renderer =
				(Ugine::RendererComponent*)Elements[i]->owner->GetComponent<Ugine::RendererComponent>();
			renderer->SetColor(Ugine::Color::White());
		}
	}

};