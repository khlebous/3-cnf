#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Wrong arg count, should be path to .txt file" << endl;
		return 0;
	}

	cout << "Hello 3-cnf!" << endl;
	return 0;
}