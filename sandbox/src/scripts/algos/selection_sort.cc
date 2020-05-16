#include "selection_sort.h"
#pragma once

//TODO: make simulation
Selectionsort::Selectionsort()
{
}

Selectionsort::~Selectionsort()
{
}

void Selectionsort::Sort()
{
	SetElementCurrentPosition();
	for (int i = 0; i < Elements.size() - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < Elements.size(); j++)
		{
			//current + 1 < current
			if (Elements[j]->Value < Elements[minIndex]->Value) 
				minIndex = j;
		}
		Swap(Elements[i], Elements[minIndex], true);
	}
	SetElementSortedPosition();
	
	//Debug
	SetElementsTransform();
}
