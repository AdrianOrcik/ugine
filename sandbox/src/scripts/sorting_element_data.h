#pragma once
#include "ugine.h"
#include "../scripts/sorting_element.h"

struct SortingElementData
{
	Ugine::Entity* ElementA;
	Ugine::Entity* ElementB;
	bool IsSwaped;

	SortingElementData(Ugine::Entity* elementA, Ugine::Entity* elementB, bool isSwaped)
		:ElementA(elementA), ElementB(elementB), IsSwaped(isSwaped)
	{}

	Ugine::TransformComponent* GetTransformA() { return (Ugine::TransformComponent*)ElementA->GetComponent<Ugine::TransformComponent>(); }
	Ugine::TransformComponent* GetTransformB() { return (Ugine::TransformComponent*)ElementB->GetComponent<Ugine::TransformComponent>(); }

	Ugine::RendererComponent* GetRenderA() { return (Ugine::RendererComponent*)ElementA->GetComponent<Ugine::RendererComponent>(); }
	Ugine::RendererComponent* GetRenderB() { return (Ugine::RendererComponent*)ElementB->GetComponent<Ugine::RendererComponent>(); }

	SortingElement* GetSortingElementA() { return (SortingElement*)ElementA->GetComponent<SortingElement>(); }
	SortingElement* GetSortingElementB() { return (SortingElement*)ElementB->GetComponent<SortingElement>(); }
};