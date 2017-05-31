# include "headFile.h"

void Kruskal(vector<StuPairsMinSid> sortedStuParisVector, vector<string> maximumVertex, ListHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize)
{
	int i = -1; // iterator variable
	//TwoThreeNode* treeNode = NULL;
	
	float totalWeight = 0.0;
	
	
	Initial_Set(maximumVertex, listHeadHashTable, maxStepSize, hashSize);
	for(i = 0; i < sortedStuParisVector.size(); i++)
	{
		if(Union_Set(sortedStuParisVector[i].stuPairs.sid_one, sortedStuParisVector[i].stuPairs.sid_two, listHeadHashTable, maxStepSize, hashSize))
		{
			totalWeight += 	sortedStuParisVector[i].stuPairs.weight;
		}		
	}
	
	printf("\nThe Cost of MST == %.4f\n", totalWeight);
	
	
	return;
}



void Initial_Set(vector<string> maximumVertex, ListHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize)  //場宎趙摩磁
{
    int i;
    char sid[16] = {};
    ListHeadHashTable currentStu;
   	// initial sets
	for(i = 0; i < maximumVertex.size(); i++)
	{
		strcpy(sid, maximumVertex[i].c_str());
		currentStu = GetAddressFromHashTable(listHeadHashTable, maxStepSize, hashSize, sid);
		strcpy(listHeadHashTable[currentStu.addressInHashTable].parent, sid);
		listHeadHashTable[currentStu.addressInHashTable].rank = 0;	
	}
	
	return;
}
 
char* Find_Set(char* sid, ListHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize)
{
	ListHeadHashTable currentStu;	
	currentStu = GetAddressFromHashTable(listHeadHashTable, maxStepSize, hashSize, sid);
	
	if(strcmp(sid, listHeadHashTable[currentStu.addressInHashTable].parent) != 0)
	{
		strcpy(listHeadHashTable[currentStu.addressInHashTable].parent, Find_Set(listHeadHashTable[currentStu.addressInHashTable].parent, listHeadHashTable, maxStepSize, hashSize));
	}
	
	return listHeadHashTable[currentStu.addressInHashTable].parent;
} 
 
 /*
int Find_Set(int x)        //脤梑x啋匼垀婓腔摩磁,隙咁奀揤坫繚噤
{
    if (x != father[x])
    {
        father[x] = Find_Set(father[x]); //隙咁奀揤坫繚噤
    }
    return father[x];
}
 */
bool Union_Set(char* sid_one, char* sid_two, ListHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize) 
{
	ListHeadHashTable currentStu_one, currentStu_two;	
	
	sid_one = Find_Set(sid_one, listHeadHashTable, maxStepSize, hashSize);
	sid_two = Find_Set(sid_two, listHeadHashTable, maxStepSize, hashSize);
	if(strcmp(sid_one, sid_two) == 0)
		return false;
	currentStu_one = GetAddressFromHashTable(listHeadHashTable, maxStepSize, hashSize, sid_one);
	currentStu_two = GetAddressFromHashTable(listHeadHashTable, maxStepSize, hashSize, sid_two);
	if(listHeadHashTable[currentStu_one.addressInHashTable].rank > listHeadHashTable[currentStu_two.addressInHashTable].rank)
	{
		strcpy(listHeadHashTable[currentStu_two.addressInHashTable].parent, sid_one);
	}else{
		if(listHeadHashTable[currentStu_one.addressInHashTable].rank == listHeadHashTable[currentStu_two.addressInHashTable].rank)
		{
			listHeadHashTable[currentStu_two.addressInHashTable].rank++;
		}
		strcpy(listHeadHashTable[currentStu_one.addressInHashTable].parent, sid_two);
	}
	
	return true;
}


//typedef struct adjacencyListNode // the node of the adjacency list 
//{
//	char sid_two[16] = {}; // information of sid2
//	float weight = -1.0;  // information of weight
//	
//	struct adjacencyListNode* nextNode; // point to next list node
//}ListNode;
//
//typedef struct adjacencyListHead
//{
//	char sid_one[16] = {};
//	
//	struct adjacencyListNode* firstNode; // the first list node behind the list head
//}ListHead;

/*

void put_ans(char ch[], Ans ans) { // 把資料放進ANS裡 
	if ( strcmp( ans.sid, ch ) == 0 )
	for ( int i  = 0 ; i < ans.next.size() ; i++ ) {
	  if ( strcmp( ans.next.at(i).sid, ch ) == 0 ) return;	
	}
	store st;
	strcpy( st.sid, ch );
	st.length = -1;
	st.visited = false;
	ans.next.push_back( st );
}

bool is_done( Ans ans ) {
	for ( int i = 0 ; i < ans.next.size() ; i++ ) if ( ans.next.at(i).visited == false ) return false;
	else return true;
}

int find_ans( char ch[], Ans ans ) { // 找尋在ANS裡的位置 
	for ( int i = 0 ; i < ans.next.size() ; i++ )
		if ( strcmp( ch, ans.next.at(i).sid ) == 0 ) return i;
	return -1;
}

void play( Ans &ans, ListHead* listHeadArray, ListHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize ) {
	int seat = -1, count = 100;
	ListHeadHashTable hashContent;
	ListHead headContent;
	ListNode* headListNode = NULL;
	Store tempStore;
	
	hashContent = GetAddressFromHashTable(listHeadHashTable, maxStepSize, hashSize, ans.sid); 
	headContent = listHeadArray[hashContent.addressInListHead];
	headListNode = headContent.firstNode;

    while(true)
    {
    	strcpy(tempStore.sid, headListNode->sid_two);
    	//tempStore.sid = headListNode->sid_two;
    	tempStore.length = headListNode->weight;
    	tempStore.visited = false;
    	
    	ans.next.push_back(tempStore);
    	if(headListNode->nextNode == NULL)
    		break;
    		else
    			headListNode = headListNode->nextNode;
	}
    for( bool finish == false ; !finish ; finish = is_done(ans) ) {
    	for( int i = 0 ; i < ans.next.size() ; i++ ) { // 尋找目前最短路徑 
        	if ( ans.next.at(i).value != -1 && ans.next.at(i).value < count) {
        		seat == i;
        		count == ans.next.at(i).value;
			}
		}
		for(  )  { // now = 目前最小路徑 temp = 目前最小路徑對應的SID可以到的所有位置 
			//if ( ans.next.at(find_ans(temp)).value == -1) { ans.next.at(find_ans(對應的SID可以到的位置)).value = count + ( now 到 temp 的距離 ) };
			//else if( ans.next.at(find_ans(temp)).value > count + ( now 到 temp 的距離 ) ) { ans.next.at(find_ans(對應的SID可以到的位置)).value = count + ( now 到 temp 的距離 ) };
			//其實上面兩行可以合併 
		}
		ans.next.at(i).visited = true;	// now標示為處理完成 
	}
} 

*/
