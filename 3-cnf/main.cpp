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
	cout << boolalpha << isSat << endl;

	if (!isSat)
		return 0;

	for (auto& x : literalsMap)
	{
		formulaLiterals.erase(x.first);
		std::cout << x.first << "-" << x.second << std::endl;
	}
	if (formulaLiterals.size() > 0)
	{
		cout << "These literals can be any: ";
		for (auto l : formulaLiterals)
			std::cout << l << " ";
		cout << endl;
	}

	return 0;
}
