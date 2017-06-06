#include "headFile.h"

StuPairsMinSid* QuickSortAlgo(StuPairsMinSid* array, int arraySize, int left, int right)
{
	char pivot[16]  = {};
	int i, j; // iterator variable 
	StuPairsMinSid tempStruct;
	
	strcpy(pivot, array[left].minSid);
	i = left + 1;   // huge bug found here 
	j = right;
	
	if(left >= right)
		return array;
			
	while(true)
	{
		while(i < right)
		{
			if( strcmp(array[i].minSid, pivot) > 0)
				break;
				else
					i++;
		}
		
		while(j > left)
		{
			if( strcmp(array[j].minSid, pivot) < 0 )
				break;
				else
					j--;
		}
		
		if(i >= j)
			break;
		else{
			tempStruct = array[i];
			array[i] = array[j];
			array[j] = tempStruct;
		} 
	}
	tempStruct = array[left];
	array[left] = array[j];
	array[j] = tempStruct;
	
	QuickSortAlgo(array, arraySize, left, j-1);
	QuickSortAlgo(array, arraySize, j+1, right);
	
}
