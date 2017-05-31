# include <iostream>	 // cout, endl
# include <vector>
# include <fstream>
# include <string.h> 
# include <stdlib.h>
# include <math.h>
# include <time.h>

using namespace std;

typedef struct stuPairs // define a struct, it will be read from file
{
	char sid_one[16] = {}; // information of sid1
	char sid_two[16] = {}; // information of sid2
	float weight = -1.0;   // the weight between student sid1 and sid2
}StuPairs;

typedef struct stuPairsMinSid
{
	StuPairs stuPairs;
	char minSid[16] = {};
}StuPairsMinSid;

typedef struct adjacencyListNode // the node of the adjacency list 
{
	char sid_two[16] = {}; // information of sid2
	float weight = -1.0;  // information of weight
	
	struct adjacencyListNode* nextNode; // point to next list node
}ListNode;

typedef struct adjacencyListHead
{
	char sid_one[16] = {};
	
	struct adjacencyListNode* firstNode; // the first list node behind the list head
}ListHead;

typedef struct listHeadHashTable
{
	char sid[16] = {};
	int addressInListHead = -1;
	int addressInHashTable = -1;
	bool visited = false;
	
	char parent[16] = {};
	int rank = -1;
	
	int hvalue = -1;	
}ListHeadHashTable;

typedef struct visitStack
{
	//char sid[16] = {};
	ListHead listHead;
	
	struct visitStack* next;
}VisitStack;

typedef struct store{  // ヴ叭ㄏノ ㄤ┮ΤSID 
	char sid[16];
	float length;
	bool visited;
}Store;

typedef struct AAns{ // ヴ叭ㄏノ  璶SID 
	char sid[16];
	vector<store> next;
} Ans;

typedef struct dijkstra{
	char sid[16];
	float length = -1;
	
	bool visited = false;
}Dijkstra;

vector<StuPairs>& ReadBinaryFile(vector<StuPairs> &, string); // read node pairs from binary file
int AdjustHeap(StuPairs *array, int i, int size, bool adjustType); // Determine whether the subtree has been adjusted. if yes return 1 else return 0;
void BuildHeap(StuPairs *array, int size,  bool adjustType); // build a min heap
void HeapSort(StuPairs *array, int size, bool adjustType); // heap sort function, adjustType == true, sort by sid, adjustType == false, sort by weight
ListHead* CreateAdjacencyList(StuPairs* array, int arraySize, ListHead* listHeadArray, int& listHeadArraySize); // create a adjacency list
ListHead* CreateAdjacencyListHead(StuPairs*, int, ListHead*, int& listHeadArraySize); // create a adjacency list head array
ListHead* CreateAdjacencyListNode(StuPairs* array, int arraySize, ListHead* listHeadArray); // create a adjacency node list
void OutputBinaryFile(ListHead* listHeadArray, int arraySize, string fileName); // output the binary file
bool JudgeIfPrime(int judgeNumber); // to determine whether a number is a prime number
double CalculateSidAscii(char* sid); // calculate sid each character ascii multiplication summation
ListHeadHashTable* CreateSidHashTable(ListHead* listHeadArray, int listHeadArraySize, int& maxStepSize, int& hashSize, ListHeadHashTable* listHeadHashTable); // using double hashing method create list head items hash table
ListHeadHashTable GetAddressFromHashTable(ListHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize, char* sid); // get address of the input sid 
vector<string> DFSTraversal(ListHead* listHeadArray, int listHeadArraySize, ListHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize); // DFS Traversal 
vector<StuPairs> BuildMaximumGraphRelationShip(vector<string> maximumVectex, ListHead* listHeadArray, listHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize); // Build the maximumGraph relationship between vertex and edges 
//void MissionTwoPrintf(StuPairs* stuPairArray, int stuPairsSize, int graphNumber); // printf mission two result to screen
//void ConnectedComponentsPrintf(StuPairs* stuPairArray, int stuPairsSize, int graphNumber); // printf connected components result to screen
void MissionTwoPrintf(Dijkstra* dijkstraArray, int arraySize, string fileName);
vector<StuPairsMinSid> SortStuParisArray(vector<StuPairs> maximumGraphVector); // sort the stu paris array according to weight and sid
StuPairsMinSid* QuickSortAlgo(StuPairsMinSid* array, int arraySize, int left, int right); // sort the minimum sid when weight is equal 
void Kruskal(vector<StuPairsMinSid> sortedStuParisVector, vector<string> maximumVertex, ListHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize); // Using Kruskal's Algorithm to build minimum spainning tree
void MissionTwoPrintf(StuPairs* stuPairArray, int stuPairsSize, int graphNumber);
void Initial_Set(vector<string> maximumVertex, ListHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize);  //初始化集合
char* Find_Set(char* sid, ListHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize);
bool Union_Set(char* sid_one, char* sid_two, ListHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize);
//vector<string> DFSTraversal_Dj(char* sid, ListHead* listHeadArray, int listHeadArraySize, ListHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize); // specify sid for dfs traversal
vector<Dijkstra> generateDijkstraArray(ListHead* listHeadArray, int listHeadArraySize, vector<Dijkstra> dijkstraVector);
//vector<Dijkstra> generateDijkstraArray(ListHead* listHeadArray, int listHeadArraySize, vector<Dijkstra> dijkstraVector, vector<string> linkedVectex); // generate a distance array for dijkstra's algorithms 
Dijkstra* QuickSortDj(Dijkstra* array, int arraySize, int left, int right, int sortType); // quick sort algo for dijkstra
vector<Dijkstra> DijkstraAlgo(char* sid, vector<Dijkstra> dijkstraVector, ListHead* listHeadArray, int listHeadArraySize, ListHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize); // Dijkstra's algorithm main function
