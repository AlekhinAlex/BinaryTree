#pragma once
#include "binaryTree.hpp"

template <typename T>
class AVLTree : public BinaryTree<T>
{
public:
    AVLTree() : BinaryTree<T>() {}
    AVLTree(const AVLTree &other) : BinaryTree<T>(other) {}
    ~AVLTree() { this->clear(); }

    void insert(const T &value) override;
    void remove(const T &value) override;
    bool isBalanced() const override { return true; }
    int getHeight(TreeNode<T> *node) const;

private:
    TreeNode<T> *insert(TreeNode<T> *node, const T &value);
    TreeNode<T> *remove(TreeNode<T> *node, const T &value);

    int getBalance(TreeNode<T> *node) const;

    TreeNode<T> *rotateLeft(TreeNode<T> *x);
    TreeNode<T> *rotateRight(TreeNode<T> *y);
    TreeNode<T> *rotateLeftRight(TreeNode<T> *node);
    TreeNode<T> *rotateRightLeft(TreeNode<T> *node);

    void updateRoot(TreeNode<T> *newRoot) { this->root = newRoot; }
};

#include "../impl/AVLTree.tpp"