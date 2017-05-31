# include "headFile.h"

vector<string> DFSTraversal(ListHead* listHeadArray, int listHeadArraySize, ListHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize)
{
	int i = 0; // iterator variable
	int graphNumber = 0; // 記錄這是搜寻出来的第幾個子圖 
	int maximumVertexSize = 0;
	VisitStack* visitStackHead = NULL; // store graph nodes which were visited
	VisitStack* visitStackNode = NULL; // need a temp node to create new 
	ListHeadHashTable currentStu;   // current stu information in hash table, address in hashTable, address in listHeadArray
	ListHead currentListHead; // read the adjacency list head
	ListNode* currentListNode = NULL; // iterator read each node adjacent the list head
//	vector<string> graphSidVector; // store every graph node have gone
	vector<string> tempVertex; // store temporary graph, compare its size() with maximumVertex vector
	vector<string> maximumVertex; //  store the maximumVertex
	StuPairs* graphSidArray = NULL;  // store every graph node have gone in arrary for heap sort
	StuPairs putTogetherTwoNode;  // store two nodes sid_one sid_two and their weight
		
	for(i = 0; i < listHeadArraySize; i++) // make sure that each node is traversed once
	{
		currentStu = GetAddressFromHashTable(listHeadHashTable, maxStepSize, hashSize, listHeadArray[i].sid_one); // get current list head node information by sid
		//cout << currentStu.sid <
		if(currentStu.visited == false) // if current list head node is not visited yet
		{
			listHeadHashTable[currentStu.addressInHashTable].visited = true;  // mark current node visited
			visitStackNode = (VisitStack*)calloc(1, sizeof(VisitStack));  // create a new stack layer
			//strcpy(visitStackNode.sid, currentStu.sid);
			visitStackNode->listHead = listHeadArray[currentStu.addressInListHead]; // push current node informations into the stack
			visitStackNode->next = visitStackHead;
			visitStackHead = visitStackNode;  // make stack head point to the newest node
			
			tempVertex.push_back(currentStu.sid);		
//			graphSidVector.push_back(currentStu.sid);  // once a node is pushed into the stack, means that the node has been traversed and the node belongs to current graph
			
			while(visitStackHead != NULL)  // if the stack is not empty, it means that the map traversal is not finished yet
			{
				currentListHead = visitStackHead->listHead; // save current list head , use the head sid_one
				currentListNode = visitStackHead->listHead.firstNode;  // traverse all the list node adjacency the list head
			//	strcpy(putTogetherTwoNode.sid_one, currentListHead.sid_one);
				
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
							//strcpy(putTogetherTwoNode.sid_one, currentListHead.sid_one);
							//putTogetherTwoNode.sid_one = currentListHead.sid_one;
					//		strcpy(putTogetherTwoNode.sid_two, currentListNode->sid_two);
							//putTogetherTwoNode.sid_two = currentListNode.sid_two;
					//		putTogetherTwoNode.weight = currentListNode->weight;
					//		tempVertex.push_back(putTogetherTwoNode);
							
							visitStackNode = (VisitStack*)calloc(1, sizeof(VisitStack));
							//strcpy(visitStackNode.sid, currentStu.sid);
							visitStackNode->listHead = listHeadArray[currentStu.addressInListHead];
							visitStackNode->next = visitStackHead;
							visitStackHead = visitStackNode;
							listHeadHashTable[currentStu.addressInHashTable].visited = true;
							
							tempVertex.push_back(currentStu.sid);
			//				graphSidVector.push_back(currentStu.sid);  // once a node is pushed into the stack, means that the node has been traversed and the node belongs to current graph
										
							break;
						}else{
							currentListNode = currentListNode->nextNode; // keep going to find next list node adjacency the list head
						}
					}
				}
				
			}			
		}else{  // if current list head node is visited, keep going to find next unvisited list head, and then iterator its list node
			continue;
		}
		
		if(tempVertex.size() > maximumVertex.size())
		{
			maximumVertex.clear(); 
			maximumVertex.assign(tempVertex.begin(), tempVertex.end());
			
		} 
			
		tempVertex.clear();
		
					
		/*
			if the stack is empty, it means that we have travesed a sub map
			we need to printf current sub map and then keep going to find next sub map
		*/
		/*
		graphNumber++;
		graphSidArray = (StuPairs*)calloc(graphSidVector.size(), sizeof(StuPairs)); // create a node array for heap sort
		for(i = 0; i < graphSidVector.size(); i++)
		{
			strcpy(graphSidArray[i].sid_one, graphSidVector[i].c_str()); // copy each node from vector to array
			
			//graphSidArray[i].sid_one = graphSidVector[i];
		}
		HeapSort(graphSidArray, graphSidVector.size(), true);  // heap sort by the sid , strcmp
		MissionTwoPrintf(graphSidArray, graphSidVector.size(), graphNumber); // printf the sub map
		
		*/
		//printf("maximumVertex Size == %d\n", maximumVertex.size());
		
		//cout << "link size == " << graphSidVector.size() << endl;
	//	graphSidVector.clear(); // clear the vector to store next sub map
	}
	
	/*
	graphSidArray = (StuPairs*)calloc(maximumVertex.size(), sizeof(StuPairs));
	for(i = 0; i < maximumVertex.size(); i++)
	{
		graphSidArray[i] = maximumVertex[i];
	}
	HeapSort(graphSidArray, maximumVertex.size(), true);
	for(i = 0; i < maximumVertex.size(); i++)
	{
		printf("%f   %s  \  %s   %s\n", graphSidArray[i].weight, graphSidArray[i].sid_one, graphSidArray[i].sid_two);
	}
	*/
	//printf("maximumSize == %d\n", maximumVertex.size());
	//MissionTwoPrintf(graphSidArray, maximumVertex.size(),2);
	
	return maximumVertex;
}
