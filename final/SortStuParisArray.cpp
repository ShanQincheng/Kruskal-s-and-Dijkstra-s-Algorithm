# include "headFile.h"

vector<StuPairsMinSid> SortStuParisArray(vector<StuPairs> maximumGraphVector)
{
	StuPairs* maximumGraphArray = NULL;
	StuPairs* subSortArray = NULL;
	StuPairs* reallocPointer = NULL;
	StuPairsMinSid* sortGraphArray;
	int graphEdgeNumber = maximumGraphVector.size();
	int i = -1; // iterator variable
	int startAddress = -1;
	int endAddress = -1; // record subSortArray Size
	float tempWeight = -1;
	char tempSid[16] = {};
	vector<StuPairsMinSid> sortedPairsVector;

		
	maximumGraphArray = (StuPairs*)calloc(maximumGraphVector.size(), sizeof(StuPairs)); // create a node array for heap sort
	sortGraphArray = (StuPairsMinSid*)calloc(maximumGraphVector.size(), sizeof(StuPairsMinSid)); // create a array store the minimum Sid for heap sort
	for(i = 0; i < graphEdgeNumber; i++)
	{
		//strcpy(graphSidArray[i].sid_one, graphSidVector[i].c_str()); // copy each node from vector to array
		maximumGraphArray[i] = maximumGraphVector[i];
		//graphSidArray[i].sid_one = graphSidVector[i];
	}
	HeapSort(maximumGraphArray, graphEdgeNumber, false);  // heap sort according to weight 
	
	/*
	for(i = 0; i < graphEdgeNumber; i++)
	{
		cout << maximumGraphArray[i].weight << endl;
	}
	*/
	
	for(i = 0; i < graphEdgeNumber; i++)
	{
		sortGraphArray[i].stuPairs = maximumGraphArray[i];
	//	sortGraphArray[i].stuPairs.weight = maximumGraphArray[i].weight;  // ask professor     
		if(strcmp(maximumGraphArray[i].sid_one, maximumGraphArray[i].sid_two) < 0)
			strcpy(sortGraphArray[i].minSid, maximumGraphArray[i].sid_one);
			else
				strcpy(sortGraphArray[i].minSid, maximumGraphArray[i].sid_two);
	}
/*
	for(i = 0; i < graphEdgeNumber; i++)
	{				
		printf("%f   %s  \  %s   %s\n", sortGraphArray[i].stuPairs.weight, sortGraphArray[i].minSid, sortGraphArray[i].stuPairs.sid_one, sortGraphArray[i].stuPairs.sid_two);
	}
*/	
//	sortGraphArray = QuickSortAlgo(sortGraphArray, graphEdgeNumber, 0, (graphEdgeNumber - 1) );
	
	
	startAddress = 0;
//	strcpy(tempSid, maximumGraphArray[startAddress].sid_one);
	tempWeight = sortGraphArray[startAddress].stuPairs.weight;
	//subSortArray = (StuPairs*)calloc(1, sizeof(StuPairs));
	//subSortArray[0] = maximumGraphArray[0];	
	for(i = 0; i < graphEdgeNumber; i++)
	{
		//if(strcmp(maximumGraphArray[i].sid_one, tempSid) == 0)
		if(sortGraphArray[i].stuPairs.weight == tempWeight)
		{
			/*
			reallocPointer = (StuPairs*)realloc(subSortArray, ( (i - startAddress) + 1) * sizeof(StuPairs));
			subSortArray = reallocPointer;
			subSortArray[i - startAddress] = maximumGraphArray[i];
			*/
			continue;
		}else{
			endAddress = i;
			//HeapSort(subSortArray, endAddress - startAddress, true);
			QuickSortAlgo(sortGraphArray, graphEdgeNumber, startAddress, (endAddress - 1) );
			/*
			for(i = startAddress; i < endAddress; i++)
			{
				maximumGraphArray[i] = subSortArray[i - startAddress];
			}
			*/
			startAddress = endAddress;
			//strcpy(tempSid, maximumGraphArray[startAddress].sid_one);
			tempWeight = sortGraphArray[i].stuPairs.weight;
			//free(subSortArray);
			//subSortArray = NULL;
			//subSortArray = (StuPairs*)calloc(1, sizeof(StuPairs));
			//subSortArray[0] = maximumGraphArray[startAddress];	
		}
	} 
	
	/*
	for(i = 0; i < graphEdgeNumber; i++)
	{				
		printf("%f   %s  \  %s   %s\n", sortGraphArray[i].stuPairs.weight, sortGraphArray[i].minSid, sortGraphArray[i].stuPairs.sid_one, sortGraphArray[i].stuPairs.sid_two);
	}
	*/
	for(i = 0; i < graphEdgeNumber; i++)
	{
		sortedPairsVector.push_back(sortGraphArray[i]);
	}
	
	
	return sortedPairsVector;
}
