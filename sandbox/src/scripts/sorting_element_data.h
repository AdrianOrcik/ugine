#pragma once
#include "ugine.h"
#include "../scripts/sorting_element.h"

//TODO: REMOVE!
struct SortingPairElement
{
	Ugine::Entity* ElementA;
	Ugine::Entity* ElementB;
	bool IsSwaped;
	bool ValueA;
	bool ValueB;

	SortingPairElement(Ugine::Entity* elementA, Ugine::Entity* elementB, bool isSwaped)
		:ElementA(elementA), ElementB(elementB), IsSwaped(isSwaped)
	{
		ValueA = GetSortingElementA()->Value;
		ValueB = GetSortingElementB()->Value;
	}

	Ugine::TransformComponent* GetTransformA() { return (Ugine::TransformComponent*)ElementA->GetComponent<Ugine::TransformComponent>(); }
	Ugine::TransformComponent* GetTransformB() { return (Ugine::TransformComponent*)ElementB->GetComponent<Ugine::TransformComponent>(); }

	Ugine::RendererComponent* GetRenderA() { return (Ugine::RendererComponent*)ElementA->GetComponent<Ugine::RendererComponent>(); }
	Ugine::RendererComponent* GetRenderB() { return (Ugine::RendererComponent*)ElementB->GetComponent<Ugine::RendererComponent>(); }

	SortingElement* GetSortingElementA() { return (SortingElement*)ElementA->GetComponent<SortingElement>(); }
	SortingElement* GetSortingElementB() { return (SortingElement*)ElementB->GetComponent<SortingElement>(); }
};

struct SortingSingleElement
{
	Ugine::Entity* Element;
	bool IsSelected;
	bool IsLast;
	int Value;

	SortingSingleElement(Ugine::Entity* element, bool isSelected, bool isLast)
		:Element(element), IsSelected(isSelected), IsLast(isLast)
	{
		Value = GetSortingElement()->Value;
	}

	Ugine::TransformComponent* GetTransform() { return (Ugine::TransformComponent*)Element->GetComponent<Ugine::TransformComponent>(); }
	Ugine::RendererComponent* GetRender() { return (Ugine::RendererComponent*)Element->GetComponent<Ugine::RendererComponent>(); }
	SortingElement* GetSortingElement() { return (SortingElement*)Element->GetComponent<SortingElement>(); }
};