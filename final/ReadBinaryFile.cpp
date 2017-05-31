# include "headFile.h"

vector<StuPairs>& ReadBinaryFile(vector<StuPairs> &stuPairVector, string inputFileName)
{
	int len = 12; // vector size
	StuPairs stuPairStruct;
 	ifstream inF;  
 	
  	inF.open(inputFileName.c_str(), std::ifstream::binary);  	
	if(inF == NULL)
	{
		stuPairVector.clear();
		return stuPairVector;
	}else{
		while(!(inF.peek() == EOF))
		{
			inF.read(reinterpret_cast<char*>(&stuPairStruct), sizeof(stuPairStruct)*1);  
			stuPairVector.push_back(stuPairStruct);	
		}
		inF.close();  
	
		return stuPairVector;
	}
}
