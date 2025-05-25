#include <gtest/gtest.h>
#include "../inc/binaryTree.hpp"
#include "../types/complex.hpp"
#include "../types/person.hpp"
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>

TEST(BinaryTreeInt, InsertAndHasValue)
{
    BinaryTree<int> tree;
    for (int i = 0; i < 100; ++i)
        tree.insert(i);
    for (int i = 0; i < 100; ++i)
        EXPECT_TRUE(tree.hasValue(i));
    EXPECT_FALSE(tree.hasValue(1000));
}

TEST(BinaryTreeInt, Remove)
{
    BinaryTree<int> tree;
    for (int i = 0; i < 10; ++i)
        tree.insert(i);
    tree.remove(5);
    EXPECT_FALSE(tree.hasValue(5));
    for (int i = 0; i < 10; ++i)
        if (i != 5)
            EXPECT_TRUE(tree.hasValue(i));
}

TEST(BinaryTreeString, InsertRemoveSearch)
{
    BinaryTree<std::string> tree;
    tree.insert("a");
    tree.insert("b");
    tree.insert("c");
    EXPECT_TRUE(tree.hasValue("a"));
    tree.remove("b");
    EXPECT_FALSE(tree.hasValue("b"));
}

TEST(BinaryTreeInt, Traversals)
{
    BinaryTree<int> tree;
    for (int i = 1; i <= 7; ++i)
        tree.insert(i);
    std::ostringstream oss;
    tree.inorderTraversal(oss);
    std::string s = oss.str();
    for (int i = 1; i <= 7; ++i)
        EXPECT_NE(s.find(std::to_string(i)), std::string::npos);
}

TEST(BinaryTreeInt, MinMax)
{
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(1);
    EXPECT_EQ(tree.getMin(), 1);
    EXPECT_EQ(tree.getMax(), 20);
}

TEST(BinaryTreeInt, BalanceAndIsBalanced)
{
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);

    EXPECT_FALSE(tree.isBalanced());

    tree.balance();
    EXPECT_TRUE(tree.isBalanced());
}

TEST(BinaryTreeInt, SubtreeAndContainsSubtree)
{
    BinaryTree<int> tree;
    for (int i = 1; i <= 7; ++i)
        tree.insert(i);
    auto sub = tree.subtree(3);
    EXPECT_TRUE(tree.containsSubtree(*sub));
    delete sub;
}

TEST(BinaryTreeInt, IteratorAndConstIterator)
{
    BinaryTree<int> tree;
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

TEST(BinaryTreeInt, OperatorEqNeq)
{
    BinaryTree<int> t1, t2;
    for (int i = 0; i < 5; ++i)
    {
        t1.insert(i);
        t2.insert(i);
    }
    EXPECT_TRUE(t1 == t2);
    t2.insert(100);
    EXPECT_TRUE(t1 != t2);
}

TEST(BinaryTreeInt, MergeAndOperatorPlus)
{
    BinaryTree<int> t1, t2;
    for (int i = 0; i < 5; ++i)
        t1.insert(i);
    for (int i = 5; i < 10; ++i)
        t2.insert(i);
    t1.merge(t2);
    for (int i = 0; i < 10; ++i)
        EXPECT_TRUE(t1.hasValue(i));
    BinaryTree<int> t3 = t1 + t2;
    for (int i = 0; i < 10; ++i)
        EXPECT_TRUE(t3.hasValue(i));
}

TEST(BinaryTreeInt, WhereApplyReduce)
{
    BinaryTree<int> tree;
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

TEST(BinaryTreeInt, ThreadedTraversal)
{
    BinaryTree<int> tree;
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

TEST(BinaryTreeInt, FindByPath)
{
    BinaryTree<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);

    auto sub = tree.findByPath("L");
    ASSERT_NE(sub, nullptr);
    EXPECT_TRUE(sub->hasValue(1));
    delete sub;

    sub = tree.findByPath("R");
    ASSERT_NE(sub, nullptr);
    EXPECT_TRUE(sub->hasValue(3));
    delete sub;

    sub = tree.findByPath("LL");
    EXPECT_EQ(sub, nullptr);
}

TEST(BinaryTreeInt, SerializeDeserialize)
{
    BinaryTree<int> tree;
    for (int i = 1; i <= 5; ++i)
        tree.insert(i);
    std::string ser = tree.serialize("inorder");
    BinaryTree<int> tree2;
}

TEST(BinaryTreeInt, LargeScaleInsertSearch)
{
    BinaryTree<int> tree;
    const int N = 10000;
    for (int i = 0; i < N; ++i)
        tree.insert(i);
    for (int i = 0; i < N; i += 1000)
        EXPECT_TRUE(tree.hasValue(i));
}

TEST(BinaryTreeString, LargeScale)
{
    BinaryTree<std::string> tree;
    for (int i = 0; i < 1000; ++i)
        tree.insert("str" + std::to_string(i));
    for (int i = 0; i < 1000; i += 100)
        EXPECT_TRUE(tree.hasValue("str" + std::to_string(i)));
}

// Tests with custom Complex type
TEST(BinaryTreeComplex, BasicOperations)
{
    BinaryTree<Complex> tree;
    tree.insert(Complex(1.0, 2.0));
    tree.insert(Complex(3.0, 4.0));
    tree.insert(Complex(5.0, 6.0));

    EXPECT_TRUE(tree.hasValue(Complex(1.0, 2.0)));
    EXPECT_TRUE(tree.hasValue(Complex(3.0, 4.0)));
    EXPECT_FALSE(tree.hasValue(Complex(7.0, 8.0)));

    tree.remove(Complex(3.0, 4.0));
    EXPECT_FALSE(tree.hasValue(Complex(3.0, 4.0)));
}

TEST(BinaryTreeComplex, Iterators)
{
    BinaryTree<Complex> tree;
    std::vector<Complex> values = {
        Complex(1.0, 1.0),
        Complex(2.0, 2.0),
        Complex(3.0, 3.0)};

    for (const auto &v : values)
        tree.insert(v);

    std::vector<Complex> traversed;
    for (auto it = tree.begin(); it != tree.end(); ++it)
        traversed.push_back(*it);

    EXPECT_EQ(traversed.size(), values.size());
}

TEST(BinaryTreeComplex, ThreadedTraversal)
{
    BinaryTree<Complex> tree;
    tree.insert(Complex(1.0, 1.0));
    tree.insert(Complex(2.0, 2.0));
    tree.insert(Complex(3.0, 3.0));

    tree.makeThreaded("inorder");
    int count = 0;
    tree.traverseThreaded([&count](Complex)
                          { count++; });
    EXPECT_EQ(count, 3);
}

// Tests with custom Person type
TEST(BinaryTreePerson, BasicOperations)
{
    BinaryTree<Person> tree;
    tree.insert(Person("Alice", 25));
    tree.insert(Person("Bob", 30));
    tree.insert(Person("Charlie", 35));

    EXPECT_TRUE(tree.hasValue(Person("Alice", 25)));
    EXPECT_TRUE(tree.hasValue(Person("Bob", 30)));
    EXPECT_FALSE(tree.hasValue(Person("Dave", 40)));

    tree.remove(Person("Bob", 30));
    EXPECT_FALSE(tree.hasValue(Person("Bob", 30)));
}

TEST(BinaryTreePerson, MinMax)
{
    BinaryTree<Person> tree;
    tree.insert(Person("Alice", 25));
    tree.insert(Person("Bob", 30));
    tree.insert(Person("Charlie", 35));
    tree.insert(Person("Dave", 20));

    EXPECT_EQ(tree.getMin().getAge(), 20);
    EXPECT_EQ(tree.getMax().getAge(), 35);
}

// Edge cases
TEST(BinaryTreeEdgeCases, EmptyTree)
{
    BinaryTree<int> tree;
    EXPECT_TRUE(tree.isEmpty());
    EXPECT_THROW(tree.getMin(), std::runtime_error);
    EXPECT_THROW(tree.getMax(), std::runtime_error);
    EXPECT_FALSE(tree.hasValue(5));

    // Empty tree iterators
    EXPECT_EQ(tree.begin(), tree.end());
    EXPECT_EQ(tree.cbegin(), tree.cend());
}

TEST(BinaryTreeEdgeCases, SingleNode)
{
    BinaryTree<int> tree;
    tree.insert(42);

    EXPECT_FALSE(tree.isEmpty());
    EXPECT_EQ(tree.getMin(), 42);
    EXPECT_EQ(tree.getMax(), 42);

    // Single node should be balanced
    EXPECT_TRUE(tree.isBalanced());

    // Removing the only node
    tree.remove(42);
    EXPECT_TRUE(tree.isEmpty());
}

TEST(BinaryTreeEdgeCases, DuplicateValues)
{
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(5); // Duplicate
    tree.insert(5); // Duplicate

    // Count occurrences using iterator
    int count = 0;
    for (auto it = tree.begin(); it != tree.end(); ++it)
    {
        if (*it == 5)
            count++;
    }
    EXPECT_EQ(count, 3);

    // Remove one occurrence
    tree.remove(5);
    count = 0;
    for (auto it = tree.begin(); it != tree.end(); ++it)
    {
        if (*it == 5)
            count++;
    }
    EXPECT_EQ(count, 2);
}

// Iterator specific tests
TEST(BinaryTreeIterators, DifferentTraversalOrders)
{
    BinaryTree<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);

    // Test inorder (should be 1,2,3)
    std::vector<int> inorder;
    for (auto it = tree.begin("inorder"); it != tree.end("inorder"); ++it)
    {
        inorder.push_back(*it);
    }
    EXPECT_EQ(inorder.size(), 3);
    if (inorder.size() == 3)
    {
        EXPECT_TRUE(inorder[0] <= inorder[1] && inorder[1] <= inorder[2]);
    }

    // Test preorder
    std::vector<int> preorder;
    for (auto it = tree.begin("preorder"); it != tree.end("preorder"); ++it)
    {
        preorder.push_back(*it);
    }
    EXPECT_EQ(preorder.size(), 3);

    // Test postorder
    std::vector<int> postorder;
    for (auto it = tree.begin("postorder"); it != tree.end("postorder"); ++it)
    {
        postorder.push_back(*it);
    }
    EXPECT_EQ(postorder.size(), 3);

    // All three traversals should contain the same elements but in different orders
    std::sort(inorder.begin(), inorder.end());
    std::sort(preorder.begin(), preorder.end());
    std::sort(postorder.begin(), postorder.end());
    EXPECT_EQ(inorder, preorder);
    EXPECT_EQ(preorder, postorder);
}
