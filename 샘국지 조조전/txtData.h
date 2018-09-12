#pragma once
#include "singletonBase.h"

class txtData : public singletonBase <txtData>
{
public:
	HRESULT init(void);
	void release(void);

	//���̺�
	void saveTXT(const char* fileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);
	//1,2,100
	
	//�ε�
	vector<string> loadTXT(const char* fileName);
	vector<string> charArraySeparation(char charArray[]);


	txtData() {}
	~txtData() {}
};

