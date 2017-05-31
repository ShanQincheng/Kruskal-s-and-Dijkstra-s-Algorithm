#include "headFile.h"

int InsertHeap(StuPairs *array, StuPairs insertElement, int size)
{
	int parentNode = (size - 1) / 2; // parent node position
//	int position = size;  // last leaf node position	
	array[size] = insertElement; // insert the insertElement into the last position of the heap
	size = size + 1; // total element plus one
	
	while(parentNode >= 0)  // make the insetElement can swim to the root of the heap
	{
		if(AdjustHeap(array, parentNode, size) == 0) // if the subtree meets the maximum heap requirement
			break;
		if(parentNode - 1 == -1) // -1 / 2 == 0 I debug this for a long time !!!
			break;
		parentNode = (parentNode - 1) / 2;		
	}
	return size;
}
