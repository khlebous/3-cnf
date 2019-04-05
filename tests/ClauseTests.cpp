#include <string>
#include <vector>
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../3-cnf/Clause.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(ClauseTests)
	{
	public:
		TEST_METHOD(SubstituteTrueWhenOneLiteralIsTheSame)
		{
			vector<int> v = { 1, 2, 3 };
			Clause clause(v);
			Clause new_clause;
			State state = clause.SubstituteTrue(1, new_clause);

			Assert::AreEqual(1, static_cast<int>(state));
		}

		TEST_METHOD(SubstituteTrueWhenOneLiteralIsNegated)
		{
			vector<int> v = { -1, 2, -3 };
			Clause clause(v);
			Clause new_clause;
			State state = clause.SubstituteTrue(1, new_clause);

			Assert::AreEqual(0, static_cast<int>(state));
			Assert::AreEqual((size_t)2, new_clause.Size());
			Assert::AreEqual(2, new_clause[0]);
			Assert::AreEqual(-3, new_clause[1]);
		}

		TEST_METHOD(SubstituteTrueWhenThereIsOnlyOneNegatedLiteral)
		{
			vector<int> v = { -1 };
			Clause clause(v);
			Clause new_clause;
			State state = clause.SubstituteTrue(1, new_clause);

			Assert::AreEqual(-1, static_cast<int>(state));
		}
	};
}
