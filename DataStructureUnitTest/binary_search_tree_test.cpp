#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DataStructure/binary_search_tree.h"
#include <vector>
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

BEGIN_TEST_MODULE_ATTRIBUTE()
TEST_MODULE_ATTRIBUTE(L"Date", L"2018/04/12")
END_TEST_MODULE_ATTRIBUTE()

TEST_MODULE_INITIALIZE(ModuleInitialize)
{
	Logger::WriteMessage("-------In Module Initialize");
}

TEST_MODULE_CLEANUP(ModuleCleanup)
{
	Logger::WriteMessage("-------In Module Cleanup");
}

namespace binary_search_tree_test
{
	TEST_CLASS(BinarySearchTreeTest)
	{
	public:
		typedef std::pair<int, char> UElement;
		typedef BinaryTreeNode<UElement> UNode;
		typedef BinarySearchTree<int, char> UTree;

		UTree u_tree;
		const int tree_size = 12;
		UNode *nodes;
		UElement *elements;

		BinarySearchTreeTest()
		{
			Logger::WriteMessage("construct test class");
			nodes = new UNode[tree_size];
			elements = new UElement[tree_size];
			int init_keys[12] = { 0, 30, 5, 40, 2, 35, 80, 32, 60, 85, 31, 33 };
			for (auto i = 1; i < tree_size; i++)
			{
				elements[i] = std::make_pair(init_keys[i], 'A' + i - 1);
				nodes[i].element = elements[i];
			}

			// build the tree
			/*
			*            30               (1)                 (A)
			*           /  \              /  \                /  \
			*          5   40           (2)  (3)            (B)  (C)
			*         /    / \          /    /  \           /    / \
			*        2    35  80      (4)  (5)  (6)       (D)  (E) (F)
			*            /   /  \          /    /  \           /   /  \
			*           32  60  85        (7)  (8) (9)       (G)  (H) (I)
			*          /  \              /  \                /  \
			*         31  33           (10) (11)           (J)  (K)
			*/
			// build the link relationship between node and node
			nodes[1].left_child = &nodes[2];
			nodes[1].right_child = &nodes[3];
			nodes[2].left_child = &nodes[4];
			nodes[3].left_child = &nodes[5];
			nodes[3].right_child = &nodes[6];
			nodes[5].left_child = &nodes[7];
			nodes[6].left_child = &nodes[8];
			nodes[6].right_child = &nodes[9];
			nodes[7].left_child = &nodes[10];
			nodes[7].right_child = &nodes[11];
			// build tree
			u_tree.make_tree(&nodes[1], tree_size - 1);
		}

		~BinarySearchTreeTest()
		{
			Logger::WriteMessage("deconstruct test class");
			delete[] elements;
			delete[] nodes;
			u_tree.~UTree();
		}

		TEST_METHOD(base_method)
		{
			UTree tree, null_tree;
			Assert::IsTrue(tree.empty());
			Assert::AreEqual(0, tree.size());
			Assert::AreEqual(0, tree.height());
			Assert::IsNull(tree.root_element());

			std::pair<int, char> element(10, 'a');
			// test tree
			tree.make_tree(element, null_tree, null_tree);
			Assert::IsFalse(tree.empty());
			Assert::AreEqual(1, tree.size());
			Assert::AreEqual(1, tree.height());
			Assert::IsNotNull(tree.root_element());
			Assert::AreEqual('a', tree.root_element()->second);
			// test global u_tree
			Assert::IsFalse(u_tree.empty());
			Assert::AreEqual(11, u_tree.size());
			Assert::AreEqual(5, u_tree.height());
			Assert::IsNotNull(u_tree.root_element());
			Assert::AreEqual('A', u_tree.root_element()->second);
		}

		TEST_METHOD(find)
		{ // ²âÊÔ²éÕÒ
			auto key = 32;
			Assert::AreEqual('G', u_tree.find(key)->second);

			key = 80;
			Assert::AreEqual('F', u_tree.find(key)->second);

			key = 20;
			Assert::IsNull(u_tree.find(key));
		}

		TEST_METHOD(insert)
		{
			UElement insert_element(10, 'Z');
			u_tree.insert(insert_element);
			// check the position of insert
			auto parent_node = u_tree.find_node(5);
			Assert::AreEqual(insert_element.second, parent_node->right_child->element.second);

			// insert when the key is equal
			insert_element = std::make_pair(30, 'T');
			u_tree.insert(insert_element);
			parent_node = u_tree.find_node(30);
			Assert::AreEqual(insert_element.second, parent_node->element.second);
		}

		TEST_METHOD(erase)
		{
			// delete the node has no child
			u_tree.erase(10);
			auto node = u_tree.find_node(5);
			Assert::IsNull(node->right_child);

			// delete the node has only one child
			u_tree.erase(5);
			node = u_tree.find_node(30);
			Assert::AreEqual(2, node->left_child->element.first);

			// delete the node has two child, and the max node is the left child
			u_tree.erase(40);
			node = u_tree.find_node(30);
			Assert::AreEqual(35, node->right_child->element.first);
			node = u_tree.find_node(35);
			Assert::AreEqual(32, node->left_child->element.first);

			// delete the node has two child, and the max node is the left subtree leaf node
			u_tree.erase(35);
			node = u_tree.find_node(30);
			Assert::AreEqual(33, node->right_child->element.first);
			node = u_tree.find_node(32);
			Assert::IsNull(node->right_child);

			// delete the root node
			u_tree.erase(30);
			Assert::AreEqual(2, u_tree.root_element()->first);
		}
	};
}