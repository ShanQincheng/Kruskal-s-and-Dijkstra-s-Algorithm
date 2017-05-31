# include "headFile.h"

ListHeadHashTable GetAddressFromHashTable(ListHeadHashTable* listHeadHashTable, int maxStepSize, int hashSize, char* sid)
{
	int stepSize = -1;
	int i = 0; // iterator variable
	int nextStoreAddress = 0; // if collision, store to the next address
	int hvalue = -1;
	double sidAsciiSummation = 0.0; // the ascii number each character of sid 		
	ListHeadHashTable emptyValue; // if can't find the sid in the hash table, return this to report main function
	
	emptyValue.hvalue = -2; // -2 represent this is a emptyValue, seach unsuccessful
	sidAsciiSummation = CalculateSidAscii(sid);  // calculate the summation of the product of each ascii  
	hvalue = fmod(sidAsciiSummation, hashSize); // calculate the hvalue by the sid of the student
	if( (listHeadHashTable[hvalue].hvalue != -1) && (strcmp(listHeadHashTable[hvalue].sid, sid) == 0) )  // If the first time to find the corresponding position sid
	{
		return listHeadHashTable[hvalue]; // return the listHeadHashTable struct, it contains some informaton about the sid node

	}else{ // if current address store other sid, go ahead to search next address
		stepSize = maxStepSize - (fmod(sidAsciiSummation, maxStepSize));  // calculte the step size				
		nextStoreAddress = (hvalue + stepSize) % hashSize; // calculte next address of the listHeadHashTable to store
		while(true)
		{
			if(hvalue == nextStoreAddress)  // already search all position in listHeadHashTable 
				return emptyValue;

			if(listHeadHashTable[nextStoreAddress].hvalue == -1) // current position is empty, represent the searching sid is inexistant
				return emptyValue;
			if(strcmp(listHeadHashTable[nextStoreAddress].sid, sid) == 0) // if get the sid at next address
			{
				return listHeadHashTable[nextStoreAddress];

			}else{  // if next address is full, try to find next of the next address 
				nextStoreAddress = (nextStoreAddress + stepSize) % hashSize;
			}
		}
		
	}
}
