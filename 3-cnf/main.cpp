#include <iostream>
#include <map>
#include "TxtReader.h"
#include "Formula.h"
#include "Parser.h"
#include "SatProblemSolver.h"
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

	cout << "This is your formula:" << endl;
	cout << formula.ToString() << endl;

	SatProblemSolver sps = SatProblemSolver();
	map<int, bool> literalsMap;
	unordered_set<int> formulaLiterals = formula.GetLiterals();
	bool isSat = sps.Solve3Snf(formula, literalsMap);
	cout << "Is sat? " << boolalpha << isSat << endl;

	if (!isSat)
		return 0;

	map<int, bool>::iterator it;
	for (it = literalsMap.begin(); it != literalsMap.end(); it++ )
	{
		formulaLiterals.erase(it->first);
		std::cout << it->first << "-" << it->second << std::endl;
	}
	if (formulaLiterals.size() > 0)
	{
		cout << "These literals can be any: ";
		for (auto it1 = formulaLiterals.begin(); it1 != formulaLiterals.end(); it++ )
			std::cout << (*it1) << " ";
		cout << endl;
	}

	return 0;
}
