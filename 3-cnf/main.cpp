#include <iostream>
#include <map>
#include "TxtReader.h"
#include "TxtWriter.h"
#include "Formula.h"
#include "Parser.h"
#include "SatProblemSolver.h"
using namespace std;

bool GetClauseValue(Clause c, map<int, bool> map)
{
	for (size_t i = 0; i < c.Size(); i++)
	{
		int iteral = c[i];
		if (iteral >= 0 && map[iteral] || iteral < 0 && !map[-iteral])
			return true;
	}

	return false;
}

bool GetFormulaValue(Formula f, map<int, bool> map)
{
	for (size_t i = 0; i < f.ClausesCount(); i++)
		if (!GetClauseValue(f[i], map))
			return false;

	return true;
}

int main(int argc, char* argv[])
{
	/*if (argc != 3)
	{
		cout << "Wrong args count." << endl;
		return 0;
	}*/

	vector<string> data;// = TxtReader::ReadFile(argv[1]);


	data.push_back("-3 2 -4");
	data.push_back("-5 4 2");
	data.push_back("-1 1 -4");
	data.push_back("4 -4 -4");
	data.push_back("-4 2 3");
	data.push_back("-2 5 -3");
	data.push_back("-2 -4 3");
	data.push_back("-4 5 5");
	data.push_back("-5 -1 -4");
	data.push_back("3 -4 -2");
	data.push_back("-4 -5 -1");
	data.push_back("4 1 1");
	data.push_back("5 4 1");
	data.push_back("-3 -1 1");
	data.push_back("3 -2 -1");
	data.push_back("-2 -4 -5");
	data.push_back("4 -5 4");
	data.push_back("1 3 -5");
	data.push_back("-1 5 3");
	data.push_back("5 3 -4");

	Formula formula;
	if (!Parser::TryParseStringToFormula(data, ' ', formula))
	{
		cout << "Cannot parse data to formula" << endl;
		return 0;
	}

	cout << "This is your formula:" << endl;
	cout << formula.ToString() << endl;

	cout << "13. Result: " << endl << formula.GetSimplified().ToString();
	SatProblemSolver sps = SatProblemSolver();
	map<int, bool> literalsMap;
	unordered_set<int> formulaLiterals = formula.GetLiterals();
	bool isSat = sps.Solve3Snf(formula, literalsMap);

	bool a = GetFormulaValue(formula, literalsMap);

	stringstream outputData = Parser::ParseToStringStream(isSat, formulaLiterals, literalsMap);
	//TxtWriter::WriteToFile(argv[2], outputData);
	cout << outputData.str();

	return 0;
}
