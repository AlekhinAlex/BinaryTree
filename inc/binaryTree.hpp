#pragma once

#include "../inc/treeNode.hpp"

template <typename T>
class BinaryTree
{
private:
    TreeNode<T> *root;

public:
    BinaryTree();
    BinaryTree(const BinaryTree &other);
    ~BinaryTree();

    const TreeNode<T> *getRoot() const; //? Do I need this?
    TreeNode<T> *getRoot();

    void insert(const TreeNode<T> *root, const T &value);
    void insert(const T &value);
    void remove(const T &value);
    const TreeNode<T> *search(const T &value) const;
    bool hasValue(const T &value) const;

    void balance();

    void inorderTraversal() const;
    void preorderTraversal() const;
    void postorderTraversal() const;

    std::string toStringInorder() const;
    std::string toStringPreorder() const;
    std::string toStringPostorder() const;
    std::string toStringFormatted() const;

    TreeNode<T> *subtree(const T &value) const;
    bool containsSubtree(const BinaryTree &sub) const;

    int getHeight() const;
    int getHeightHelper(const TreeNode<T> *node) const;
    bool isEmpty() const;

    void clear();
};

#include "../impl/binaryTree.tpp"
