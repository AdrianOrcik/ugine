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

	void SetElementTransform()
	{
		//todo: constant values in one file
		for (int i = 0; i < Elements.size(); i++)
		{
			Ugine::TransformComponent* transform =
				(Ugine::TransformComponent*)Elements[i]->GetEntity()->GetComponent<Ugine::TransformComponent>();
			transform->SetLocalPosition({ (float)i / 10.0f, 0.0f });

			Elements[i]->CurrentPosition = i;
		}
	}

};