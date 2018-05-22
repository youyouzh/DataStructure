#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DataStructure/linked_stack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace linked_stack_test
{
	TEST_CLASS(LinkedStackTest)
	{
	public:
		typedef LinkedStack<int> UList;

		TEST_METHOD(empty)
		{
			UList list(10);
			Assert::IsTrue(list.empty());
		}

		TEST_METHOD(push)
		{
			UList list(5);
			list.push(3);
			Assert::AreEqual(1, list.size());
			Assert::IsFalse(list.empty());

			list.push(6);
			Assert::AreEqual(2, list.size());
		}

		TEST_METHOD(top)
		{
			UList list(2);

			// stack empty
			auto func = [&list]() { list.top(); };
			Assert::ExpectException<StackEmptyException>(func);

			// general insert
			list.push(4);
			Assert::AreEqual(1, list.size());
			Assert::AreEqual(4, list.top());

			// gereral insert
			list.push(10);
			Assert::AreEqual(2, list.size());
			Assert::AreEqual(10, list.top());

			// space out insert
			list.push(15);
			Assert::AreEqual(3, list.size());
			Assert::AreEqual(15, list.top());
		}


		TEST_METHOD(pop)
		{
			UList list(2);

			// stack empty
			auto func = [&list]() { list.pop(); };
			Assert::ExpectException<StackEmptyException>(func);

			list.push(10);
			Assert::AreEqual(1, list.size());
			Assert::AreEqual(10, list.top());

			list.pop();
			Assert::IsTrue(list.empty());

			list.push(3);
			list.push(5);
			list.push(10);

			Assert::AreEqual(3, list.size());
			list.pop();
			Assert::AreEqual(5, list.top());
		}
	};
}