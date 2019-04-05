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
	TEST_CLASS(StringToFormulaParserTests)
	{
	public:
		TEST_METHOD(TryParseEmptyStringToFormula)
		{
			Formula formula;
			vector<string> v;
			bool canParse = Parser::TryParseStringToFormula(v, ' ', formula);

			Assert::AreEqual(false, canParse);
		}

		TEST_METHOD(TryParseVectorOfStringsToFormula)
		{
			Formula formula;
			vector<string> v;
			v.push_back("1 2 3");
			v.push_back("+1 -2 3");
			v.push_back("1 ");
			v.push_back("2 3");
			bool canParse = Parser::TryParseStringToFormula(v, ' ', formula);

			Assert::AreEqual(true, canParse);
			Assert::AreEqual((size_t)4, formula.ClausesCount());
		}

		TEST_METHOD(TryParseIncorrectVectorOfStringsToFormula)
		{
			Formula formula;
			vector<string> v;
			v.push_back("1 2 3 4");
			bool canParse = Parser::TryParseStringToFormula(v, ' ', formula);

			Assert::AreEqual(false, canParse);
		}

		TEST_METHOD(TryParseIncorrectVectorOfStringsToFormula2)
		{
			Formula formula;
			vector<string> v;
			v.push_back("1 -2 3");
			v.push_back("1 +-2 3");
			bool canParse = Parser::TryParseStringToFormula(v, ' ', formula);

			Assert::AreEqual(false, canParse);
		}

		TEST_METHOD(TryParseIncorrectVectorOfStringsToFormula3)
		{
			Formula formula;
			vector<string> v;
			v.push_back("1 -2 3");
			v.push_back("1 $ 3");
			bool canParse = Parser::TryParseStringToFormula(v, ' ', formula);

			Assert::AreEqual(false, canParse);
		}
	};
}
