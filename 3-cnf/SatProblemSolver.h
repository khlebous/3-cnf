#pragma once
#include <vector>
#include <map>
#include "Formula.h"

class SatProblemSolver
{
private:
	void InsertValueToMap(map<int, bool> &m, int value)
	{
		if (value > 0)
			m[value] = true;
		else
			m[-value] = false;
	}

	bool Solve3SnfRec(Formula const& formula, map<int, bool> & literalsMap)
	{
		if (formula.ClausesCount() == 0)
			return false;

		Clause clause = formula[0];
		
		Formula f_x;
		InsertValueToMap(literalsMap, clause[0]);
		if (formula.SubstituteTrue(clause[0], f_x))
			return true;

		if (Solve3SnfRec(f_x, literalsMap))
			return true;

		if (clause.Size() == 1)
			return false;

		literalsMap.erase(clause[0]);
		Formula f_negx;
		InsertValueToMap(literalsMap, -clause[0]);
		formula.SubstituteTrue(-clause[0], f_negx);
		Formula f_negx_y;
		InsertValueToMap(literalsMap, clause[1]);
		if (f_negx.SubstituteTrue(clause[1], f_negx_y))
			return true;

		if (Solve3SnfRec(f_negx_y, literalsMap))
			return true;
		
		if (clause.Size() == 2)
			return false;
		
		literalsMap.erase(clause[1]);
		Formula f_negx_neg_y;
		InsertValueToMap(literalsMap, -clause[1]);
		f_negx.SubstituteTrue(-clause[1], f_negx_neg_y);
		Formula f_negx_neg_y_z;
		InsertValueToMap(literalsMap, clause[2]);
		InsertValueToMap(literalsMap, clause[1]);
		if (f_negx_neg_y.SubstituteTrue(clause[2], f_negx_neg_y_z))
			return true;
		
		return (Solve3SnfRec(f_negx_neg_y_z, literalsMap));
	}

public:
	bool Solve3Snf(Formula const& f, map<int, bool> & m)
	{
		return Solve3SnfRec(f, m);
	}
};

