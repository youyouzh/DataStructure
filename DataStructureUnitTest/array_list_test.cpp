#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DataStructure/array_list.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace linear_list_test
{
	TEST_CLASS(ArrayListTest)
	{
	public:
		typedef ArrayList<int> UList;

		TEST_METHOD(empty)
		{
			UList list(10);
			Assert::AreEqual(true, list.empty());
		}

		TEST_METHOD(get)
		{
			UList list(5);
			auto func = [&list]() {list.get(2); };
			Assert::ExpectException<IllegalIndexException>(func);

			list.insert(0, 5);
			Assert::AreEqual(5, list.get(0));
		}

		TEST_METHOD(insert)
		{
			UList list(3);
			// general insert
			list.insert(0, 4);
			Assert::AreEqual(4, list.get(0));
			Assert::AreEqual(1, list.size());

			// illegal insert
			auto func = [&list](){ list.insert(2, 2); };
			Assert::ExpectException<IllegalIndexException>(func);

			// back insert
			list.insert(1, 12);
			Assert::AreEqual(12, list.get(1));
			Assert::AreEqual(2, list.size());

			// before insert
			list.insert(0, 1);
			Assert::AreEqual(1, list.get(0));
			Assert::AreEqual(3, list.size());

			// array length out insert, double capacity
			list.insert(3, 3);
			Assert::AreEqual(3, list.get(3));
			Assert::AreEqual(6, list.capacity());
			Assert::AreEqual(4, list.size());

		}


		TEST_METHOD(erase)
		{
			UList list(4);
			list.insert(0, 0);
			list.insert(1, 1);
			list.insert(2, 2);
			list.insert(3, 3);

			list.erase(0);
			Assert::AreEqual(1, list.get(0));
			Assert::AreEqual(3, list.size());

			auto func2 = [&list]() { list.erase(4); };
			Assert::ExpectException<IllegalIndexException>(func2);
		}

		TEST_METHOD(index_of)
		{
			UList list(10);
			list.insert(0, 0);
			list.insert(1, 1);
			list.insert(2, 2);
			list.insert(3, 3);
			list.insert(4, 4);
			list.insert(5, 5);

			Assert::AreEqual(2, list.index_of(2));
			Assert::AreEqual(-1, list.index_of(10));
		}
	};
}