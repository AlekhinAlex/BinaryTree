#include <gtest/gtest.h>
#include "../inc/binaryTree.hpp"
#include "../inc/AVLTree.hpp"
#include "../types/complex.hpp"
#include "../types/person.hpp"
#include <vector>
#include <string>

// Tests for Complex type
class ComplexTreeTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Add some complex numbers to the tree
        tree.insert(Complex(1.0, 2.0));
        tree.insert(Complex(3.0, 4.0));
        tree.insert(Complex(5.0, 6.0));
        tree.insert(Complex(0.0, 0.0));
        tree.insert(Complex(-1.0, -2.0));
    }
    
    BinaryTree<Complex> tree;
};

TEST_F(ComplexTreeTest, Search) {
    EXPECT_TRUE(tree.hasValue(Complex(1.0, 2.0)));
    EXPECT_TRUE(tree.hasValue(Complex(3.0, 4.0)));
    EXPECT_FALSE(tree.hasValue(Complex(10.0, 10.0)));
}

TEST_F(ComplexTreeTest, MinMax) {
    // Min should be the complex number with smallest magnitude
    Complex min = tree.getMin();
    EXPECT_DOUBLE_EQ(min.getReal(), 0.0);
    EXPECT_DOUBLE_EQ(min.getImag(), 0.0);
    
    // Max should be the complex number with largest magnitude
    Complex max = tree.getMax();
    EXPECT_DOUBLE_EQ(max.getReal(), 5.0);
    EXPECT_DOUBLE_EQ(max.getImag(), 6.0);
}

TEST_F(ComplexTreeTest, Traversals) {
    std::vector<Complex> inorder;
    for (auto it = tree.begin("inorder"); it != tree.end("inorder"); ++it) {
        inorder.push_back(*it);
    }
    EXPECT_EQ(inorder.size(), 5);
    
    std::vector<Complex> preorder;
    for (auto it = tree.begin("preorder"); it != tree.end("preorder"); ++it) {
        preorder.push_back(*it);
    }
    EXPECT_EQ(preorder.size(), 5);
    
    std::vector<Complex> postorder;
    for (auto it = tree.begin("postorder"); it != tree.end("postorder"); ++it) {
        postorder.push_back(*it);
    }
    EXPECT_EQ(postorder.size(), 5);
}

TEST_F(ComplexTreeTest, FunctionalOperations) {
    // Apply: multiply real and imaginary parts by 2
    auto doubled = tree.apply([](Complex c) {
        return Complex(c.getReal() * 2, c.getImag() * 2);
    });
    
    EXPECT_TRUE(doubled.hasValue(Complex(2.0, 4.0)));
    EXPECT_TRUE(doubled.hasValue(Complex(6.0, 8.0)));
    
    // Where: only keep complex numbers with positive real part
    auto positive = tree.where([](Complex c) {
        return c.getReal() > 0;
    });
    
    EXPECT_TRUE(positive.hasValue(Complex(1.0, 2.0)));
    EXPECT_FALSE(positive.hasValue(Complex(-1.0, -2.0)));
}

TEST_F(ComplexTreeTest, Threading) {
    tree.makeThreaded("inorder");
    
    std::vector<Complex> result;
    tree.traverseThreaded([&result](Complex c) {
        result.push_back(c);
    });
    
    EXPECT_EQ(result.size(), 5);
}

// Tests for Person type
class PersonTreeTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Add some people to the tree
        tree.insert(Person("Alice", 25));
        tree.insert(Person("Bob", 30));
        tree.insert(Person("Charlie", 20));
        tree.insert(Person("David", 35));
        tree.insert(Person("Eve", 28));
    }
    
    BinaryTree<Person> tree;
};

TEST_F(PersonTreeTest, Search) {
    EXPECT_TRUE(tree.hasValue(Person("Alice", 25)));
    EXPECT_TRUE(tree.hasValue(Person("Bob", 30)));
    EXPECT_FALSE(tree.hasValue(Person("Frank", 40)));
}

TEST_F(PersonTreeTest, MinMax) {
    // Min should be the person with lowest age
    Person min = tree.getMin();
    EXPECT_EQ(min.getName(), "Charlie");
    EXPECT_EQ(min.getAge(), 20);
    
    // Max should be the person with highest age
    Person max = tree.getMax();
    EXPECT_EQ(max.getName(), "David");
    EXPECT_EQ(max.getAge(), 35);
}

TEST_F(PersonTreeTest, Traversals) {
    std::vector<Person> inorder;
    for (auto it = tree.begin("inorder"); it != tree.end("inorder"); ++it) {
        inorder.push_back(*it);
    }
    EXPECT_EQ(inorder.size(), 5);
    
    std::vector<Person> preorder;
    for (auto it = tree.begin("preorder"); it != tree.end("preorder"); ++it) {
        preorder.push_back(*it);
    }
    EXPECT_EQ(preorder.size(), 5);
    
    std::vector<Person> postorder;
    for (auto it = tree.begin("postorder"); it != tree.end("postorder"); ++it) {
        postorder.push_back(*it);
    }
    EXPECT_EQ(postorder.size(), 5);
}

TEST_F(PersonTreeTest, FunctionalOperations) {
    // Apply: increment everyone's age by 1
    auto aged = tree.apply([](Person p) {
        Person newP = p;
        newP.setAge(p.getAge() + 1);
        return newP;
    });
    
    EXPECT_TRUE(aged.hasValue(Person("Alice", 26)));
    EXPECT_TRUE(aged.hasValue(Person("Bob", 31)));
    
    // Where: only keep people older than 25
    auto adults = tree.where([](Person p) {
        return p.getAge() > 25;
    });
    
    EXPECT_TRUE(adults.hasValue(Person("Bob", 30)));
    EXPECT_FALSE(adults.hasValue(Person("Charlie", 20)));
}

TEST_F(PersonTreeTest, Threading) {
    tree.makeThreaded("inorder");
    
    std::vector<Person> result;
    tree.traverseThreaded([&result](Person p) {
        result.push_back(p);
    });
    
    EXPECT_EQ(result.size(), 5);
}

// Test AVL tree with custom types - renamed to avoid duplicate symbols
TEST(AVLTreeComplexCustom, BasicOperations) {
    AVLTree<Complex> tree;
    tree.insert(Complex(1.0, 2.0));
    tree.insert(Complex(3.0, 4.0));
    tree.insert(Complex(5.0, 6.0));
    
    EXPECT_TRUE(tree.hasValue(Complex(1.0, 2.0)));
    EXPECT_TRUE(tree.hasValue(Complex(3.0, 4.0)));
    EXPECT_FALSE(tree.hasValue(Complex(7.0, 8.0)));
    
    tree.remove(Complex(3.0, 4.0));
    EXPECT_FALSE(tree.hasValue(Complex(3.0, 4.0)));
}

TEST(AVLTreePersonCustom, BasicOperations) {
    AVLTree<Person> tree;
    tree.insert(Person("Alice", 25));
    tree.insert(Person("Bob", 30));
    tree.insert(Person("Charlie", 20));
    
    EXPECT_TRUE(tree.hasValue(Person("Alice", 25)));
    EXPECT_TRUE(tree.hasValue(Person("Bob", 30)));
    EXPECT_FALSE(tree.hasValue(Person("David", 35)));
    
    tree.remove(Person("Bob", 30));
    EXPECT_FALSE(tree.hasValue(Person("Bob", 30)));
}