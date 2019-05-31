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

		//--------------------------------------------------------

		TEST_METHOD(TestPass1)
		{
			vector<Clause> v =
			{
				Clause({1,2,3})
			};

			SatProblemSolver sps = SatProblemSolver();
			map<int, bool> literalsMap;
			bool isSat = sps.Solve3Snf(Formula(v), literalsMap);

			Assert::AreEqual(true, isSat);
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
			bool isSat = sps.Solve3Snf(Formula(v), literalsMap);

			Assert::AreEqual(true, isSat);
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
			bool isSat = sps.Solve3Snf(Formula(v), literalsMap);

			Assert::AreEqual(true, isSat);
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
			bool isSat = sps.Solve3Snf(Formula(v), literalsMap);

			Assert::AreEqual(true, isSat);
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
			bool isSat = sps.Solve3Snf(Formula(v), literalsMap);

			Assert::AreEqual(true, isSat);
		}
	};
}