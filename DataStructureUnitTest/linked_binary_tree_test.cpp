#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DataStructure/linked_binary_tree.h"
#include <vector>
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace linked_binary_tree_test
{
	TEST_CLASS(LinkedBinaryTreeTest)
	{
	public:
		typedef LinkedBinaryTree<std::pair<int, char>> UTree;
		typedef BinaryTreeNode<std::pair<int, char>> UNode;

		TEST_METHOD(base_method)
		{
			UTree tree, null_tree;
			Assert::IsTrue(tree.empty());
			Assert::AreEqual(0, tree.size());
			Assert::AreEqual(0, tree.height());
			Assert::IsNull(tree.root_element());

			std::pair<int, char> element(10, 'a');
			
			tree.make_tree(element, null_tree, null_tree);
			Assert::IsFalse(tree.empty());
			Assert::AreEqual(1, tree.size());
			Assert::AreEqual(1, tree.height());
			Assert::IsNotNull(tree.root_element());
			Assert::AreEqual('a', tree.root_element()->second);
		}

		TEST_METHOD(order_visit)
		{ // 测试树的构建
			UTree tree, null_tree, t1, t2, t3, t4, t5;
			const auto tree_size = 12;
			UNode nodes[tree_size];
			int element_keys[tree_size] = { 0, 30, 5, 40, 2, 35, 80, 32, 60, 85, 31, 33 };
			std::pair<int, char> elements[tree_size];
			for (auto i = 1; i < tree_size; i++)
			{
				elements[i] = std::make_pair(element_keys[i], 'A' + i - 1);
				nodes[i].element = elements[i];
			}

			// build the tree
			/*
			 *            30                 (1)
			 *           /  \                /  \
			 *          5   40             (2)  (3)
			 *         /    / \            /    /  \
			 *        2    35  80        (4)  (5)  (6) 
			 *            /   /  \            /    /  \
			 *           32  60  85          (7)  (8)  (9)
			 *          /  \                /  \
			 *         31  33             (10) (11)
			 */
			// 5:7:10-11
			t1.make_tree(elements[10], null_tree, null_tree);
			t2.make_tree(elements[11], null_tree, null_tree);
			t3.make_tree(elements[7], t1, t2);
			t4.make_tree(elements[5], t3, null_tree);

			// 6:8-9
			t1.make_tree(elements[8], null_tree, null_tree);
			t2.make_tree(elements[9], null_tree, null_tree);
			t3.make_tree(elements[6], t1, t2);

			// 3:5-6，右子树
			t5.make_tree(elements[3], t4, t3);
			Assert::AreEqual(40, t5.root_element()->first);

			// 左子树
			t1.make_tree(elements[4], null_tree, null_tree);
			t2.make_tree(elements[2], t1, null_tree);

			tree.make_tree(elements[1], t2, t5);
			Assert::AreEqual(30, tree.root_element()->first);

			// level order visit
			int order_actual[tree_size] = { 0 };
			int order_expected[tree_size] = { 30, 5, 40, 2, 35, 80, 32, 60, 85, 31, 33, 0 };
			auto index = 0;

			const auto visit_func = [&order_actual, &index](UNode* node)
			{
				order_actual[index++] = node->element.first;
			};

			tree.level_order(visit_func);
			for (auto i = 0; i < tree_size; i++)
			{
				Assert::AreEqual(order_expected[i], order_actual[i]);
			}

			// pre order visit
			index = 0;
			int pre_order_expected[tree_size] = { 30, 5, 2, 40, 35, 32, 31, 33, 80, 60, 85, 0 };
			tree.pre_order(visit_func);
			for (auto i = 0; i < tree_size; i++)
			{
				Assert::AreEqual(pre_order_expected[i], order_actual[i]);
			}

			// in order visit
			index = 0;
			int in_order_expected[tree_size] = { 2, 5, 30, 31, 32, 33, 35, 40, 60, 80, 85, 0 };
			tree.in_order(visit_func);
			for (auto i = 0; i < tree_size; i++)
			{
				Assert::AreEqual(in_order_expected[i], order_actual[i]);
			}

			// post order visit
			index = 0;
			int post_order_expected[tree_size] = { 2, 5, 31, 33, 32, 35, 60, 85, 80, 40, 30, 0 };
			tree.post_order(visit_func);
			for (auto i = 0; i < tree_size; i++)
			{
				Assert::AreEqual(post_order_expected[i], order_actual[i]);
			}

		}

	};
}