# include "headFile.h"

void OutputBinaryFile(ListHead* listHeadArray, int arraySize, string fileName)
{
	fstream outfile;
	ListNode* listNode;
	fileName = "OutPutBinary" + fileName + ".txt" ;
	outfile.open(fileName.c_str(), fstream::app) ;
	
	if ( !outfile.is_open() ) {
	cout << endl << fileName << " cannot be created!" << endl;
	}else{	
		outfile  << endl;
		for ( int i = 0; i < arraySize; i++ ) {
		  if (listHeadArray[i].firstNode != NULL) {
		    outfile << "[" << i << "]  " << listHeadArray[i].sid_one << ":" << endl;
		    listNode = listHeadArray[i].firstNode;
		    int j = 1;
		    while(listNode->nextNode != NULL)
		    {
		    	if((j-1) % 5 == 0)
		    		outfile << endl;
		    	outfile << "\t" << "(" << j << ") " << listNode->sid_two << ",  " << listNode->weight << "\t";
		    	listNode = listNode->nextNode;
		    	j++; 	
			}
			if((j-1) % 5 == 0)
		    	outfile << endl;
			outfile << "\t" << "(" << j << ") " << listNode->sid_two << ",  " << listNode->weight << "\t" << endl;;
		   }else{
		   		cout << "Unpredictable Error !" << endl;
		   		exit(1);
		   }
		} // for
		
		outfile << "data size:  " << arraySize << endl;
	}
	return;
}
