#include <gtest/gtest.h>
#include "../inc/AVLTree.hpp"
#include "../types/complex.hpp"
#include "../types/person.hpp"
#include <string>
#include <set>
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>

TEST(AVLTreeInt, InsertAndHasValue)
{
    AVLTree<int> tree;
    for (int i = 0; i < 100; ++i)
        tree.insert(i);
    for (int i = 0; i < 100; ++i)
        EXPECT_TRUE(tree.hasValue(i));
    EXPECT_FALSE(tree.hasValue(1000));
}

TEST(AVLTreeInt, Remove)
{
    AVLTree<int> tree;
    for (int i = 0; i < 10; ++i)
        tree.insert(i);
    tree.remove(5);
    EXPECT_FALSE(tree.hasValue(5));
    for (int i = 0; i < 10; ++i)
        if (i != 5)
            EXPECT_TRUE(tree.hasValue(i));
}

TEST(AVLTreeString, InsertRemoveSearch)
{
    AVLTree<std::string> tree;
    tree.insert("a");
    tree.insert("b");
    tree.insert("c");
    EXPECT_TRUE(tree.hasValue("a"));
    tree.remove("b");
    EXPECT_FALSE(tree.hasValue("b"));
}

TEST(AVLTreeInt, Traversals)
{
    AVLTree<int> tree;
    for (int i = 1; i <= 7; ++i)
        tree.insert(i);
    std::set<int> traversed;
    for (auto it = tree.cbegin(); it != tree.cend(); ++it)
        traversed.insert(*it);
    for (int i = 1; i <= 7; ++i)
        EXPECT_TRUE(traversed.count(i));
}

TEST(AVLTreeInt, MinMax)
{
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(1);
    EXPECT_EQ(tree.getMin(), 1);
    EXPECT_EQ(tree.getMax(), 20);
}

TEST(AVLTreeInt, IsBalancedAlways)
{
    AVLTree<int> tree;
    for (int i = 1; i <= 100; ++i)
        tree.insert(i);
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AVLTreeInt, SubtreeAndContainsSubtree)
{
    AVLTree<int> tree;
    for (int i = 1; i <= 7; ++i)
        tree.insert(i);
    auto sub = tree.subtree(3);
    EXPECT_TRUE(tree.containsSubtree(*sub));
    delete sub;
}

TEST(AVLTreeInt, IteratorAndConstIterator)
{
    AVLTree<int> tree;
    std::set<int> values = {1, 2, 3, 4, 5};
    for (int v : values)
        tree.insert(v);
    std::set<int> traversed;
    for (auto it = tree.begin(); it != tree.end(); ++it)
        traversed.insert(*it);
    EXPECT_EQ(values, traversed);
    traversed.clear();
    for (auto it = tree.cbegin(); it != tree.cend(); ++it)
        traversed.insert(*it);
    EXPECT_EQ(values, traversed);
}

TEST(AVLTreeInt, OperatorEqNeq)
{
    AVLTree<int> t1, t2;
    for (int i = 0; i < 5; ++i)
    {
        t1.insert(i);
        t2.insert(i);
    }
    EXPECT_TRUE(t1 == t2);
    t2.insert(100);
    EXPECT_TRUE(t1 != t2);
}

TEST(AVLTreeInt, MergeAndOperatorPlus)
{
    AVLTree<int> t1, t2;
    for (int i = 0; i < 5; ++i)
        t1.insert(i);
    for (int i = 5; i < 10; ++i)
        t2.insert(i);
    t1.merge(t2);
    for (int i = 0; i < 10; ++i)
        EXPECT_TRUE(t1.hasValue(i));
}

TEST(AVLTreeInt, WhereApplyReduce)
{
    AVLTree<int> tree;
    for (int i = 1; i <= 10; ++i)
        tree.insert(i);
    auto evenTree = tree.where([](int x)
                               { return x % 2 == 0; });
    for (int i = 2; i <= 10; i += 2)
        EXPECT_TRUE(evenTree.hasValue(i));
    auto squared = tree.apply([](int x)
                              { return x * x; });
    for (int i = 1; i <= 10; ++i)
        EXPECT_TRUE(squared.hasValue(i * i));
    int sum = tree.reduce([](int a, int b)
                          { return a + b; }, 0);
    EXPECT_EQ(sum, 55);
}

TEST(AVLTreeInt, ThreadedTraversal)
{
    AVLTree<int> tree;
    for (int i = 1; i <= 10; ++i)
        tree.insert(i);
    tree.makeThreaded("inorder");
    std::vector<int> result;
    tree.traverseThreaded([&](int x)
                          { result.push_back(x); });
    std::sort(result.begin(), result.end());
    for (int i = 1; i <= 10; ++i)
        EXPECT_EQ(result[i - 1], i);
}

TEST(AVLTreeInt, FindByPath)
{
    AVLTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    auto sub = tree.findByPath("L");
    tree.print();
    ASSERT_NE(sub, nullptr);
    EXPECT_TRUE(sub->hasValue(1));
    delete sub;
}

TEST(AVLTreeInt, LargeScaleInsertSearch)
{
    AVLTree<int> tree;
    const int N = 10000;
    for (int i = 0; i < N; ++i)
        tree.insert(i);
    for (int i = 0; i < N; i += 1000)
        EXPECT_TRUE(tree.hasValue(i));
}

TEST(AVLTreeString, LargeScale)
{
    AVLTree<std::string> tree;
    for (int i = 0; i < 1000; ++i)
        tree.insert("str" + std::to_string(i));
    for (int i = 0; i < 1000; i += 100)
        EXPECT_TRUE(tree.hasValue("str" + std::to_string(i)));
}

// Tests with custom Complex type
TEST(AVLTreeComplex, BasicOperations)
{
    AVLTree<Complex> tree;
    tree.insert(Complex(1.0, 2.0));
    tree.insert(Complex(3.0, 4.0));
    tree.insert(Complex(5.0, 6.0));

    EXPECT_TRUE(tree.hasValue(Complex(1.0, 2.0)));
    EXPECT_TRUE(tree.hasValue(Complex(3.0, 4.0)));
    EXPECT_FALSE(tree.hasValue(Complex(7.0, 8.0)));

    // Test that AVL tree maintains balance
    EXPECT_TRUE(tree.isBalanced());

    // Test removal
    tree.remove(Complex(3.0, 4.0));
    EXPECT_FALSE(tree.hasValue(Complex(3.0, 4.0)));
    EXPECT_TRUE(tree.isBalanced());
}

// Tests with custom Person type
TEST(AVLTreePerson, BasicOperations)
{
    AVLTree<Person> tree;
    tree.insert(Person("Alice", 25));
    tree.insert(Person("Bob", 30));
    tree.insert(Person("Charlie", 20));

    EXPECT_TRUE(tree.hasValue(Person("Alice", 25)));
    EXPECT_TRUE(tree.hasValue(Person("Bob", 30)));
    EXPECT_FALSE(tree.hasValue(Person("Dave", 40)));

    // Test that AVL tree maintains balance
    EXPECT_TRUE(tree.isBalanced());

    // Test removal
    tree.remove(Person("Bob", 30));
    EXPECT_FALSE(tree.hasValue(Person("Bob", 30)));
    EXPECT_TRUE(tree.isBalanced());
}

// Edge cases for AVL tree
TEST(AVLTreeEdgeCases, EmptyTree)
{
    AVLTree<int> tree;
    EXPECT_TRUE(tree.isEmpty());
    EXPECT_THROW(tree.getMin(), std::runtime_error);
    EXPECT_THROW(tree.getMax(), std::runtime_error);
    EXPECT_FALSE(tree.hasValue(5));

    // Empty tree should be considered balanced
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AVLTreeEdgeCases, SingleNode)
{
    AVLTree<int> tree;
    tree.insert(42);

    EXPECT_FALSE(tree.isEmpty());
    EXPECT_EQ(tree.getMin(), 42);
    EXPECT_EQ(tree.getMax(), 42);

    // Single node should be balanced
    EXPECT_TRUE(tree.isBalanced());
}

// Test specific AVL tree rotations
TEST(AVLTreeRotations, LeftRotation)
{
    AVLTree<int> tree;
    // Create a right-heavy tree that requires left rotation
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    // After rotations, tree should be balanced
    EXPECT_TRUE(tree.isBalanced());

    // All values should still be present
    EXPECT_TRUE(tree.hasValue(10));
    EXPECT_TRUE(tree.hasValue(20));
    EXPECT_TRUE(tree.hasValue(30));
}

TEST(AVLTreeRotations, RightRotation)
{
    AVLTree<int> tree;
    // Create a left-heavy tree that requires right rotation
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);

    // After rotations, tree should be balanced
    EXPECT_TRUE(tree.isBalanced());

    // All values should still be present
    EXPECT_TRUE(tree.hasValue(10));
    EXPECT_TRUE(tree.hasValue(20));
    EXPECT_TRUE(tree.hasValue(30));
}

TEST(AVLTreeRotations, LeftRightRotation)
{
    AVLTree<int> tree;
    // Create a tree that requires left-right rotation
    tree.insert(30);
    tree.insert(10);
    tree.insert(20);

    // After rotations, tree should be balanced
    EXPECT_TRUE(tree.isBalanced());

    // All values should still be present
    EXPECT_TRUE(tree.hasValue(10));
    EXPECT_TRUE(tree.hasValue(20));
    EXPECT_TRUE(tree.hasValue(30));
}

TEST(AVLTreeRotations, RightLeftRotation)
{
    AVLTree<int> tree;
    // Create a tree that requires right-left rotation
    tree.insert(10);
    tree.insert(30);
    tree.insert(20);

    // After rotations, tree should be balanced
    EXPECT_TRUE(tree.isBalanced());

    // All values should still be present
    EXPECT_TRUE(tree.hasValue(10));
    EXPECT_TRUE(tree.hasValue(20));
    EXPECT_TRUE(tree.hasValue(30));
}

// Test AVL tree with sequential insertions
TEST(AVLTreeBalance, SequentialInsertions)
{
    AVLTree<int> tree;
    // Insert values in ascending order
    for (int i = 1; i <= 100; ++i)
    {
        tree.insert(i);
        EXPECT_TRUE(tree.isBalanced());
    }

    // Tree should remain balanced after all insertions
    EXPECT_TRUE(tree.isBalanced());

    // All values should be present
    for (int i = 1; i <= 100; ++i)
    {
        EXPECT_TRUE(tree.hasValue(i));
    }
}
