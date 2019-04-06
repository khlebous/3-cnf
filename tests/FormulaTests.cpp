#include <string>
#include <vector>
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../3-cnf/Formula.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(FormulaSubstitutionTrueTests)
	{
	public:
		TEST_METHOD(SubstituteTrueWhenOneClauseWithOneSameLiteral)
		{
			vector<Clause> v =
			{
				Clause({ 1, 2, 3 })
			};
			Formula formula(v);

			Formula new_formula;
			bool state = formula.SubstituteTrue(1, new_formula);

			Assert::AreEqual(true, state);
		}

		TEST_METHOD(SubstituteTrueWhenOneClauseHasOneSameNegateLiteral)
		{
			vector<Clause> v =
			{
				Clause({ -1 }),
				Clause({ 1, 2 ,3 }),
			};
			Formula formula(v);

			Formula new_formula;
			bool state = formula.SubstituteTrue(1, new_formula);

			Assert::AreEqual(false, state);
		}

		TEST_METHOD(SubstituteTrueWhichSimplifyFormula)
		{
			vector<Clause> v =
			{
				Clause({ -1 }),
				Clause({ 1, 2 , -3 }),
			};
			Formula formula(v);

			Formula new_formula;
			bool state = formula.SubstituteTrue(-1, new_formula);

			Assert::AreEqual(false, state);
			Assert::AreEqual((size_t)1, new_formula.ClausesCount());
			Assert::AreEqual(2, new_formula[0][0]);
			Assert::AreEqual(-3, new_formula[0][1]);
		}

		TEST_METHOD(SubstituteTrueWhichDoNotChangeFormula)
		{
			vector<Clause> v =
			{
				Clause({ 3 }),
				Clause({ 1, -2, 3 }),
			};
			Formula formula(v);

			Formula new_formula;
			bool state = formula.SubstituteTrue(4, new_formula);

			Assert::AreEqual(false, state);
			Assert::AreEqual((size_t)2, new_formula.ClausesCount());
			Assert::AreEqual(3, new_formula[0][0]);
			Assert::AreEqual(1, new_formula[1][0]);
			Assert::AreEqual(-2, new_formula[1][1]);
			Assert::AreEqual(3, new_formula[1][2]);
		}
	};
}
