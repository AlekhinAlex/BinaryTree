#pragma once

#include "treeNode.hpp"
#include "iterators.hpp"
#include <iostream>
#include <vector>
#include <functional>

template <typename T>
class BinaryTree
{
protected:
    TreeNode<T> *root;
    bool isThreaded = false;

public:
    BinaryTree();
    BinaryTree(const BinaryTree &other);
    ~BinaryTree();

    const TreeNode<T> *getRoot() const;
    TreeNode<T> *getRoot();

    const TreeNode<T> *getMaxNode() const;
    TreeNode<T> *getMaxNode();
    const T &getMax() const;
    T &getMax();
    void getMaxHelper(TreeNode<T> *node, TreeNode<T> *&max) const;

    const TreeNode<T> *getMinNode() const;
    TreeNode<T> *getMinNode();
    const T &getMin() const;
    T &getMin();
    void getMinHelper(TreeNode<T> *node, TreeNode<T> *&min) const;

    void insert(const T &value, TreeNode<T> *root); //? Do I need this
    virtual void insert(const T &value);

    virtual void remove(const T &value);

    const TreeNode<T> *search(const T &value) const;
    TreeNode<T> *search(const T &value);

    TreeNode<T> *findParent(TreeNode<T> *node) const;

    //? MB remake for convinient printing into app
    void print(std::ostream &os = std::cout) const;

    bool hasValue(const T &value) const;

    void balance();
    TreeNode<T> *buildBalancedTree(std::vector<TreeNode<T> *> &nodes, int start, int end);
    virtual bool isBalanced() const;
    int isBalancedHelper(const TreeNode<T> *node) const;

    // L - root - R
    void inorderTraversal(std::ostream &os = std::cout) const;
    void inorderTraversal(const TreeNode<T> *node, std::ostream &os = std::cout) const;
    void inorderTraversal(TreeNode<T> *node, std::vector<TreeNode<T> *> &nodes);

    // root - L - R
    void preorderTraversal(std::ostream &os = std::cout) const;
    void preorderTraversal(const TreeNode<T> *node, std::ostream &os = std::cout) const;

    // L - R - root
    void postorderTraversal(std::ostream &os = std::cout) const;
    void postorderTraversal(const TreeNode<T> *node, std::ostream &os = std::cout) const;

    BinaryTree<T> *subtree(const T &value) const;
    bool containsSubtree(const BinaryTree &sub) const;

    int getHeight() const;
    bool isEmpty() const;

    void clear();

    bool operator==(const BinaryTree<T> &other) const;
    bool operator!=(const BinaryTree<T> &other) const;
    BinaryTree<T> &operator=(const BinaryTree<T> &other);

    BinaryTree<T> apply(std::function<T(T)> func) const;
    BinaryTree<T> where(std::function<bool(T)> predicate) const;
    T reduce(std::function<T(T, T)> func, T initial) const;

    void makeThreaded(const std::string &traversalOrder = "inorder");
    void traverseThreaded(std::function<void(T)> visit = [](const T &val)
                          { std::cout << val; }) const;

    std::string serialize(const std::string &traversalOrder = "inorder") const;
    void deserialize(const std::string &data, const std::string &format = "default");

    BinaryTree<T> *findByPath(const std::string &path) const;

    BinaryTree<T> *mergeImmutable(const BinaryTree<T> &other) const;
    void merge(const BinaryTree<T> &other);

    BinaryTree<T> operator+(const BinaryTree<T> &other) const;
    friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &tree);

public:
    using Iterator = BinaryTreeIterator<T>;
    using ConstIterator = ConstBinaryTreeIterator<T>;

    Iterator begin(std::string order = "inorder");
    Iterator end(std::string order = "inorder");
    ConstIterator cbegin(std::string order = "inorder") const;
    ConstIterator cend(std::string order = "inorder") const;

    ConstIterator cbegin(const TreeNode<T> *node, std::string order = "inorder") const;
    ConstIterator cend(const TreeNode<T> *node, std::string order = "inorder") const;

private:
    std::string threadedOrder;
};

#include "../impl/binaryTree.tpp"
