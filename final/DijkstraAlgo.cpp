# include "headFile.h"

/*
	Dijkstra's algorithm main function
*/
vector<Dijkstra> DijkstraAlgo(char* sid, vector<Dijkstra> dijkstraVector, ListHead* listHeadArray, int listHeadArraySize, ListHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize)
{
	ListHeadHashTable currentStuHead;
	ListHeadHashTable currentStuNode;
	ListHead currentListHead;
	ListNode* currentListNode = NULL;
	// using this array to record how many sids connect to the searching sid and how far from them to the searching sid
	// this array main effect is to sorting and find out which sid has the shortest distance to the searching sid
	Dijkstra* shortestVectex = NULL; 
	Dijkstra* tempPointer = NULL;
	float sidToHereDistance = 0.0;
	int shortestVectexSize = 1;
	int startAddress = -1;
	int endAddress = -1;
	int tempWeight = -1;
	int i = -1; // iterator variable

	shortestVectex = (Dijkstra*)calloc(1, sizeof(Dijkstra));
	strcpy(shortestVectex[shortestVectexSize - 1].sid, sid);
	shortestVectex[shortestVectexSize - 1].length = 0;
	//  the distance from the searching sid to itself is 0
	dijkstraVector.at(GetAddressFromHashTable(listHeadHashTable, maxStepSize, hashSize, sid).addressInListHead).length = 0;

	while(true)
	{
		for(i = 0; i < shortestVectexSize; i++)
		{
			// if current sid has been visited, stip it
			if(dijkstraVector.at(GetAddressFromHashTable(listHeadHashTable, maxStepSize, hashSize, shortestVectex[i].sid).addressInListHead).visited)
				continue;
				// if current sid has not been visited, visit this sid and update the distance that those sid connected to this sid
				else{
					currentStuHead = GetAddressFromHashTable(listHeadHashTable, maxStepSize, hashSize, shortestVectex[i].sid);
					sidToHereDistance = dijkstraVector.at(currentStuHead.addressInListHead).length;
					dijkstraVector.at(currentStuHead.addressInListHead).visited = true;
					currentListHead = listHeadArray[currentStuHead.addressInListHead];
					currentListNode = currentListHead.firstNode;
					
					break;
				}
		}
		if(i == shortestVectexSize)   // All the sid connect to the searching sid has been visited, the Dijkstra's Algo is done
			break;
		
		while(true)
		{
			currentStuNode = GetAddressFromHashTable(listHeadHashTable, maxStepSize, hashSize, currentListNode->sid_two);	
			// if current sid has not been visited, and it is the first time to calculate the distance from the sid to the searching sid		
			if(dijkstraVector.at(currentStuNode.addressInListHead).visited == false && dijkstraVector.at(currentStuNode.addressInListHead).length == -1)
			{
				dijkstraVector.at(currentStuNode.addressInListHead).length = currentListNode->weight + sidToHereDistance;
			// if current sid has not been visited and it was calculated the distance
			// but now, the distance can be cut down through walk a another way
			}else if(dijkstraVector.at(currentStuNode.addressInListHead).visited == false 
			   			&& dijkstraVector.at(currentStuNode.addressInListHead).length > currentListNode->weight + sidToHereDistance){
				dijkstraVector.at(currentStuNode.addressInListHead).length = currentListNode->weight + sidToHereDistance;						
			// if current sid has been visited, continue to find next sid
			}else if(dijkstraVector.at(currentStuNode.addressInListHead).visited == true){
				if(currentListNode->nextNode == NULL)
					break;
				else{			
					currentListNode = currentListNode->nextNode;
					continue;
				}
			// if current sid has not been visited and it was calculated the distance
			// now, the distance still is a shotest distance, keep the value and the find next sid
			}else if(dijkstraVector.at(currentStuNode.addressInListHead).visited == false 
			   			&& dijkstraVector.at(currentStuNode.addressInListHead).length <= currentListNode->weight + sidToHereDistance){
			 	if(currentListNode->nextNode == NULL)
					break;
				else{			
					currentListNode = currentListNode->nextNode;
					continue;
				}			
			}else{	
				printf("error!!!\n");
				exit(-1);
			}
			
			// update the shortestVectex , update existing members or ( see below )
			for(i = 0; i < shortestVectexSize; i++)
			{
				if(strcmp(shortestVectex[i].sid, currentListNode->sid_two) == 0)
				{
					shortestVectex[i].length = dijkstraVector.at(currentStuNode.addressInListHead).length;
					break;
				}else
					continue;
			}
			// add new sid to the arry  
			if( i == shortestVectexSize)
			{
				tempPointer = (Dijkstra*)realloc(shortestVectex, ++shortestVectexSize * sizeof(Dijkstra));
				shortestVectex = tempPointer;
				shortestVectex[shortestVectexSize - 1].length = dijkstraVector.at(currentStuNode.addressInListHead).length;
				strcpy(shortestVectex[shortestVectexSize - 1].sid, currentListNode->sid_two);
			}			
			if(currentListNode->nextNode == NULL)
				break;
				else
					currentListNode = currentListNode->nextNode;
		}
		
		// sorting the shortestVectex to find out the sid which has both the shortest distance and minimum sid characters
		shortestVectex = QuickSortDj(shortestVectex, shortestVectexSize, 0, shortestVectexSize - 1, 1);		
		startAddress = 0;
		tempWeight = shortestVectex[startAddress].length;
		for(i = 0; i < shortestVectexSize; i++)
		{
			//if(strcmp(maximumGraphArray[i].sid_one, tempSid) == 0)
			if(shortestVectex[i].length == tempWeight)
			{
				continue;
			}else{
				endAddress = i;
				QuickSortDj(shortestVectex, shortestVectexSize, startAddress, (endAddress - 1), 2);
				startAddress = endAddress;
				tempWeight = shortestVectex[startAddress].length;	
			}
		} 
	} // while loop again
	
	return dijkstraVector;
} 

/*
	using DFS Traversal algorithm to paint a graph which contains all the sid connect to the searching sid
*/
/* 
vector<string> DFSTraversal_Dj(char* sid, ListHead* listHeadArray, int listHeadArraySize, ListHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize)
{
	int i = 0; // iterator variable
	int graphNumber = 0; // 記錄這是搜寻出来的第幾個子圖 
	int maximumVertexSize = 0;
	VisitStack* visitStackHead = NULL; // store graph nodes which were visited
	VisitStack* visitStackNode = NULL; // need a temp node to create new 
	ListHeadHashTable currentStu;   // current stu information in hash table, address in hashTable, address in listHeadArray
	ListHead currentListHead; // read the adjacency list head
	ListNode* currentListNode = NULL; // iterator read each node adjacent the list head
	vector<string> linkedVertex; // store temporary graph, compare its size() with maximumVertex vector
	StuPairs* graphSidArray = NULL;  // store every graph node have gone in arrary for heap sort
	StuPairs putTogetherTwoNode;  // store two nodes sid_one sid_two and their weight
		
		
	for(i = 0; i < hashSize; i++)
	{
		listHeadHashTable[i].visited = false;
	}
	//currentStu = GetAddressFromHashTable(listHeadHashTable, maxStepSize, hashSize, listHeadArray[i].sid_one); // get current list head node information by sid
	currentStu = GetAddressFromHashTable(listHeadHashTable, maxStepSize, hashSize, sid); // get current list head node information by sid

	listHeadHashTable[currentStu.addressInHashTable].visited = true;  // mark current node visited
	visitStackNode = (VisitStack*)calloc(1, sizeof(VisitStack));  // create a new stack layer
	visitStackNode->listHead = listHeadArray[currentStu.addressInListHead]; // push current node informations into the stack
	visitStackNode->next = visitStackHead;
	visitStackHead = visitStackNode;  // make stack head point to the newest node
	
	linkedVertex.push_back(currentStu.sid);		
	
	while(visitStackHead != NULL)  // if the stack is not empty, it means that the map traversal is not finished yet
	{
		currentListHead = visitStackHead->listHead; // save current list head , use the head sid_one
		currentListNode = visitStackHead->listHead.firstNode;  // traverse all the list node adjacency the list head
		
		while(true)
		{
			if(currentListNode == NULL) // to the end of current list node
			{
				visitStackHead = visitStackHead->next;  // pop() stack
				
				break;
			}else{	
				currentStu = GetAddressFromHashTable(listHeadHashTable, maxStepSize, hashSize, currentListNode->sid_two); // // get current list node information by sid
				if(currentStu.visited == false) // if the node is not visited yet, push it into the stack
				{
					visitStackNode = (VisitStack*)calloc(1, sizeof(VisitStack));
					visitStackNode->listHead = listHeadArray[currentStu.addressInListHead];
					visitStackNode->next = visitStackHead;
					visitStackHead = visitStackNode;
					listHeadHashTable[currentStu.addressInHashTable].visited = true;
					
					linkedVertex.push_back(currentStu.sid);
								
					break;
				}else{
					currentListNode = currentListNode->nextNode; // keep going to find next list node adjacency the list head
				}
			}
		}
		
	}		
	printf("linkedSize == %d\n", linkedVertex.size());
	
	return linkedVertex;		
}
*/


/*
	listHeadArray contains all sid  we need
	
	I use this array to initialize a vector<Dijkstra> for the subsequence processing
	all the sid which connect to the searching sid initialize length to -1 and all the not connected sid initialize length to -2
	
	vector<string> linkedVectex contains all the sid which connect to the searching sid, so we can use this vector determine whether 
	a sid connect to the searching sid
	
*/
//vector<Dijkstra> generateDijkstraArray(ListHead* listHeadArray, int listHeadArraySize, vector<Dijkstra> dijkstraVector, vector<string> linkedVectex)
vector<Dijkstra> generateDijkstraArray(ListHead* listHeadArray, int listHeadArraySize, vector<Dijkstra> dijkstraVector)
{
	int i = 0; // iterator variable
	int j = 0; // iterator variable
	char tempSid[16];
	Dijkstra tempDijkstra;
	
	for(i = 0; i < listHeadArraySize; i++) // the size of dijkstraArray is equal to listHeadArray
	{
		strcpy(tempDijkstra.sid, listHeadArray[i].sid_one);
		/*
		for(j = 0; j < linkedVectex.size(); j++) // using linkedVectex determine whether a sid connect to the searching sid
		{
			strcpy(tempSid, linkedVectex.at(j).c_str());		
			if(strcmp(listHeadArray[i].sid_one, tempSid) != 0)
				continue;
				else
					break;
		}
		if(j == linkedVectex.size())
			tempDijkstra.length = -2.0;
			//dijkstraVector.at(i).length = -2.0;
			else
				tempDijkstra.length = -1.0;
				//dijkstraVector.at(i).length = -1.0;
		*/
		//dijkstraVector.at(i).length = -1.0;
		tempDijkstra.length = -1.0;
		dijkstraVector.push_back(tempDijkstra);
	}
	
	
	return dijkstraVector;
}


/*
	prepare data for dijkstra algorithm using quick sort algorithm
	sortType: 1 represent sort according to distance
				2 represent sort according to sid
*/
Dijkstra* QuickSortDj(Dijkstra* array, int arraySize, int left, int right, int sortType)
{
	float pivotFloat = -1;
	char pivotString[16];
	if(sortType == 1)
	{
		//float pivot;
	//	pivot = -1.0;
		pivotFloat = array[left].length;
	}else if (sortType == 2)
	{
		//char pivot[16];
		strcpy(pivotString, array[left].sid);
	}else{
		printf("error QuickSort\n");
		exit(1);
	}
	int i, j; // iterator variable 
	Dijkstra tempStruct;
	//strcpy(pivot, array[left].minSid);
	
	i = left;
	j = right;
	
	if(left >= right)
		return array;
			
	while(true)
	{
		while(i < right)
		{
			if(sortType == 1)
			{
				if( array[i].length > pivotFloat)
				break;
				else
					i++;	
			}else if(sortType == 2){
				if( strcmp(array[i].sid, pivotString) > 0)
					break;
					else
						i++;
			}
			
		}
		
		while(j > left)
		{
			if(sortType == 1)
			{
				if( array[j].length < pivotFloat )
				break;
				else
					j--;
			}else if(sortType == 2){
				if( strcmp(array[j].sid, pivotString) < 0)
					break;
					else
						j--;
			}
			
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
	
	QuickSortDj(array, arraySize, left, j-1, sortType);
	QuickSortDj(array, arraySize, j+1, right, sortType);
	
}

