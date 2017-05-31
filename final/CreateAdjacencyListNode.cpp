# include "headFile.h"

ListHead* CreateAdjacencyListNode(StuPairs* array, int arraySize, ListHead* listHeadArray)
{
	int currentPos = 0; // iterator variable
	int i = 0; // iterator variable
	char tempSid[16] = {}; // temporarily stores the sid in the array pointed to by currentPos 
	//int listHeadArraySize = 0;
	int listHeadArraySize = 0;
//	listHeadArray = (ListHead*)calloc(1, sizeof(ListHead));
//	ListHead* tempListHeadForRealloc = NULL;
	ListNode* listNode = NULL;
	ListNode* tempListNode = NULL;
	vector<StuPairs> belongToTheSameHeadNodeVector; // a vector store nodes belong to the same vector temporarily
	StuPairs* listNodeHeapArray = NULL;
	
	strcpy(tempSid, array[currentPos].sid_one);
	//tempSid = array[currentPos].sid_one;
//	strcpy(listHeadArray[listHeadArraySize].sid_one, array[currentPos].sid_one);
	//listHeadArray[listHeadArraySize].sid_one = array[currentPos].sid_one;
	belongToTheSameHeadNodeVector.push_back(array[currentPos]);
	listHeadArraySize++;
	currentPos++;
	

	while(true)
	{
		while( (currentPos < arraySize) && (strcmp(array[currentPos].sid_one, tempSid) == 0) )
		{	
			belongToTheSameHeadNodeVector.push_back(array[currentPos]);	
			currentPos++;
		}
	
		listNodeHeapArray = (StuPairs*) calloc(belongToTheSameHeadNodeVector.size(), sizeof(StuPairs));
		for(i = 0; i < belongToTheSameHeadNodeVector.size(); i++)
		{
			listNodeHeapArray[i] = belongToTheSameHeadNodeVector[i];
		}
		HeapSort(listNodeHeapArray, belongToTheSameHeadNodeVector.size(), false);
		for(i = 0; i < belongToTheSameHeadNodeVector.size(); i++)
		{
			listNode = (ListNode*)calloc(1, sizeof(ListNode));
			listNode->nextNode = tempListNode;
			strcpy(listNode->sid_two, listNodeHeapArray[i].sid_two);
		//	listNode->sid_two = listNodeHeapArray[i].sid_two;
			listNode->weight = listNodeHeapArray[i].weight;
			tempListNode = listNode;
			listNode = NULL;
		}
		belongToTheSameHeadNodeVector.clear(); // clear the vector for next store
		listHeadArray[listHeadArraySize - 1].firstNode = tempListNode;
//			free(listNode);
//			free(tempListNode);
//			free(listNodeHeapArray);
//			listNode = NULL;
		tempListNode = NULL;
		listNodeHeapArray = NULL;
		
		if(currentPos == arraySize)
		{
			break;
		}
		//tempSid = listHeadArray[currentPos].sid_one;
		strcpy(tempSid, array[currentPos].sid_one);
		//tempListHeadForRealloc = (ListHead*)realloc(listHeadArray, sizeof(listHeadArray) + sizeof(ListHead));
		/*
		tempListHeadForRealloc = (ListHead*) realloc (listHeadArray, (listHeadArraySize + 1) * sizeof(ListHead));
		if(!tempListHeadForRealloc)
		{
			free(listHeadArray);
			printf("realloc unsuccessful\n");
			exit(1);
		}
		listHeadArray = tempListHeadForRealloc; 
		strcpy(listHeadArray[listHeadArraySize].sid_one, array[currentPos].sid_one);
		//listHeadArray[listHeadArraySize].sid_one = array[currentPos].sid_one;
		*/
		listHeadArraySize++;
		//	currentPos++;
		
	}
	
		
	
	return listHeadArray;
}
