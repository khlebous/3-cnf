#include <iostream>
#include <map>
#include "TxtReader.h"
#include "TxtWriter.h"
#include "Formula.h"
#include "Parser.h"
#include "SatProblemSolver.h"
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Wrong args count." << endl;
		return 0;
	}

	vector<string> data = TxtReader::ReadFile(argv[1]);

	Formula formula;
	if (!Parser::TryParseStringToFormula(data, ' ', formula))
	{
		cout << "Cannot parse data to formula" << endl;
		return 0;
	}

	cout << "This is your formula:" << endl;
	cout << formula.ToString() << endl;

	SatProblemSolver sps = SatProblemSolver();
	map<int, bool> literalsMap;
	unordered_set<int> formulaLiterals = formula.GetLiterals();
	bool isSat = sps.Solve3Snf(formula, literalsMap);
	
	stringstream outputData = Parser::ParseToStringStream(isSat, formulaLiterals, literalsMap);
	TxtWriter::WriteToFile(argv[2], outputData);
	cout << outputData.str();

	return 0;
}
