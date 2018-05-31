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
			// TODO: 在此输入测试代码
			int input[] = { 2, 6, 3, 10, 5 };
			int expect[] = { 2, 3, 5, 6, 10 };
			int actual[5] = { 0 };
			int n = 5;
			selectionSort(input, n);
			for (int i = 0; i < n; i++) 
			{
				Assert::AreEqual(expect[i], input[i]);
			}
		}

	};
}