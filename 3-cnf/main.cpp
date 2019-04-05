#include <iostream>
#include "TxtReader.h"
#include "Formula.h"
#include "Parser.h"
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Wrong args count, should be path to .txt file" << endl;
		return 0;
	}

	vector<string> data = TxtReader::ReadFile(argv[1]);
	
	Formula formula;
	if (!Parser::TryParseStringToFormula(data, ' ', formula))
	{
		cout << "Cannot parse data to formula" << endl;
		return 0;
	}

	cout << "This is yout formula:" << endl;
	cout << formula.ToString() << endl;

	return 0;
}
