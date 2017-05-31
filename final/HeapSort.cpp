#include "headFile.h"

void HeapSort(StuPairs *array, int size, bool adjustType)
{
	BuildHeap(array, size, adjustType); // make sure the array is a heap
	while(size > 0) // exchange from the last leaf to the root of the heap
	{
		StuPairs temp; // exchange root node and the last node need a temporary node
		int parentNode = (size - 1 - 1) / 2; // parentNode position
		
		temp = array[0];
		array[0] = array[size - 1];
		array[size - 1] = temp;
		
		//BuildHeap(array, --size, adjustType);
		AdjustHeap(array, 0, --size, adjustType);
	}
}
