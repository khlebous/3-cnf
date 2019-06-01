#include <string>
#include <vector>
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../3-cnf/SatProblemSolver.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(SatProblemSolverTests)
	{
	public:
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

		TEST_METHOD(TestFail1)
		{
			vector<Clause> v =
			{
				Clause({-1}),
				Clause({ 1}),
			};

			SatProblemSolver sps = SatProblemSolver();
			map<int, bool> literalsMap;
			bool isSat = sps.Solve3Snf(Formula(v), literalsMap);

			Assert::AreEqual(false, isSat);
		}

		TEST_METHOD(TestFail2)
		{
			vector<Clause> v =
			{
				Clause({-1, -2, -3}),
				Clause({ 1}),
				Clause({ -1, 2 }),
				Clause({ -2, 3 })
			};

			SatProblemSolver sps = SatProblemSolver();
			map<int, bool> literalsMap;
			bool isSat = sps.Solve3Snf(Formula(v), literalsMap);

			Assert::AreEqual(false, isSat);
		}


		TEST_METHOD(TestFail3)
		{
			vector<Clause> v =
			{
				Clause({1, 2}),
				Clause({-2, 3}),
				Clause({-3, -1}),
				Clause({1, -2, -3}),
				Clause({-1, 2, 3})
			};

			SatProblemSolver sps = SatProblemSolver();
			map<int, bool> literalsMap;
			bool isSat = sps.Solve3Snf(Formula(v), literalsMap);

			Assert::AreEqual(false, isSat);
		}

		TEST_METHOD(TestFail4)
		{
			vector<Clause> v =
			{
				Clause({1}),
				Clause({-1, 2}),
				Clause({-1, -2 ,3}),
				Clause({-3}),
			};

			SatProblemSolver sps = SatProblemSolver();
			map<int, bool> literalsMap;
			bool isSat = sps.Solve3Snf(Formula(v), literalsMap);

			Assert::AreEqual(false, isSat);
		}

		TEST_METHOD(TestFail5)
		{
			vector<Clause> v =
			{
				Clause({1, 2 ,3}),
				Clause({-1, 2 ,3}),
				Clause({1, -2 ,3}),
				Clause({1, 2 ,-3}),
				Clause({-1, -2 ,3}),
				Clause({1, -2 ,-3}),
				Clause({-1, 2 ,-3}),
				Clause({-1, -2 ,-3}),
			};

			SatProblemSolver sps = SatProblemSolver();
			map<int, bool> literalsMap;
			bool isSat = sps.Solve3Snf(Formula(v), literalsMap);

			Assert::AreEqual(false, isSat);
		}


		TEST_METHOD(TestFail6)
		{
			vector<Clause> v =
			{
				Clause({4,-4,-4}),
				Clause({-4, 2 }),
				Clause({-2, -4 }),
				Clause({ -4 }),
				Clause({-4, -2 }),
				Clause({ 4 }),
				Clause({ 4 }),
				Clause({ -4 }),
			};

			SatProblemSolver sps = SatProblemSolver();
			map<int, bool> literalsMap;
			bool isSat = sps.Solve3Snf(Formula(v), literalsMap);

			Assert::AreEqual(false, isSat);
		}

		TEST_METHOD(TestFail7)
		{
			vector<Clause> v =
			{
				Clause({ -1}),
				Clause({ -3}),
				Clause({1,3,2}),
				Clause({-2}),
			};

			SatProblemSolver sps = SatProblemSolver();
			map<int, bool> literalsMap;
			bool isSat = sps.Solve3Snf(Formula(v), literalsMap);

			Assert::AreEqual(false, isSat);
		}
		//--------------------------------------------------------

		TEST_METHOD(TestPass1)
		{
			vector<Clause> v =
			{
				Clause({1,2,3})
			};

			SatProblemSolver sps = SatProblemSolver();
			map<int, bool> literalsMap;
			Formula f = Formula(v);

			bool isSat = sps.Solve3Snf(f, literalsMap);
			bool formulaValue = GetFormulaValue(f, literalsMap);

			Assert::AreEqual(true, isSat);
			Assert::AreEqual(true, formulaValue);
		}

		TEST_METHOD(TestPass2)
		{
			vector<Clause> v =
			{
				Clause({1 ,-1,1}),
				Clause({2 ,1 ,1}),
				Clause({1, 4 ,5})
			};

			SatProblemSolver sps = SatProblemSolver();
			map<int, bool> literalsMap;
			Formula f = Formula(v);

			bool isSat = sps.Solve3Snf(f, literalsMap);
			bool formulaValue = GetFormulaValue(f, literalsMap);

			Assert::AreEqual(true, isSat);
			Assert::AreEqual(true, formulaValue);
		}

		TEST_METHOD(TestPass3)
		{
			vector<Clause> v =
			{
				Clause({1, 2}),
				Clause({-2, 3}),
				Clause({-3,-1}),
				Clause({1,-2,-3})
			};

			SatProblemSolver sps = SatProblemSolver();
			map<int, bool> literalsMap;
			Formula f = Formula(v);

			bool isSat = sps.Solve3Snf(f, literalsMap);
			bool formulaValue = GetFormulaValue(f, literalsMap);

			Assert::AreEqual(true, isSat);
			Assert::AreEqual(true, formulaValue);
		}

		TEST_METHOD(TestPass4)
		{
			vector<Clause> v =
			{
				Clause({1}),
				Clause({-1, 2}),
				Clause({-1, -2 ,3}),
			};

			SatProblemSolver sps = SatProblemSolver();
			map<int, bool> literalsMap;
			Formula f = Formula(v);

			bool isSat = sps.Solve3Snf(f, literalsMap);
			bool formulaValue = GetFormulaValue(f, literalsMap);

			Assert::AreEqual(true, isSat);
			Assert::AreEqual(true, formulaValue);
		}

		TEST_METHOD(TestPass5)
		{
			vector<Clause> v =
			{
				Clause({1, 2 ,3}),
				Clause({-1, 2 ,3}),
				Clause({1, -2 ,3}),
				Clause({1, 2 ,-3}),
				Clause({-1, -2 ,3}),
				Clause({1, -2 ,-3}),
				Clause({-1, 2 ,-3}),
			};

			SatProblemSolver sps = SatProblemSolver();
			map<int, bool> literalsMap;
			Formula f = Formula(v);

			bool isSat = sps.Solve3Snf(f, literalsMap);
			bool formulaValue = GetFormulaValue(f, literalsMap);

			Assert::AreEqual(true, isSat);
			Assert::AreEqual(true, formulaValue);
		}

		TEST_METHOD(TestPass6)
		{
			vector<Clause> v =
			{
				Clause({1,2}),
				Clause({-1 }),
				Clause({-1,2 })
			};

			SatProblemSolver sps = SatProblemSolver();
			map<int, bool> literalsMap;
			Formula f = Formula(v);

			bool isSat = sps.Solve3Snf(f, literalsMap);
			bool formulaValue = GetFormulaValue(f, literalsMap);

			Assert::AreEqual(true, isSat);
			Assert::AreEqual(true, formulaValue);
		}

		TEST_METHOD(TestPass7)
		{
			vector<Clause> v =
			{
				Clause({1,2}),
				Clause({-1 }),
			};

			SatProblemSolver sps = SatProblemSolver();
			map<int, bool> literalsMap;
			Formula f = Formula(v);

			bool isSat = sps.Solve3Snf(f, literalsMap);
			bool formulaValue = GetFormulaValue(f, literalsMap);

			Assert::AreEqual(true, isSat);
			Assert::AreEqual(true, formulaValue);
		}

		TEST_METHOD(TestPass8)
		{
			vector<Clause> v =
			{
				Clause({ -3, 2, -4 }),
				Clause({ -5 ,4, 2 }),
				Clause({ -1 ,1, -4 }),
				Clause({ 4 ,-4, -4 }),
				Clause({ -4 ,2, 3 }),
				Clause({ -2 ,5, -3 }),
				Clause({ -2 ,-4, 3 }),
				Clause({ -4 ,5, 5 }),
				Clause({ -5 ,-1, -4 }),
				Clause({ 3 ,-4, -2 }),
				Clause({ -4 ,-5, -1 }),
				Clause({ 4 ,1, 1 }),
				Clause({ 5 ,4, 1 }),
				Clause({ -3 ,-1, 1 }),
				Clause({ 3 ,-2, -1 }),
				Clause({ -2 ,-4, -5 }),
				Clause({ 4 ,-5, 4 }),
				Clause({ 1 ,3, -5 }),
				Clause({ -1 ,5, 3 }),
				Clause({ 5 ,3, -4 })
			};

			SatProblemSolver sps = SatProblemSolver();
			map<int, bool> literalsMap;
			Formula f = Formula(v);

			bool isSat = sps.Solve3Snf(f, literalsMap);
			bool formulaValue = GetFormulaValue(f, literalsMap);

			Assert::AreEqual(true, isSat);
			Assert::AreEqual(true, formulaValue);
		}
	};
}