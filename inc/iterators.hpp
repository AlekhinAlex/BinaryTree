#pragma once

#include <vector>
#include <cstddef>
#include "treeNode.hpp"

template <typename T>
class BinaryTree;

template <typename T>
class BinaryTreeIterator
{
    friend class BinaryTree<T>;

public:
    using NodePtr = TreeNode<T> *;

    BinaryTreeIterator(NodePtr root, std::string order = "inorder");

    T &operator*();
    BinaryTreeIterator &operator++();
    BinaryTreeIterator operator++(int);
    BinaryTreeIterator &operator--();
    BinaryTreeIterator operator--(int);
    bool operator!=(const BinaryTreeIterator &other) const;
    bool operator==(const BinaryTreeIterator &other) const;

private:
    std::vector<NodePtr> nodes;
    size_t current;

    void buildInOrder(NodePtr node);
    void buildPreOrder(NodePtr node);
    void buildPostOrder(NodePtr node);
};

template <typename T>
class ConstBinaryTreeIterator
{
    friend class BinaryTree<T>;

public:
    using ConstNodePtr = const TreeNode<T> *;

    ConstBinaryTreeIterator(ConstNodePtr root, std::string order = "inorder");

    const T &operator*() const;
    ConstBinaryTreeIterator &operator++();
    ConstBinaryTreeIterator operator++(int);
    ConstBinaryTreeIterator &operator--();
    ConstBinaryTreeIterator operator--(int);
    bool operator!=(const ConstBinaryTreeIterator &other) const;
    bool operator==(const ConstBinaryTreeIterator &other) const;

private:
    std::vector<ConstNodePtr> nodes;
    size_t current;

    void buildInOrder(ConstNodePtr node);
    void buildPreOrder(ConstNodePtr node);
    void buildPostOrder(ConstNodePtr node);
};

#include "../impl/iterators.tpp"