#include <string>
#include <vector>
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../3-cnf/TxtReader.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{		
	TEST_CLASS(TxtReaderTests)
	{
	public:
		TEST_METHOD(ReturnEmptyVectorIfFileDoNotExist)
		{
			TxtReader txtReader = TxtReader();
			vector<string> data = txtReader.ReadFile(
				"..\\tests\\TxtReaderTestFiles\\fileDoNotExist.txt");

			Assert::AreEqual((size_t)0, data.size());
		}

		TEST_METHOD(ReturnEmptyVectorIfFileIsEmpty)
		{
			TxtReader txtReader = TxtReader();
			vector<string> data = txtReader.ReadFile(
				"..\\tests\\TxtReaderTestFiles\\emptyFile.txt");

			Assert::AreEqual((size_t)0, data.size());
		}

		TEST_METHOD(ReturnVectorWithOneElementWhenFileHasOneLine)
		{
			TxtReader txtReader = TxtReader();
			vector<string> data = txtReader.ReadFile(
				"..\\tests\\TxtReaderTestFiles\\oneLineFile.txt");

			Assert::AreEqual((size_t)1, data.size());
		}

		TEST_METHOD(ReturnVectorWithThreeElementsWhenFileHasThreeLines)
		{
			TxtReader txtReader = TxtReader();
			vector<string> data = txtReader.ReadFile(
				"..\\tests\\TxtReaderTestFiles\\threeLinesFile.txt");

			Assert::AreEqual((size_t)3, data.size());
		}
	};
}