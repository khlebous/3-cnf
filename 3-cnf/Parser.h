#pragma once
#include <map>
#include "Formula.h"
#include "Clause.h"
#include <sstream>
#include <map>
using namespace std;

class Parser
{
private:
	static bool CanCreateClause(const vector<int>& v)
	{
		return v.size() > 0 && v.size() < 4;
	}

public:
	static stringstream ParseToStringStream(bool isSat, unordered_set<int> formulaLiterals, const map<int, bool>& literalsMap)
	{
		stringstream data;

		data << boolalpha << "Is sat? " << (isSat ? "yes" : "no") << endl;

		if (!isSat)
			return data;

		for (auto it = literalsMap.begin(); it != literalsMap.end(); it++)
		{
			formulaLiterals.erase(it->first);
			data << it->first << "-" << it->second << std::endl;
		}
		if (formulaLiterals.size() > 0)
		{
			data << "These literals can be any: ";
			for (auto it1 = formulaLiterals.begin(); it1 != formulaLiterals.end(); it1++)
				data << (*it1) << " ";
			data << endl;
		}

		return data;
	}

	static bool TryParseStringToInt(string s, int& i)
	{
		size_t idx = 0;

		bool negate = (s[idx] == '-');
		if (s[idx] == '+' || s[idx] == '-')
			idx++;

		if (s[idx] == '\0')
			return false;

		int result = 0;
		for (size_t i = idx; i < s.size(); i++)
		{
			if (s[i] >= '0' && s[i] <= '9')
				result = result * 10 + (s[i] - '0');
			else
				return false;
		}
		i = negate ? -result : result;

		return true;
	}

	static bool TryParseStringToClause(string line, char delimeter, Clause & clause)
	{
		if (line == "")
			return false;

		size_t startIdx = 0;
		vector<int> v;

		size_t i = 0;
		for (; i < line.size(); i++)
		{
			if (line[i] == delimeter)
			{
				if (startIdx == i)
				{
					startIdx++;
					continue;
				}
				else
				{
					string toParse = line.substr(startIdx, i - startIdx);
					int parsed;
					if (!TryParseStringToInt(toParse, parsed))
						return false;
					v.push_back(parsed);
					startIdx = i + 1;
				}
			}
		}
		if (startIdx < i)
		{
			string toParse = line.substr(startIdx, i - startIdx);
			int parsed;
			if (!TryParseStringToInt(toParse, parsed))
				return false;
			v.push_back(parsed);
		}

		if (!CanCreateClause(v))
			return false;

		clause = Clause(v);

		return true;
	}

	static bool TryParseStringToFormula(vector<string>& const data, char delemiter,
		Formula& formula)
	{
		if (data.size() == 0)
			return false;

		vector<Clause> clauses;
		for (size_t i = 0; i < data.size(); i++)
		{
			Clause clause;
			if (!TryParseStringToClause(data[i], delemiter, clause))
				return false;

			clauses.push_back(clause);
		}
		formula = Formula(clauses);

		return true;
	}
};

