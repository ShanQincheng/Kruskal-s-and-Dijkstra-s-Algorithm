# include "headFile.h"

ListHead* CreateAdjacencyListHead(StuPairs* array, int arraySize, ListHead* listHeadArray, int& listHeadArraySize) // create a adjacency list head array
{
	int currentPos = 0; // iterator variable
	char tempSid[16] = {}; // temporarily stores the sid in the array pointed to by currentPos 
	//int listHeadArraySize = 0;
	listHeadArraySize = 0;
	listHeadArray = (ListHead*)calloc(1, sizeof(ListHead));
	ListHead* tempListHeadForRealloc = NULL;
	
	strcpy(tempSid, array[currentPos].sid_one);
	//tempSid = array[currentPos].sid_one;
	strcpy(listHeadArray[listHeadArraySize].sid_one, array[currentPos].sid_one);
	//listHeadArray[listHeadArraySize].sid_one = array[currentPos].sid_one;
	listHeadArraySize++;
	currentPos++;
	
	
	while(true)
	{
		while( (currentPos < arraySize) && (strcmp(array[currentPos].sid_one, tempSid) == 0) )
		{		
			currentPos++;
		}
		if(currentPos == arraySize)
			break;
		else{
			//tempSid = listHeadArray[currentPos].sid_one;
			strcpy(tempSid, array[currentPos].sid_one);
			//tempListHeadForRealloc = (ListHead*)realloc(listHeadArray, sizeof(listHeadArray) + sizeof(ListHead));
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
			listHeadArraySize++;
		//	currentPos++;
		}
	}
	
	
	
	return listHeadArray;
//	return listHeadArraySize;
}
