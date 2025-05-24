#include <iostream>
#include <sstream>
#include <cassert>
#include "../inc/binaryTree.hpp"

// Helper function to check if two values are equal
template <typename T>
void assertEqual(const T &expected, const T &actual, const std::string &message)
{
    if (expected != actual)
    {
        std::cerr << "FAILED: " << message << std::endl;
        std::cerr << "  Expected: " << expected << std::endl;
        std::cerr << "  Actual: " << actual << std::endl;
    }
    else
    {
        std::cout << "PASSED: " << message << std::endl;
    }
}

// Helper function to capture output from traversals
template <typename T>
std::string captureOutput(void (BinaryTree<T>::*method)(std::ostream &) const, const BinaryTree<T> &tree)
{
    std::ostringstream oss;
    (tree.*method)(oss);
    return oss.str();
}

int main()
{
    std::cout << "=== Testing Binary Tree Implementation ===" << std::endl;

    // Test 1: Create an empty tree
    BinaryTree<int> tree;
    assertEqual(true, tree.isEmpty(), "Empty tree should be empty");
    assertEqual(-1, tree.getHeight(), "Height of empty tree should be -1");

    // Test 2: Insert nodes
    tree.insert(5); // Root
    assertEqual(false, tree.isEmpty(), "Tree with root should not be empty");
    assertEqual(0, tree.getHeight(), "Height of tree with only root should be 0");

    tree.insert(3); // Left child of root
    tree.insert(7); // Right child of root
    tree.insert(2); // Left child of 3
    tree.insert(4); // Right child of 3

    assertEqual(2, tree.getHeight(), "Height of tree should be 2");

    // Test 3: Search for nodes
    TreeNode<int> *node4 = tree.search(4);
    assertEqual(4, node4->getData(), "Search should find node with value 4");

    // Test 4: Insert at specific node
    tree.insert(6, tree.search(7));
    // The height should be 2 because the insert method adds nodes in level order
    assertEqual(2, tree.getHeight(), "Height after inserting 6 should be 2");

    // Test 5: Test traversals
    std::cout << "\nInorder traversal (expected: 2 3 4 5 6 7): ";
    tree.inorderTraversal();

    std::cout << "\nPreorder traversal (expected: 5 3 2 4 7 6): ";
    tree.preorderTraversal();

    std::cout << "\nPostorder traversal (expected: 2 4 3 6 7 5): ";
    tree.postorderTraversal();

    // Test 6: Min/Max functionality
    std::cout << "\n\nTesting min/max functionality..." << std::endl;
    int minValue = tree.getMin(); // Changed from const int* to int
    int maxValue = tree.getMax(); // Changed from const int* to int
    assertEqual(2, minValue, "Min value should be 2");
    assertEqual(7, maxValue, "Max value should be 7");

    // Test 7: Remove a node
    std::cout << "\nRemoving node 3..." << std::endl;
    tree.remove(3);
    std::cout << "Tree after removal:" << std::endl;
    tree.print();

    // Test 8: Copy constructor
    BinaryTree<int> treeCopy(tree);
    std::cout << "\nOriginal tree:" << std::endl;
    tree.print();
    std::cout << "\nCopied tree:" << std::endl;
    treeCopy.print();

    // Test 9: Exception handling
    std::cout << "\nTesting exception handling..." << std::endl;
    try
    {
        tree.remove(99); // Value doesn't exist
        std::cout << "FAILED: Should have thrown exception" << std::endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "PASSED: Caught exception: " << e.what() << std::endl;
    }

    // Test 10: Clear the tree
    std::cout << "\nClearing the tree..." << std::endl;
    tree.clear();
    assertEqual(true, tree.isEmpty(), "Tree should be empty after clear");
    assertEqual(-1, tree.getHeight(), "Height should be -1 after clear");

    std::cout << "\nAll tests completed!" << std::endl;

    return 0;
}
