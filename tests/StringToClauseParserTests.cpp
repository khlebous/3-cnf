#include <string>
#include <vector>
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../3-cnf/Parser.h"
#include "../3-cnf/Clause.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(StringToClauseParserTests)
	{
	public:
		TEST_METHOD(TryParseEmptyStringToClause)
		{
			Clause clause;
			bool canParse = Parser::TryParseStringToClause("", ' ', clause);

			Assert::AreEqual(false, canParse);
		}

		TEST_METHOD(TryParseStringWithOneLiteralToClause)
		{
		Clause clause;
		bool canParse = Parser::TryParseStringToClause("2", ' ', clause);

		Assert::AreEqual(true, canParse);
		Assert::AreEqual((size_t)1, clause.Size());
		Assert::AreEqual(2, clause[0]);
		}

		TEST_METHOD(TryParseStringWithOneSignedLiteralAndSpacesToClause)
		{
			Clause clause;
			bool canParse = Parser::TryParseStringToClause("  +2 ", ' ', clause);

			Assert::AreEqual(true, canParse);
			Assert::AreEqual((size_t)1, clause.Size());
			Assert::AreEqual(2, clause[0]);
		}

		TEST_METHOD(TryParseStringWithThreeLiteralsAndSpacesToClause)
		{
			Clause clause;
			bool canParse = Parser::TryParseStringToClause("  +2 1  -3", ' ', clause);

			Assert::AreEqual(true, canParse);
			Assert::AreEqual((size_t)3, clause.Size());
			Assert::AreEqual(2, clause[0]);
			Assert::AreEqual(1, clause[1]);
			Assert::AreEqual(-3, clause[2]);
		}

		TEST_METHOD(TryParseIncorrectStringToClause)
		{
			Clause clause;
			bool canParse = Parser::TryParseStringToClause("1 2 +-3", ' ', clause);

			Assert::AreEqual(false, canParse);
		}

		TEST_METHOD(TryParseStringWithFourIntsToClause)
		{
			Clause clause;
			bool canParse = Parser::TryParseStringToClause("1 2 3 4", ' ', clause);

			Assert::AreEqual(false, canParse);
		}
	};
}
