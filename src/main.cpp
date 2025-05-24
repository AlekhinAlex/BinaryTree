#include <iostream>
#include <sstream>
#include <cassert>
#include <algorithm>
#include "../inc/binaryTree.hpp"
#include "../types/complex.hpp"
#include "../types/person.hpp"
#include <numeric>

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
    int minValue = tree.getMin();
    int maxValue = tree.getMax();
    assertEqual(2, minValue, "Min value should be 2");
    assertEqual(7, maxValue, "Max value should be 7");

    // Test 7: Iterator functionality
    std::cout << "\nTesting iterator functionality..." << std::endl;
    std::cout << "Iterating through tree using iterator: ";
    for (auto it = tree.begin(); it != tree.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Iterating through tree using range-based for loop: ";
    for (const auto &value : tree)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // Test 8: Const iterator functionality
    std::cout << "\nTesting const iterator functionality..." << std::endl;
    const BinaryTree<int> &constTree = tree;
    std::cout << "Iterating through const tree using const_iterator: ";
    for (auto it = constTree.cbegin(); it != constTree.cend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Test 9: Using iterators with algorithms
    std::cout << "\nTesting iterators with algorithms..." << std::endl;
    int sum = std::accumulate(tree.begin(), tree.end(), 0);
    std::cout << "Sum of all elements: " << sum << std::endl;
    assertEqual(27, sum, "Sum of all elements should be 27");

    // Test 10: Complex type in binary tree
    std::cout << "\nTesting binary tree with Complex type..." << std::endl;
    BinaryTree<Complex> complexTree;
    complexTree.insert(Complex(1, 2));
    complexTree.insert(Complex(3, 4));
    complexTree.insert(Complex(5, 6));

    std::cout << "Complex tree elements: ";
    for (const auto &c : complexTree)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    // Test 11: Person type in binary tree
    std::cout << "\nTesting binary tree with Person type..." << std::endl;
    BinaryTree<Person> personTree;
    personTree.insert(Person("Alice", 30));
    personTree.insert(Person("Bob", 25));
    personTree.insert(Person("Charlie", 35));

    std::cout << "Person tree elements: ";
    for (const auto &p : personTree)
    {
        std::cout << p << " ";
    }
    std::cout << std::endl;

    // Test 12: Remove a node
    std::cout << "\nRemoving node 3..." << std::endl;
    tree.remove(3);
    std::cout << "Tree after removal:" << std::endl;
    tree.print();

    // Test 13: Copy constructor
    BinaryTree<int> treeCopy(tree);
    std::cout << "\nOriginal tree:" << std::endl;
    tree.print();
    std::cout << "\nCopied tree:" << std::endl;
    treeCopy.print();

    // Test 14: Exception handling
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

    // Test 15: Clear the tree
    std::cout << "\nClearing the tree..." << std::endl;
    tree.clear();
    assertEqual(true, tree.isEmpty(), "Tree should be empty after clear");
    assertEqual(-1, tree.getHeight(), "Height should be -1 after clear");

    std::cout << "\nAll tests completed!" << std::endl;

    return 0;
}
