#pragma once
#include <vector>
#include "Formula.h"

class SatProblemSolver
{
private:
	bool Solve3SnfRec(Formula const& f)
	{
		cout << "1. TRY SOLVE FORMULA: " << f.ToString() << endl;
		if (f.ClausesCount() == 0)
		{
			cout << "RETURN FALSE" << endl;
			return false;
		}

		Clause c = f[0];
		
		Formula f_x;
		cout << "2. Substitute " << to_string(c[0]) << " as true to formula ";
		cout << f.ToString() << endl;
		switch (f.SubstituteTrue(c[0], f_x))
		{
		case State::NEVER:
			break;
		case State::ALWAYS:
			return true;
			break;
		default:
			break;
		}
		cout << "3. Result: " << f_x.ToString() << endl;
		cout << endl;
		
		cout << "4. Try solve formula f_x: " << f_x.ToString() << endl;
		cout << endl;
		if (Solve3SnfRec(f_x))
			return true;
		if (c.Size() == 1)
			return false;

		cout << "NOT OK, lets try -x" << endl;
		Formula f_negx;
		f.SubstituteTrue(-c[0], f_negx);
		cout << "5. Substitute " << to_string(-c[0]) << " as true to formula ";
		cout << f.ToString() << endl;
		cout << "6. Result: " << f_negx.ToString() << endl;

		Formula f_negx_y;
		cout << "7. Substitute " << to_string(c[1]) << " as true to formula ";
		cout << f_negx.ToString() << endl;
		switch (f_negx.SubstituteTrue(c[1], f_negx_y))
		{
		case State::NEVER:
			break;
		case State::ALWAYS:
			return true;
			break;
		default:
			break;
		}
		cout << "8. Result: " << f_negx_y.ToString() << endl;

		cout << "9. Try solve formula f_negx_y: " << f_negx_y.ToString() << endl;
		cout << endl;
		if (Solve3SnfRec(f_negx_y))
			return true;
		if (c.Size() == 2)
			return false;

		cout << "NOT OK, lets try -x and -y" << endl;

		cout << "10. Substitute " << to_string(-c[1]) << " as true to formula ";
		cout << f_negx.ToString() << endl;
		Formula f_negx_neg_y;
		f_negx.SubstituteTrue(-c[1], f_negx_neg_y);
		cout << "11. Result: " << f_negx_neg_y.ToString();

		Formula f_negx_neg_y_z;
		cout << "12. Substitute " << to_string(c[2]) << " as true to formula ";
		cout << f_negx_neg_y_z.ToString() << endl;
		switch (f_negx_neg_y.SubstituteTrue(c[2], f_negx_neg_y_z))
		{
		case State::NEVER:
			break;
		case State::ALWAYS:
			return true;
			break;
		default:
			break;
		}
		cout << "13. Result: " << f_negx_neg_y_z.ToString();

		cout << "14. Try solve formula f_negx_neg_y_z: " << f_negx_neg_y_z.ToString() << endl;
		return (Solve3SnfRec(f_negx_neg_y_z));
	}

public:
	bool Solve3Snf(Formula const& f, vector<bool> & v)
	{
		return Solve3SnfRec(f);
	}
};

