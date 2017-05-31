# include "headFile.h"

/*
	使用 HashTable 將 sid 與其存放在 AdjacencyList 中的位置相對應， 這樣操作避免了找尋一個 sid 需要遍曆 AdjacencyList 的麻煩 
*/
ListHeadHashTable* CreateSidHashTable(ListHead* listHeadArray, int listHeadArraySize, int& maxStepSize, int& hashSize, ListHeadHashTable* listHeadHashTable)
{
	hashSize = listHeadArraySize + 1; // size of the listHeadHashTable will be created
	maxStepSize = listHeadArraySize / 3 + 1;
	int stepSize = -1;
	int i = 0; // iterator variable
	int itemsNum = 0; // the number of items 
	int nextStoreAddress = 0; // if collision, store to the next address
	double collisionNum = 0.0; // calculae the number of collisions
	double listHeadArraySizeDouble = 0.0; // change listHeadArraySize from int to double , because the average compare time is double
	double sidAsciiSummation = 0.0; // the ascii number each character of sid 	
	double sidAsciiSumming = 0.0; 
	ListHeadHashTable tempListHeadHashTable;
	
	do{
		if(JudgeIfPrime(hashSize))  // determine whether current hashsize is a prime number
			break;
		else
			hashSize++;
	}while(true);  // calculate the hashSize
	do{
		if(JudgeIfPrime(maxStepSize))
			break;
		else
			maxStepSize++;
	}while(true); // calculate the maxStepSize
	
	listHeadHashTable = (ListHeadHashTable*)calloc(hashSize, sizeof(ListHeadHashTable));  // dynamic create a listHeadHashTable with hashSize
	
	for(i = 0; i < hashSize; i++)
	{
		strcpy(listHeadHashTable[i].sid, "");
		listHeadHashTable[i].addressInListHead = -1;
		listHeadHashTable[i].addressInHashTable = -1;
		listHeadHashTable[i].visited = false;
		listHeadHashTable[i].hvalue = -1;  // initial the hvalue of each item in the listHeadHashTable
	}
	
	for(i = 0; i < listHeadArraySize; i++)
	{
		sidAsciiSummation = CalculateSidAscii(listHeadArray[i].sid_one);  // calculate the summation of the product of each ascii  
		strcpy(tempListHeadHashTable.sid, listHeadArray[i].sid_one);
		tempListHeadHashTable.hvalue = fmod(sidAsciiSummation, hashSize); // calculate the hvalue by the sid of the student
		collisionNum++;  // add collision time
		if(listHeadHashTable[tempListHeadHashTable.hvalue].hvalue == -1)  // if current address is empty, just store
		{
			strcpy(listHeadHashTable[tempListHeadHashTable.hvalue].sid, tempListHeadHashTable.sid);
			listHeadHashTable[tempListHeadHashTable.hvalue].addressInHashTable = tempListHeadHashTable.hvalue;
			listHeadHashTable[tempListHeadHashTable.hvalue].addressInListHead = i;
			listHeadHashTable[tempListHeadHashTable.hvalue].hvalue = tempListHeadHashTable.hvalue;

		}else{ // if current address is full, find next address to store
			stepSize = maxStepSize - (fmod(sidAsciiSummation, maxStepSize));  // calculte the step size	
			nextStoreAddress = (tempListHeadHashTable.hvalue + stepSize) % hashSize; // calculte next address of the listHeadHashTable to store

			while(true)
			{
				collisionNum++;  // add collision time

				if(listHeadHashTable[nextStoreAddress].hvalue == -1)  // if next address is empty, just store
				{
					strcpy(listHeadHashTable[nextStoreAddress].sid, tempListHeadHashTable.sid);
				//	listHeadHashTable[nextStoreAddress].stuInfoStruct = tempListHeadHashTable.stuInfoStruct;
					listHeadHashTable[nextStoreAddress].addressInHashTable = nextStoreAddress;
					listHeadHashTable[nextStoreAddress].addressInListHead = i;
					listHeadHashTable[nextStoreAddress].hvalue = tempListHeadHashTable.hvalue;
					
					break;
				}else{  // if next address is full, try to find next of the next address 
					nextStoreAddress = (nextStoreAddress + stepSize) % hashSize;
				}
			}
			
		}
		
	}
	listHeadArraySizeDouble = listHeadArraySize;
	
	return listHeadHashTable;
	
}
