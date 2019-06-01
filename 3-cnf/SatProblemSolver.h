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
		//cout << "1. TRY SOLVE FORMULA: " << formula.ToString() << endl;
		if (formula.ClausesCount() == 0)
		{
			//cout << "RETURN FALSE" << endl;
			return false;
		}

		Clause clause = formula[0];

		int c[3];
		for (size_t i = 0; i < clause.Size(); i++)
			c[i] = clause[i];

		Formula f_x;
		//cout << "2. Substitute " << to_string(clause[0]) << " as true to formula ";
		//cout << formula.ToString() << endl;
		InsertValueToMap(literalsMap, clause[0]);
		//cout << "Current map: ";
		//for (auto& x : literalsMap) //cout << x.first << "-" << boolalpha << x.second << " ";
		//cout << endl;

		State state = formula.SubstituteTrue(clause[0], f_x);
		if (state == State::ALWAYS)
			return true;

		//cout << "3. Result: " << f_x.ToString() << endl;
		//cout << endl;
		//cout << "4. Try solve formula f_x: " << f_x.ToString() << endl;
		//cout << endl;
		if (state == State::UNKNOWN)
			if (Solve3SnfRec(f_x, literalsMap))
				return true;

		literalsMap.erase(clause[0]);
		if (clause.Size() == 1)
			return false;

		//cout << "NOT OK, lets try -x" << endl;
		Formula f_negx;
		InsertValueToMap(literalsMap, -clause[0]);


		state = formula.SubstituteTrue(-clause[0], f_negx);

		if (state == State::ALWAYS)
			return true;

		if (state == State::NEVER) {
			literalsMap.erase(-clause[0]);
			return false;
		}

		//cout << "5. Substitute " << to_string(-clause[0]) << " as true to formula ";
		//cout << formula.ToString() << endl;
		//cout << "6. Result: " << f_negx.ToString() << endl;

		Formula f_negx_y;
		InsertValueToMap(literalsMap, clause[1]);
		//cout << "Current map: ";
		//for (auto& x : literalsMap) //cout << x.first << "-" << boolalpha << x.second << " ";
		//cout << endl;
		//cout << "7. Substitute " << to_string(clause[1]) << " as true to formula ";
		//cout << f_negx.ToString() << endl;

		state = f_negx.SubstituteTrue(clause[1], f_negx_y);
		if (state == State::ALWAYS)
			return true;


		//cout << "8. Result: " << f_negx_y.ToString() << endl;

		//cout << "9. Try solve formula f_negx_y: " << f_negx_y.ToString() << endl;
		//cout << endl;

		if (state == State::UNKNOWN)
			if (Solve3SnfRec(f_negx_y, literalsMap))
				return true;

		literalsMap.erase(clause[1]);

		if (clause.Size() == 2)
			return false;

		//cout << "NOT OK, lets try -x and -y" << endl;

		//cout << "10. Substitute " << to_string(-clause[1]) << " as true to formula ";
		//cout << f_negx.ToString() << endl;

		Formula f_negx_neg_y;
		InsertValueToMap(literalsMap, -clause[1]);
		state = f_negx.SubstituteTrue(-clause[1], f_negx_neg_y);

		if (state == State::ALWAYS)
			return true;

		if (state == State::NEVER) {
			literalsMap.erase(-clause[1]);
			return false;
		}
		//cout << "11. Result: " << f_negx_neg_y.ToString();

		Formula f_negx_neg_y_z;
		InsertValueToMap(literalsMap, clause[2]);
		//InsertValueToMap(literalsMap, clause[1]);

		//cout << "Current map: ";
		//for (auto& x : literalsMap) //cout << x.first << "-" << boolalpha << x.second << " ";
		//cout << endl;
		//cout << "12. Substitute " << to_string(clause[2]) << " as true to formula ";
		//cout << f_negx_neg_y_z.ToString() << endl;


		state = f_negx_neg_y.SubstituteTrue(clause[2], f_negx_neg_y_z);

		if (state == State::ALWAYS)
			return true;

		if (state == State::NEVER) {
			literalsMap.erase(-clause[2]);
			return false;
		}

		//cout << "13. Result: " << f_negx_neg_y_z.ToString();
		//cout << "14. Try solve formula f_negx_neg_y_z: " << f_negx_neg_y_z.ToString() << endl;

		return (Solve3SnfRec(f_negx_neg_y_z, literalsMap));
	}

public:
	bool Solve3Snf(Formula const& f, map<int, bool> & m)
	{
		return Solve3SnfRec(f.GetSimplified(), m);
	}
};

