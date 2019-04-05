#pragma once
#include <vector>
#include "Clause.h"
#include <sstream>
using namespace std;

class Formula
{
	vector<Clause> clauses;

public:
	Formula() {}
	Formula(vector<Clause>& const _clauses)
	{
		clauses.clear();
		for (auto const &c : _clauses)
			clauses.push_back(c);
	}
	Formula(const Formula & f)
	{
		clauses.clear();
		for (auto const &c : f.clauses)
			clauses.push_back(c);
	}
	~Formula()
	{
		clauses.clear();
	}

	const Clause & operator[](size_t nr) const { return clauses[nr]; }
	Formula& operator=(const Formula& f)
	{
		if (this != &f)
		{
			clauses.clear();

			for (auto const &c : f.clauses)
				clauses.push_back(c);
		}
		
		return *this;
	}
	
	size_t GetClausesCount() const { return clauses.size(); }
	string ToString() const
	{
		std::stringstream ss;

		for (size_t i = 0; i < GetClausesCount(); i++)
			{
			ss << "( " << clauses[i].ToString() << " )";
				if (i != GetClausesCount() -1)
					ss << " ^ ";
			}

		return ss.str();
	}
};
