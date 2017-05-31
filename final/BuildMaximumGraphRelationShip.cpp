# include "headFile.h"

vector<StuPairs> BuildMaximumGraphRelationShip(vector<string> maximumVertex, ListHead* listHeadArray, listHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize)
{
	ListHead currentListHead;
	ListNode* currentListNode;
	StuPairs currentStuPair;
	vector<StuPairs> maximumGraph;
	ListHeadHashTable currentStu;
	int i = -1; //iterator variable
	char sid[16] = {};
	
	for(i = 0; i < maximumVertex.size(); i++)
	{
		strcpy(sid, maximumVertex[i].c_str());
		
		currentStu = GetAddressFromHashTable(listHeadHashTable, maxStepSize, hashSize, sid);
		currentListHead = listHeadArray[currentStu.addressInListHead];
		strcpy(currentStuPair.sid_one, currentListHead.sid_one);
		currentListNode = currentListHead.firstNode;
		while(currentListNode != NULL)
		{
			strcpy(currentStuPair.sid_one, currentListHead.sid_one);
			strcpy(currentStuPair.sid_two, currentListNode->sid_two);
			currentStuPair.weight = currentListNode->weight;
			maximumGraph.push_back(currentStuPair);
			
			currentListNode = currentListNode->nextNode;
		}
		
	}
	
	return maximumGraph;
	
	
}
