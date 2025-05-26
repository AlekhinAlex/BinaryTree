#include "../inc/treeNode.hpp"
#include <algorithm>
#include <stdexcept>

template <typename T>
TreeNode<T>::~TreeNode<T>()
{
    if (left && !isLeftThread)
    {
        delete left;
    }
    if (right && !isRightThread)
    {
        delete right;
    }
}

template <typename T>
const int TreeNode<T>::getHeight() const
{
    return height;
}

template <typename T>
void TreeNode<T>::setHeight(int h)
{
    height = h;
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
    isLeftThread = false;
    height = 1 + std::max(
                     left ? left->height : -1,
                     right ? right->height : -1);
}

template <typename T>
void TreeNode<T>::setRight(TreeNode<T> *right)
{
    this->right = right;
    isRightThread = false;
    height = 1 + std::max(
                     left ? left->height : -1,
                     right ? right->height : -1);
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
    newNode->height = this->height;
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

template <typename T>
bool TreeNode<T>::hasLeftThread() const
{
    return isLeftThread;
}

template <typename T>
bool TreeNode<T>::hasRightThread() const
{
    return isRightThread;
}

template <typename T>
void TreeNode<T>::setLeftThread(TreeNode *node)
{
    left = node;
    isLeftThread = true;
}

template <typename T>
void TreeNode<T>::setRightThread(TreeNode *node)
{
    right = node;
    isRightThread = true;
}

template <typename T>
void TreeNode<T>::clearThreads()
{
    isLeftThread = false;
    isRightThread = false;
}

template <typename T>
TreeNode<T> *TreeNode<T>::getParent(TreeNode<T> *root) const
{
    if (!root)
        return nullptr;

    TreeNode<T> *current = root;
    TreeNode<T> *parent = nullptr;

    while (current && current != this)
    {
        parent = current;
        if (this->data < current->data)
            current = current->getLeft();
        else
            current = current->getRight();
    }

    return (current == this) ? parent : nullptr;
}

template <typename T>
TreeNode<T> *TreeNode<T>::getRightThread() const
{
    if (!isRightThread)
    {
        throw std::logic_error("This node does not have a right thread.");
    }
    return right;
}