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
	std::vector<SortingElementData*> BubbleElements;
	int ElementIndex = 0;

	bool HasElements() { return ElementIndex < BubbleElements.size(); }
	void SetElements(std::vector<SortingElement*> elements) { Elements = elements; }

	void Swap(SortingElement * elementA, SortingElement * elementB, bool isSwaped)
	{
		BubbleElements.push_back(DBG_NEW SortingElementData(elementA->GetEntity(), elementB->GetEntity(), isSwaped));

		if (isSwaped) {
			SortingElement temp = *elementA;
			*elementA = *elementB;
			*elementB = temp;
		}
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

};