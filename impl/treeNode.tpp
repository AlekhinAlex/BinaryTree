#include "../inc/treeNode.hpp"

template <typename T>
TreeNode<T>::~TreeNode<T>()
{
    if (left)
    {
        delete left;
    }

    if (right)
    {
        delete right;
    }
}

template <typename T>
const T &TreeNode<T>::getData() const
{
    return data;
}

template <typename T>
T &TreeNode<T>::getData()
{
    return data;
}

template <typename T>
const TreeNode<T> *TreeNode<T>::getLeft() const
{
    return left;
}

template <typename T>
TreeNode<T> *TreeNode<T>::getLeft()
{
    return left;
}

template <typename T>
const TreeNode<T> *TreeNode<T>::getRight() const
{
    return right;
}

template <typename T>
TreeNode<T> *TreeNode<T>::getRight()
{
    return right;
}

template <typename T>
void TreeNode<T>::setData(T value)
{
    this->data = value;
}

template <typename T>
void TreeNode<T>::setLeft(TreeNode<T> *left)
{
    this->left = left;
}

template <typename T>
void TreeNode<T>::setRight(TreeNode<T> *right)
{
    this->right = right;
}

template <typename T>
bool TreeNode<T>::isLeaf() const
{
    return left == nullptr && right == nullptr;
}

template <typename T>
bool TreeNode<T>::hasChildren() const
{
    return left != nullptr || right != nullptr;
}

template <typename T>
TreeNode<T> *TreeNode<T>::clone() const
{
    TreeNode *newNode = new TreeNode(data);
    if (left)
    {
        newNode->left = left->clone();
    }
    if (right)
    {
        newNode->right = right->clone();
    }
    return newNode;
}
