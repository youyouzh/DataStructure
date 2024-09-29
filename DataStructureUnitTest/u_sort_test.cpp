#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DataStructure/u_sort.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataStructureUnitTest
{		
	TEST_CLASS(USortUnitTest)
	{
	public:

		TEST_METHOD(selectionSortTest)
		{
			int input[] = { 2, 6, 3, 10, 5 };
			int expect[] = { 2, 3, 5, 6, 10 };
			int n = 5;
			selectionSort(input, n);
			for (int i = 0; i < n; i++) 
			{
				Assert::AreEqual(expect[i], input[i]);
			}
		}

		TEST_METHOD(bubbleSortTest)
		{
			int input[] = { 2, 6, 3, 10, 5 };
			int expect[] = { 2, 3, 5, 6, 10 };
			int n = 5;
			bubbleSort(input, n);
			for (int i = 0; i < n; i++)
			{
				Assert::AreEqual(expect[i], input[i]);
			}
		}

		TEST_METHOD(QSortTest)
		{
			int input[] = { 12, 2, 6, 3, 10, 5 };
			int expect[] = { 2, 3, 5, 6, 10, 12 };
			int n = sizeof(input) / sizeof(input[0]);
			QSort(input, n - 1);
			for (int i = 0; i < n; i++)
			{
				Assert::AreEqual(expect[i], input[i]);
			}
		}

	};
}