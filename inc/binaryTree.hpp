#pragma once

#include "../inc/treeNode.hpp"
#include <iostream>

template <typename T>
class BinaryTree
{
private:
    TreeNode<T> *root;

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
    void insert(const T &value);

    void remove(const T &value);

    const TreeNode<T> *search(const T &value) const;
    TreeNode<T> *search(const T &value);

    TreeNode<T> *findParent(TreeNode<T> *node) const;

    //? MB remake for convinient printing into app
    void print(std::ostream &os = std::cout) const;

    bool hasValue(const T &value) const;

    void balance();

    // L - root - R
    void inorderTraversal(std::ostream &os = std::cout) const;
    void inorderTraversal(const TreeNode<T> *node, std::ostream &os = std::cout) const;

    // root - L - R
    void preorderTraversal(std::ostream &os = std::cout) const;
    void preorderTraversal(const TreeNode<T> *node, std::ostream &os = std::cout) const;

    // L - R - root
    void postorderTraversal(std::ostream &os = std::cout) const;
    void postorderTraversal(const TreeNode<T> *node, std::ostream &os = std::cout) const;

    TreeNode<T> *subtree(const T &value) const;
    bool containsSubtree(const BinaryTree &sub) const;

    int getHeight() const;
    int getHeightHelper(const TreeNode<T> *node) const;
    bool isEmpty() const;

    void clear();
};

#include "../impl/binaryTree.tpp"
