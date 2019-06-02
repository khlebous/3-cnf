#pragma once
#include <vector>
#include <unordered_set>
#include <sstream>
#include "Clause.h"
using namespace std;

class Formula
{
private:
	vector<Clause> clauses;

public:
	Formula() {}
	Formula(vector<Clause>& const _clauses)
	{
		clauses.clear();
		for (size_t i = 0; i < _clauses.size(); i++)
			clauses.push_back(_clauses[i]);
	}
	Formula(const Formula & f)
	{
		clauses.clear();
		for (size_t i = 0; i < f.clauses.size(); i++)
			clauses.push_back(f.clauses[i]);
	}
	~Formula()
	{
		clauses.clear();
	}

	const Clause& operator[](size_t nr) const { return clauses[nr]; }
	Formula& operator=(const Formula& f)
	{
		if (this != &f)
		{
			clauses.clear();

			for (size_t i = 0; i < f.clauses.size(); i++)
				clauses.push_back(f.clauses[i]);
		}

		return *this;
	}

	size_t ClausesCount() const { return clauses.size(); }
	string ToString() const
	{
		std::stringstream ss;
		if (clauses.size() == 0)
		{
			ss << "Formula is empty";
			return ss.str();
		}

		for (size_t i = 0; i < ClausesCount(); i++)
		{
			ss << "( " << clauses[i].ToString() << " )";
			if (i != ClausesCount() - 1)
				ss << " ^ ";
		}

		return ss.str();
	}
	unordered_set<int> GetLiterals() const
	{
		unordered_set<int> literals;
		for (size_t i = 0; i < clauses.size(); i++)
			for (size_t j = 0; j < clauses[i].Size(); j++)
				literals.insert(abs(clauses[i][j]));

		return literals;
	}
	State SubstituteTrue(int nr, Formula& f) const
	{
		vector<Clause> v;

		for (size_t i = 0; i < ClausesCount(); i++)
		{
			Clause c;
			switch (clauses[i].SubstituteTrue(nr, c))
			{
			case State::NEVER:
				return NEVER;
				break;
			case State::UNKNOWN:
				v.push_back(c);
				break;
			default:
				break;
			}
		}

		if (v.size() == 0)
			return ALWAYS;

		f = Formula(v);

		return UNKNOWN;
	}
	Formula GetSimplified() const
	{
		vector<Clause> simplifedClauses;
		for (size_t i = 0; i < ClausesCount(); i++)
		{
			Clause c = clauses[i];

			if (c.Size() > 1 && c[1] == -c[0])
				continue;

			if (c.Size() > 2 && (c[2] == -c[1] || c[2] == -c[0]))
				continue;

			vector<int> v;

			v.push_back(c[0]);

			if (c.Size() > 1 && c[1] != c[0])
				v.push_back(c[1]);

			if (c.Size() > 2 && c[2] != c[1] && c[2] != c[0])
				v.push_back(c[2]);

			simplifedClauses.push_back(Clause(v));
		}

		return Formula(simplifedClauses);
	}
};
