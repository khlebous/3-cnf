#include <iostream>
#include "TxtReader.h"
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Wrong args count, should be path to .txt file" << endl;
		return 0;
	}

	TxtReader txtReader = TxtReader();
	vector<string> input = txtReader.ReadFile(argv[1]);
	
	cout << "Hello 3-cnf!" << endl;
	return 0;
}
