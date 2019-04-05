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
	TEST_CLASS(StringToIntParserTests)
	{
	public:
		TEST_METHOD(TryParseEmptyStringToInt)
		{
			int value;
			bool canParse = Parser::TryParseStringToInt("", value);

			Assert::AreEqual(false, canParse);
		}

		TEST_METHOD(TryParseStringToInt)
		{
			int value;
			bool canParse = Parser::TryParseStringToInt("3", value);

			Assert::AreEqual(true, canParse);
			Assert::AreEqual(3, value);
		}

		TEST_METHOD(TryParseStringWithThreeDigitsToInt)
		{
			int value;
			bool canParse = Parser::TryParseStringToInt("321", value);

			Assert::AreEqual(true, canParse);
			Assert::AreEqual(321, value);
		}

		TEST_METHOD(TryParseStringWithPlusSignToInt)
		{
			int value;
			bool canParse = Parser::TryParseStringToInt("+1", value);

			Assert::AreEqual(true, canParse);
			Assert::AreEqual(1, value);
		}

		TEST_METHOD(TryParseStringWithPlusSignAndThreeDigitsToInt)
		{
			int value;
			bool canParse = Parser::TryParseStringToInt("+123", value);

			Assert::AreEqual(true, canParse);
			Assert::AreEqual(123, value);
		}

		TEST_METHOD(TryParseStringWithMinusSignToInt)
		{
			int value;
			bool canParse = Parser::TryParseStringToInt("-12", value);

			Assert::AreEqual(true, canParse);
			Assert::AreEqual(-12, value);
		}

		TEST_METHOD(TryParseIncorrectStringToInt)
		{
			int value;
			bool canParse = Parser::TryParseStringToInt("+-12", value);

			Assert::AreEqual(false, canParse);
		}

		TEST_METHOD(TryParseIncorrectStringToInt2)
		{
			int value;
			bool canParse = Parser::TryParseStringToInt("12 1", value);

			Assert::AreEqual(false, canParse);
		}
	};
}