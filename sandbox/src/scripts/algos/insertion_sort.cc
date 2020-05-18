#include "insertion_sort.h"

InsertionSort::InsertionSort()
{
}

InsertionSort::~InsertionSort()
{
}

void InsertionSort::Sort()
{
	//OnSimulationStart();

	SetElementCurrentPosition();
	
	for (int i = 0; i < Elements.size() - 1; i++) {
		int j = i + 1;
		SortingElement* tmp = Elements[j];
		while (j > 0 && tmp->Value < Elements[j - 1]->Value) {
			Elements[j] = Elements[j - 1];
			j--;
		}
		Elements[j] = tmp;
	}

	SetElementSortedPosition();
	//OnSimulationDone();
	
	//Debug
	SetElementsTransform();
}
