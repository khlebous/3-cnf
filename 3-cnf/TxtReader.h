#pragma once
#include <vector>
using namespace std; 

class TxtReader
{
public:
	TxtReader() {}
	~TxtReader() {}

	vector<string> ReadFile(string filename);
};

