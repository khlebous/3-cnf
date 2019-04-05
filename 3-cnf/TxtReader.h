#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "TxtReader.h"
using namespace std; 

class TxtReader
{
public:
	TxtReader() {}
	~TxtReader() {}

	static vector<string> ReadFile(string filename)
	{
		vector<string> data;
		ifstream file(filename);

		if (!file.is_open())
		{
			cout << "Cant open the file." << endl;
			return data;
		}

		string line;
		while (getline(file, line))
			data.push_back(line);

		file.close();

		return data;
	}
};

