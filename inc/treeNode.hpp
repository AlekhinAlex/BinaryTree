#pragma once

template <typename T>
class TreeNode
{
private:
    T data;
    TreeNode *left;
    TreeNode *right;

    bool isLeftThread;
    bool isRightThread;

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

    bool operator==(const TreeNode &other) const;
    bool operator!=(const TreeNode &other) const;
    bool operator<(const TreeNode &other) const;
    bool operator>(const TreeNode &other) const;
    TreeNode &operator=(const TreeNode &other);

public:
    bool hasLeftThread() const;
    bool hasRightThread() const;
    void setLeftThread(TreeNode *node);
    void setRightThread(TreeNode *node);
    void clearThreads();
};

#include "../impl/treeNode.tpp"