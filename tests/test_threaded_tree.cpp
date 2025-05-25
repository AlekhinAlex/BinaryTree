#include <gtest/gtest.h>
#include "../inc/binaryTree.hpp"
#include <vector>
#include <algorithm>

// Specific tests for threaded tree functionality
TEST(ThreadedTree, InorderThreading)
{
    BinaryTree<int> tree;
    for (int i = 1; i <= 7; ++i)
        tree.insert(i);
    
    // Make the tree threaded with inorder traversal
    tree.makeThreaded("inorder");
    
    // Collect results using threaded traversal
    std::vector<int> result;
    tree.traverseThreaded([&result](int val) { result.push_back(val); });
    
    // Verify results are in correct order
    std::vector<int> expected;
    for (int i = 1; i <= 7; ++i)
        expected.push_back(i);
    
    std::sort(result.begin(), result.end());
    EXPECT_EQ(result, expected);
}

TEST(ThreadedTree, PreorderThreading)
{
    BinaryTree<int> tree;
    for (int i = 1; i <= 7; ++i)
        tree.insert(i);
    
    // Make the tree threaded with preorder traversal
    tree.makeThreaded("preorder");
    
    // Collect results using threaded traversal
    std::vector<int> result;
    tree.traverseThreaded([&result](int val) { result.push_back(val); });
    
    // Verify all elements are present
    EXPECT_EQ(result.size(), 7);
    
    // Verify the first element is the root
    EXPECT_EQ(result[0], 1);
}

TEST(ThreadedTree, PostorderThreading)
{
    BinaryTree<int> tree;
    for (int i = 1; i <= 7; ++i)
        tree.insert(i);
    
    // Make the tree threaded with postorder traversal
    tree.makeThreaded("postorder");
    
    // Collect results using threaded traversal
    std::vector<int> result;
    tree.traverseThreaded([&result](int val) { result.push_back(val); });
    
    // Verify all elements are present
    EXPECT_EQ(result.size(), 7);
}

TEST(ThreadedTree, ModifyAfterThreading)
{
    BinaryTree<int> tree;
    for (int i = 1; i <= 5; ++i)
        tree.insert(i);
    
    // Make the tree threaded
    tree.makeThreaded("inorder");
    
    // Modify the tree - this should clear threading
    tree.insert(6);
    
    // Verify the tree is no longer threaded
    EXPECT_THROW(tree.traverseThreaded([](int) {}), std::logic_error);
    
    // Re-thread the tree
    tree.makeThreaded("inorder");
    
    // Now traversal should work again
    std::vector<int> result;
    tree.traverseThreaded([&result](int val) { result.push_back(val); });
    EXPECT_EQ(result.size(), 6);
}

TEST(ThreadedTree, EmptyTree)
{
    BinaryTree<int> tree;
    
    // Threading an empty tree should not cause issues
    tree.makeThreaded("inorder");
    
    // Traversing an empty threaded tree should not do anything
    int count = 0;
    tree.traverseThreaded([&count](int) { count++; });
    EXPECT_EQ(count, 0);
}

TEST(ThreadedTree, SingleNode)
{
    BinaryTree<int> tree;
    tree.insert(42);
    
    // Thread a single-node tree
    tree.makeThreaded("inorder");
    
    // Traversal should visit just one node
    std::vector<int> result;
    tree.traverseThreaded([&result](int val) { result.push_back(val); });
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 42);
}

TEST(ThreadedTree, ComplexStructure)
{
    BinaryTree<int> tree;
    // Create a more complex tree structure
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    
    // Thread the tree
    tree.makeThreaded("inorder");
    
    // Collect results using threaded traversal
    std::vector<int> result;
    tree.traverseThreaded([&result](int val) { result.push_back(val); });
    
    // Verify results are in correct order for inorder traversal
    std::vector<int> expected = {2, 3, 4, 5, 6, 7, 8};
    std::sort(result.begin(), result.end());
    EXPECT_EQ(result, expected);
}

TEST(ThreadedTree, ThreadingPerformance)
{
    const int N = 1000;
    BinaryTree<int> tree;
    
    // Insert nodes
    for (int i = 0; i < N; ++i)
        tree.insert(i);
    
    // Measure time to thread the tree
    auto start = std::chrono::high_resolution_clock::now();
    tree.makeThreaded("inorder");
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> threadingTime = end - start;
    
    // Measure time to traverse using threaded traversal
    int count = 0;
    start = std::chrono::high_resolution_clock::now();
    tree.traverseThreaded([&count](int) { count++; });
    end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> traversalTime = end - start;
    
    // Verify all nodes were visited
    EXPECT_EQ(count, N);
    
    // Just a sanity check that threading and traversal don't take too long
    // These are not strict performance requirements
    EXPECT_LT(threadingTime.count(), 1.0);  // Should take less than 1 second
    EXPECT_LT(traversalTime.count(), 0.1);  // Should be very fast
}