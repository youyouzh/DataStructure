#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DataStructure/max_heap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace max_heap_test
{
	TEST_CLASS(MaxHeapTest)
	{
	public:
		typedef MaxHeap<int> UHeap;

		TEST_METHOD(empty)
		{
			UHeap heap(10);
			Assert::AreEqual(true, heap.empty());
		}

		TEST_METHOD(size)
		{
			UHeap heap(10);
			Assert::AreEqual(0, heap.size());

			heap.push(10);
			Assert::AreEqual(1, heap.size());

			heap.pop();
			Assert::AreEqual(0, heap.size());
		}

		TEST_METHOD(push_pop_top)
		{
			UHeap heap(10);
			heap.push(5);
			Assert::AreEqual(1, heap.size());
			Assert::AreEqual(5, heap.top());

			heap.push(6);
			Assert::AreEqual(6, heap.top());
			heap.push(1);
			Assert::AreEqual(6, heap.top());

			heap.pop();
			Assert::AreEqual(5, heap.top());
		}

		TEST_METHOD(initialize)
		{
			UHeap heap(11);
			int init[11] = { -1, 20, 12, 35, 15, 10, 80, 30, 17, 2, 1 };
			heap.initialize(init, 11);
			auto actual = heap.get_heap();

			int excepted[] = { -1, 80, 17, 35, 15, 10, 20, 30, 12, 2, 1 };
			for (auto i = 1; i < 11; i++)
			{
				Assert::AreEqual(excepted[i], actual[i]);
			}
		}
	};
}