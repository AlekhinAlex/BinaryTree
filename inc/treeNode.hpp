#pragma once

template <typename T>
class TreeNode
{
private:
    T data;
    TreeNode *left;
    TreeNode *right;

public:
    TreeNode() : data(T()), left(nullptr), right(nullptr) {}
    TreeNode(T value) : data(value), left(nullptr), right(nullptr) {}
    ~TreeNode();

    const T &getData() const;
    T &getData();

    const TreeNode *getLeft() const;
    TreeNode *getLeft();

    const TreeNode *getRight() const;
    TreeNode *getRight();

    TreeNode *getMax() const;
    TreeNode *getMin() const;

    void setData(T value);
    void setLeft(TreeNode *node);
    void setRight(TreeNode *node);

    bool isLeaf() const;
    bool hasChildren() const;
    TreeNode *clone() const;
};

#include "../impl/treeNode.tpp"