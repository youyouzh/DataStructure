#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DataStructure/array_queue.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace array_queue_test
{
	TEST_CLASS(ArrayQueueTest)
	{
	public:
		typedef ArrayQueue<int> UQueue;

		TEST_METHOD(empty)
		{
			UQueue queue(10);
			Assert::IsTrue(queue.empty());
		}

		TEST_METHOD(size)
		{
			UQueue queue(2);
			Assert::AreEqual(0, queue.size());

			queue.push(3);
			Assert::AreEqual(1, queue.size());
		}

		TEST_METHOD(front)
		{
			UQueue queue(2);

			auto func = [&queue]() { queue.front(); };
			Assert::ExpectException<QueueEmptyException>(func);

			queue.push(3);
			Assert::AreEqual(3, queue.front());
			queue.push(6);
			Assert::AreEqual(3, queue.front());
		}


		TEST_METHOD(back)
		{
			UQueue queue(2);

			auto func = [&queue]() { queue.back(); };
			Assert::ExpectException<QueueEmptyException>(func);

			queue.push(3);
			Assert::AreEqual(3, queue.back());
			queue.push(6);
			Assert::AreEqual(6, queue.back());
		}

		TEST_METHOD(push)
		{
			UQueue queue(2);
			queue.push(3);
			queue.push(4);
			Assert::AreEqual(2, queue.size());
			Assert::AreEqual(3, queue.front());
			Assert::AreEqual(4, queue.back());

			queue.push(5);
			Assert::AreEqual(3, queue.front());
			Assert::AreEqual(5, queue.back());
			Assert::AreEqual(3, queue.size());
		}

		TEST_METHOD(pop)
		{
			UQueue queue(2);
			auto func = [&queue]() { queue.pop(); };
			Assert::ExpectException<QueueEmptyException>(func);

			queue.push(2);
			queue.push(3);
			queue.push(4);
			queue.pop();

			Assert::AreEqual(3, queue.front());
			Assert::AreEqual(4, queue.back());
			Assert::AreEqual(2, queue.size());

			queue.pop();
			queue.pop();
			Assert::AreEqual(0, queue.size());
		}
	};
}