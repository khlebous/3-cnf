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
			State state = formula.SubstituteTrue(1, new_formula);

			Assert::AreEqual(static_cast<int>(ALWAYS), static_cast<int>(state));
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
			State state = formula.SubstituteTrue(1, new_formula);

			Assert::AreEqual(static_cast<int>(NEVER), static_cast<int>(state));
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
			State state = formula.SubstituteTrue(-1, new_formula);

			Assert::AreEqual(static_cast<int>(UNKNOWN), static_cast<int>(state));
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
			State state = formula.SubstituteTrue(4, new_formula);

			Assert::AreEqual(static_cast<int>(UNKNOWN), static_cast<int>(state));
			Assert::AreEqual((size_t)2, new_formula.ClausesCount());
			Assert::AreEqual(3, new_formula[0][0]);
			Assert::AreEqual(1, new_formula[1][0]);
			Assert::AreEqual(-2, new_formula[1][1]);
			Assert::AreEqual(3, new_formula[1][2]);
		}
	};
}
