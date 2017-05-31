# include "headFile.h"

ListHead* CreateAdjacencyList(StuPairs* array, int arraySize, ListHead* listHeadArray, int& listHeadArraySize)
{
	int i = 0; // iterator variable
    listHeadArraySize = 0;
	ListNode* listNode;
	
	listHeadArray = CreateAdjacencyListHead(array, arraySize, listHeadArray, listHeadArraySize);
	//for(i = 0; i < listHeadArraySize; i++)
		//printf("%s\n",listHeadArray[i].sid_one);
	
	listHeadArray = CreateAdjacencyListNode(array, arraySize, listHeadArray);
	/*	
	cout << listHeadArraySize << endl;
	
	while(i < listHeadArraySize)
	{
		cout << listHeadArray[i].sid_one << "  ";
	//	printf("%.4lf", )
		if(listHeadArray[i].firstNode != NULL)
		{
			listNode = listHeadArray[i].firstNode;
			while(listNode->nextNode != NULL)
			{
				//cout << listNode->weight << "  ";
				printf("%.2lf", listNode->weight);
				printf("   ");
				listNode = listNode->nextNode;
			}
			//cout << listNode->weight << endl;
			if(listNode->weight != NULL)
				printf("%.2lf\n", listNode->weight);
			else
				printf("\n");
		}
		printf("\n\n");
		i++;
	}
	*/
	return listHeadArray;
}
