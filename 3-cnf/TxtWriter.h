#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class TxtWriter
{
public:
	TxtWriter() {}
	~TxtWriter() {}

	static void WriteToFile(const string & filename, const stringstream & data)
	{
		ofstream file(filename);

		if (!file.is_open())
		{
			cout << "Cant open the file to write \"" << filename << "\"" << endl;
			return;
		}

		file << data.rdbuf();
		file.close();
	}
};
