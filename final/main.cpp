 // T07
// 10427124 ¿Â±üŒ’   04106034 ºÎÕþÁØ 


# include "headFile.h"

int main(int argc, char** argv) {
	vector<StuPairs> stuPairVectorReadFromFile;
	string filename;
	string filenameHead = "pairs";
	string filenameEnd = ".dat";
	int i = 0; // iterator variable
	int continueFlag = 0;  // The variable used to determine whether the program continues execution
	int listHeadArraySize = 0; 
	int originalStuPairVectorSize = 0;
	int maxStepSize = 0;
	int hashSize = 0;
	int sidPosition = 0;
	char missionTwoSid[16];
	StuPairs tempStuPair;
	StuPairs* stuPairsArray = NULL;
	ListHead* listHeadArray = NULL;
	ListHeadHashTable* listHeadHashTable = NULL;
	vector<string> maximumVertex;
	vector<StuPairs> maximumGraph;
	vector<StuPairsMinSid> sortedStuParisVector;
	vector<Dijkstra> dijkstraVector;
	vector<string> linkedVectex;
	Dijkstra* dijkstraArray = NULL;
	
	clock_t start, finish;  
	double duration = 0.0;
	
	cout << "*******************************************###***" << endl;
	cout << " On-machine Exercise                            *" << endl;
	cout << " Mission 1: Minimum Spanning Tree               *" << endl;
	cout << " Mission 2: Shortest Paths                      *" << endl;
	cout << "*******************************************###***" << endl;
	cout << "##############################################################" << endl;
	cout << "Mission 1: Minimum Spanning Tree" << endl;
	cout << "##############################################################" << endl << endl;
	
	cout << "Input the file name (e.g., 700): [0]Quit" << endl;
  	cin >> filename ;
  	
  	//start = clock();
  	while ( filename != "0" ) {
	    /*
			Read the student information file, split each single student information 
			and then store each single student information into a stuInfo Structre.
			push_back each stu info structure into the stuInfoVector
		*/	
	   	while( ReadBinaryFile(stuPairVectorReadFromFile, filenameHead + filename + filenameEnd).empty() ) // generate the input .txt file name
		{
			cout << filenameHead + filename + filenameEnd << " does not exist!!!" << endl << endl;
			cout <<"Input the file name (e.g., 600a, 601, 602a): [0]Quit" << endl;
			cin >> filename;
		}
		
		originalStuPairVectorSize = stuPairVectorReadFromFile.size();
		for(i = 0; i < originalStuPairVectorSize; i++)
		{
			strcpy(tempStuPair.sid_two, stuPairVectorReadFromFile[i].sid_one);
			//tempStuPair.sid_two = stuPairVectorReadFromFile[i].sid_one;
			strcpy(tempStuPair.sid_one, stuPairVectorReadFromFile[i].sid_two);
			//tempStuPair.sid_one = stuPairVectorReadFromFile[i].sid_two;
			tempStuPair.weight = stuPairVectorReadFromFile[i].weight;
			
			stuPairVectorReadFromFile.push_back(tempStuPair);
		}
		
		
		
		if( (stuPairsArray = (StuPairs*)calloc(stuPairVectorReadFromFile.size(), sizeof(StuPairs)) ) == NULL )
		{
			printf("calloc unsuccessful\n");
			exit(0);
		}
		
				
		for(i = 0; i < stuPairVectorReadFromFile.size(); i++)
		{
			stuPairsArray[i] = stuPairVectorReadFromFile[i];
		}
		
		/*
		HeapSort(stuPairsArray, stuPairVectorReadFromFile.size(), false);
		
		for(i = 0; i < stuPairVectorReadFromFile.size(); i++)
		{
			cout << stuPairsArray[i].weight <<  "  " << stuPairsArray[i].sid_one << "  " << stuPairsArray[i].sid_two << endl;
		}
		*/
		/*
			 using sid_one sort the student pairs array
		*/ 
		HeapSort(stuPairsArray, stuPairVectorReadFromFile.size(), true);  
		/*
			create adjacency list
		*/
		listHeadArray = CreateAdjacencyList(stuPairsArray, stuPairVectorReadFromFile.size(), listHeadArray, listHeadArraySize);
		/*
			output adjacency list to file
		*/
		OutputBinaryFile(listHeadArray, listHeadArraySize, filename);		
		
		printf("<<< %d  pairs => %d nodes >>>\n\n", stuPairVectorReadFromFile.size() / 2, stuPairVectorReadFromFile.size());
		printf("Adjacency lists are written into a file...\n\n\n") ;
		
		
		/*
			Using double hashing method to create a hash table, 
			associate each sid with its address in the listHeadArray. 
			Make it more quickly to get its list node by input a sid
		*/
		listHeadHashTable = CreateSidHashTable(listHeadArray, listHeadArraySize, maxStepSize, hashSize, listHeadHashTable);
		
		printf("<<< There are %d nodes in total. >>>\n\n", stuPairVectorReadFromFile.size());
		/*
		cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
		cout << "Mission 2: Shortest Paths" << endl;
		cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl << endl;
		*/
		/*
			DFS traverse the adjacency list, and output the result
		*/
		maximumVertex = DFSTraversal(listHeadArray, listHeadArraySize, listHeadHashTable, maxStepSize, hashSize);
		maximumGraph = BuildMaximumGraphRelationShip(maximumVertex, listHeadArray, listHeadHashTable, maxStepSize, hashSize);
	//	printf("maximumGraph Size == %d\n", maximumGraph.size());
		//Kruskal(maximumGraph);
		sortedStuParisVector = SortStuParisArray(maximumGraph); 		
		Kruskal(sortedStuParisVector, maximumVertex, listHeadHashTable, maxStepSize, hashSize);
				
		printf("Mission 2: Shortest Distances\n");
		printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");		
		for(i = 0; i < listHeadArraySize; i++)
		{
			if((i + 1) % 5 != 0)
				printf("\t%s", listHeadArray[i].sid_one);
				else
					printf("\t%s\n", listHeadArray[i].sid_one);
		}		
		printf("\nInput a student id from the above: \n");
		scanf("%s", missionTwoSid);		
		//linkedVectex = DFSTraversal_Dj(missionTwoSid, listHeadArray, listHeadArraySize, listHeadHashTable, maxStepSize, hashSize);
		//dijkstraVector = generateDijkstraArray(listHeadArray, listHeadArraySize, dijkstraVector, linkedVectex);
		dijkstraVector = generateDijkstraArray(listHeadArray, listHeadArraySize, dijkstraVector);
		dijkstraVector =  DijkstraAlgo(missionTwoSid, dijkstraVector, listHeadArray, listHeadArraySize, listHeadHashTable, maxStepSize, hashSize);
		
		dijkstraArray = (Dijkstra*)calloc(dijkstraVector.size(), sizeof(Dijkstra));
		for(i = 0; i < dijkstraVector.size(); i++)
		{
			dijkstraArray[i] = dijkstraVector.at(i);
			//printf("%s     %f\n", dijkstraVector.at(i).sid, dijkstraVector.at(i).length);
		}
		
		QuickSortDj(dijkstraArray, dijkstraVector.size(), 0, dijkstraVector.size() - 1 , 2);
		MissionTwoPrintf(dijkstraArray, dijkstraVector.size(), filename);
		
		
		
		/**/
		
		/*
		char name[16]; 
		cout << "input what you want to do in mission two\n";
		cin >> name;
		Ans ans;
		strcpy( ans.sid, name );
		for ( i = 0 ; i < stuPairVectorReadFromFile.size() ; i++ ) { //  »s§@¥ô°È¤G­n¨Ï¥Îªºµª®×®æ¦¡¤Î¸ê®Æµ²ºc  
			put_ans( stuPairVectorReadFromFile.at(i).sid_one, ans );
			put_ans( stuPairVectorReadFromFile.at(i).sid_two, ans );
		}
		
		//----------------------------------------------------------------
		//     play();  ¥ô°È¤G­n¨Ï¥Îªº¥D­nfunction  °O±o­n§ï 
		//---------------------------------------------------------------- 
		
		
		*/
		cin.clear();
		stuPairVectorReadFromFile.clear();
		dijkstraVector.clear();
		linkedVectex.clear();
		maximumVertex.clear();
	 	maximumGraph.clear();
		sortedStuParisVector.clear();
		stuPairsArray = NULL;
		listHeadArray = NULL;
		
		/*		
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;  
  	 	printf( "%lf seconds\n", duration );  
  	 	*/
		cout << "[0]Quit or [Any other key]continue?" << endl;
	    scanf("%d", &continueFlag);
	    
	    if(continueFlag == 0)
	    {
	    	free(stuPairsArray);
			free(listHeadArray);
			return 0;
		}
	    	
	    else{
	    	cout << "Input the file name (e.g., 600a, 601, 602a): [0]Quit" << endl;
	  		cin >> filename ;
	  	}
		
	}
	
	
	
	return 0;
}
