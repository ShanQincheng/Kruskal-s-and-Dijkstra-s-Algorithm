#include "headFile.h"

//void AdjustHeap(StudentNumberNode *array, int i, int size) // size is the array size, i represents the position in the array

 /**Determine whether the subtree has been adjusted. if yes return 1 else return 0;**/ 																			
int AdjustHeap(StuPairs *array, int i, int size, bool adjustType) // size is the array size, i represents the position in the array, true represent adjust sid_one and false represent adjust weight
{
	int leftChild = 2 * i + 1;	 // the left child node is twice the value of the parent node 
	int rightChild = 2 * i + 2; // the right child node is equal to twice the value of the parent node plus one
	int max = i;  // the temporary location of the largest node
	StuPairs temp;		 // exchange two node
	
	if(i <= size / 2 - 1)  // starting from the last none-leaf node
	{  
		if(adjustType)
		{
	//	if(leftChild <= size - 1 && array[leftChild].studentNumber > array[max].studentNumber)	
			if(leftChild <= size - 1 && (strcmp(array[leftChild].sid_one, array[max].sid_one) > 0))	
	//	if(leftChild <= size -1 && (atoi(array[leftChild].sid_one) > atoi(array[max].sid_one)) )
				max = leftChild;
	//	if(rightChild <= size - 1 && array[rightChild].studentNumber > array[max].studentNumber)
			if(rightChild <= size - 1 && (strcmp(array[rightChild].sid_one, array[max].sid_one) > 0))	
	//	if(rightChild <= size -1 && (atoi(array[rightChild].sid_one) > atoi(array[max].sid_one)) )
				max = rightChild;
		}else{
			if(leftChild <= size - 1 && (array[leftChild].weight > array[max].weight) )	
				max = leftChild;
			if(rightChild <= size - 1 && (array[rightChild].weight > array[max].weight))	
				max = rightChild;
		}
		if(max != i)
		{
			/*
			array[i] = array[i]^array[max];
			array[i] = array[i]^array[max];
			array[i] = array[i]^array[max];
			*/
			
			// exchange two numbers
			temp = array[i];
			array[i] = array[max];
			array[max] = temp;
										  // 避免調整以後以 max 為父節點的子樹不滿足最大堆 
			AdjustHeap(array, max, size, adjustType); // Avoid the adjustment of the parent tree with max as the parent does not satisfy the maximum heap
			
			return 1;
		}
		return 0;	
	}
}	
