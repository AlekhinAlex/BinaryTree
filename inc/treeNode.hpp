#pragma once

template <typename T>
class TreeNode
{
private:
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;

    bool isLeftThread;
    bool isRightThread;

    int height = 0;

public:
    TreeNode() : data(T()), left(nullptr), right(nullptr), isLeftThread(false), isRightThread(false), height(0) {}
    TreeNode(T value) : data(value), left(nullptr), right(nullptr), isLeftThread(false), isRightThread(false), height(0) {}

    ~TreeNode();

    TreeNode<T> *getParent(TreeNode<T> *root) const;

    const int getHeight() const;
    void setHeight(int h);

    const T &getData() const;
    T &getData();

    const TreeNode<T> *getLeft() const;
    TreeNode<T> *getLeft();

    const TreeNode<T> *getRight() const;
    TreeNode<T> *getRight();

    TreeNode<T> *getMax() const;
    TreeNode<T> *getMin() const;

    void setData(T value);
    void setLeft(TreeNode<T> *node);
    void setRight(TreeNode<T> *node);

    bool isLeaf() const;
    bool hasChildren() const;
    TreeNode<T> *clone() const;

    bool operator==(const TreeNode<T> &other) const;
    bool operator!=(const TreeNode<T> &other) const;
    bool operator<(const TreeNode<T> &other) const;
    bool operator>(const TreeNode<T> &other) const;
    TreeNode<T> &operator=(const TreeNode<T> &other);

public:
    bool hasLeftThread() const;
    bool hasRightThread() const;
    TreeNode<T> *getRightThread() const;
    void setLeftThread(TreeNode<T> *node);
    void setRightThread(TreeNode<T> *node);
    void clearThreads();
};

#include "../impl/treeNode.tpp"