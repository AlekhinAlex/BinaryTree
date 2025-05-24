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

template <typename T>
bool TreeNode<T>::operator==(const TreeNode &other) const
{

    if (data != other.data)
    {
        return false;
    }

    if ((left == nullptr) != (other.left == nullptr))
    {
        return false;
    }
    if (left && !(*left == *other.left))
    {
        return false;
    }

    if ((right == nullptr) != (other.right == nullptr))
    {
        return false;
    }
    if (right && !(*right == *other.right))
    {
        return false;
    }

    return true;
}

template <typename T>
bool TreeNode<T>::operator!=(const TreeNode &other) const
{
    return !(*this == other);
}
template <typename T>
bool TreeNode<T>::operator<(const TreeNode &other) const
{
    return data < other.data;
}
template <typename T>
bool TreeNode<T>::operator>(const TreeNode &other) const
{
    return data > other.data;
}
template <typename T>
TreeNode<T> &TreeNode<T>::operator=(const TreeNode &other)
{
    if (this != &other)
    {
        TreeNode<T> *newLeft = other.left ? other.left->clone() : nullptr;
        TreeNode<T> *newRight = other.right ? other.right->clone() : nullptr;

        delete left;
        delete right;

        data = other.data;
        left = newLeft;
        right = newRight;
    }
    return *this;
}
