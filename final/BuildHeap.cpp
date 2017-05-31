#include "headFile.h"

void BuildHeap(StuPairs *array, int size,  bool adjustType)
{
	int i = size / 2 - 1; // i represents the last non-leaf node
	
	for(; i >= 0; i--) // loop adjust to bulid a maximum heap
		AdjustHeap(array, i, size, adjustType);  // starting bulid heap
} 
