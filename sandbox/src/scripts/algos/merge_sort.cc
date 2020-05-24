#include "merge_sort.h"

MergeSort::MergeSort()
{
}

MergeSort::~MergeSort()
{
}

void MergeSort::Sort()
{
	index_ = 0;
	arrayIndex = 0;

	Merge(0, Elements.size() - 1);
	SetElementsTransform();
}

void MergeSort::Merge(int low, int high)
{
	int mid = 0;
	if (low < high)
	{
		// find middle of the array
		int mid = (low + high) / 2;

		// sort first half
		Merge(low, mid);
		// sort second half
		Merge(mid + 1, high);

		// merge together 
		MergeHelper(low, high, mid);
	}
}

void MergeSort::MergeHelper(int low, int high, int mid)
{
	int i, j, k;
	SortingElement* c[50];
	i = low;
	k = low;
	j = mid + 1;

	// merge array back into arr[low..high]
	while (i <= mid && j <= high)
	{
		if (Elements[i]->Value < Elements[j]->Value)
		{
			c[k] = Elements[i];
			i++;
		}
		else
		{
			c[k] = Elements[j];
			j++;
		}
		k++;
	}

	while (i <= mid)
	{
		c[k] = Elements[i];
		k++;
		i++;
	}

	while (j <= high)
	{
		c[k] = Elements[j];
		k++;
		j++;
	}

	for (i = low; i < k; i++)
	{
		Elements[i] = c[i];
	}
}
