# include "headFile.h"


/*
	printf function for mission two

*/
void MissionTwoPrintf(Dijkstra* dijkstraArray, int arraySize, string fileName)
{
	int i = -1; // iterator variable
	int count = 0; // counting tool
	fstream outfile;
	
	printf("~~~~~ Shortest Distance ~~~~~~\n");
	for(i = 0; i < arraySize; i++)
	{
		if(dijkstraArray[i].length != -2)
		{
			if((count + 1) % 5 != 0)
				printf("(%d)\t%s . %.2f\t", ++count, dijkstraArray[i].sid, dijkstraArray[i].length);
				else{
					printf("(%d)\t%s . %.2f\n", ++count, dijkstraArray[i].sid, dijkstraArray[i].length);
				}
		}
			
	}
	printf("\n\n\n");
		
	fileName = "MinDist" + fileName + ".txt" ;
	outfile.open(fileName.c_str(), fstream::app) ;
	
	if ( !outfile.is_open() ) {
		cout << endl << fileName << " cannot be created!" << endl;
	}else{	
		outfile  << endl;
		for ( int i = 0; i < arraySize; i++ ) {	 
		  	if((i + 1) % 5 != 0)
		  	{
		  		if(dijkstraArray[i].length == -1)
		  			outfile << "(" << i << ")" << "\t"<< dijkstraArray[i].sid << ", " << "Inf" << "\t";
		  			else
		  				outfile << "(" << i << ")" << "\t"<< dijkstraArray[i].sid << ", " << dijkstraArray[i].length << "\t";
			}else{
				if(dijkstraArray[i].length == -1)
					outfile << "(" << i << ")" << "\t"<< dijkstraArray[i].sid << ", " << "Inf" << endl;
					else
		  				outfile << "(" << i << ")" << "\t"<< dijkstraArray[i].sid << ", " << dijkstraArray[i].length << "\n";
			}
		}	
	}
	return;	
}
