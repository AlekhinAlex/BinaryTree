#include "../inc/iterators.hpp"

template <typename T>
void BinaryTreeIterator<T>::buildInOrder(NodePtr node)
{
    if (!node)
    {
        return;
    }
    buildInOrder(node->getLeft());
    nodes.push_back(node);
    buildInOrder(node->getRight());
}

template <typename T>
void BinaryTreeIterator<T>::buildPreOrder(NodePtr node)
{
    if (!node)
    {
        return;
    }
    nodes.push_back(node);
    buildPreOrder(node->getLeft());
    buildPreOrder(node->getRight());
}

template <typename T>
void BinaryTreeIterator<T>::buildPostOrder(NodePtr node)
{
    if (!node)
    {
        return;
    }
    buildPostOrder(node->getLeft());
    buildPostOrder(node->getRight());
    nodes.push_back(node);
}

template <typename T>
BinaryTreeIterator<T>::BinaryTreeIterator(NodePtr root, std::string order) : current(0)
{
    if (root)
    {
        if (order == "preorder")
        {
            buildPreOrder(root);
        }
        else if (order == "postorder")
        {
            buildPostOrder(root);
        }
        else
        {
            buildInOrder(root);
        }
    }
}

template <typename T>
T &BinaryTreeIterator<T>::operator*()
{
    if (nodes.empty() || current >= nodes.size())
    {
        throw std::out_of_range("BinaryTreeIterator dereference out of range");
    }
    return nodes[current]->getData();
}

template <typename T>
BinaryTreeIterator<T> &BinaryTreeIterator<T>::operator++()
{
    ++current;
    return *this;
}

template <typename T>
BinaryTreeIterator<T> BinaryTreeIterator<T>::operator++(int)
{
    BinaryTreeIterator<T> temp = *this;
    ++current;
    return temp;
}

template <typename T>
BinaryTreeIterator<T> &BinaryTreeIterator<T>::operator--()
{
    if (current > 0)
    {
        --current;
    }
    return *this;
}

template <typename T>
BinaryTreeIterator<T> BinaryTreeIterator<T>::operator--(int)
{
    BinaryTreeIterator<T> temp = *this;
    if (current > 0)
    {
        --current;
    }
    return temp;
}

template <typename T>
bool BinaryTreeIterator<T>::operator!=(const BinaryTreeIterator<T> &other) const
{
    if (nodes.empty() && other.nodes.empty())
    {
        return false;
    }
    if (nodes.empty() || other.nodes.empty())
    {
        return true;
    }
    return current != other.current;
}

template <typename T>
bool BinaryTreeIterator<T>::operator==(const BinaryTreeIterator<T> &other) const
{
    return !(*this != other);
}

// ConstBinaryTreeIterator implementation

template <typename T>
void ConstBinaryTreeIterator<T>::buildInOrder(ConstNodePtr node)
{
    if (!node)
    {
        return;
    }
    buildInOrder(node->getLeft());
    nodes.push_back(node);
    buildInOrder(node->getRight());
}

template <typename T>
void ConstBinaryTreeIterator<T>::buildPreOrder(ConstNodePtr node)
{
    if (!node)
    {
        return;
    }
    nodes.push_back(node);
    buildPreOrder(node->getLeft());
    buildPreOrder(node->getRight());
}

template <typename T>
void ConstBinaryTreeIterator<T>::buildPostOrder(ConstNodePtr node)
{
    if (!node)
    {
        return;
    }
    buildPostOrder(node->getLeft());
    buildPostOrder(node->getRight());
    nodes.push_back(node);
}

template <typename T>
ConstBinaryTreeIterator<T>::ConstBinaryTreeIterator(ConstNodePtr root, std::string order) : current(0)
{
    if (root)
    {
        if (order == "preorder")
        {
            buildPreOrder(root);
        }
        else if (order == "postorder")
        {
            buildPostOrder(root);
        }
        else
        {
            buildInOrder(root);
        }
    }
}

template <typename T>
const T &ConstBinaryTreeIterator<T>::operator*() const
{
    if (nodes.empty() || current >= nodes.size())
    {
        throw std::out_of_range("ConstBinaryTreeIterator dereference out of range");
    }
    return nodes[current]->getData();
}

template <typename T>
ConstBinaryTreeIterator<T> &ConstBinaryTreeIterator<T>::operator++()
{
    ++current;
    return *this;
}

template <typename T>
ConstBinaryTreeIterator<T> ConstBinaryTreeIterator<T>::operator++(int)
{
    ConstBinaryTreeIterator<T> temp = *this;
    ++current;
    return temp;
}

template <typename T>
ConstBinaryTreeIterator<T> &ConstBinaryTreeIterator<T>::operator--()
{
    if (current > 0)
    {
        --current;
    }
    return *this;
}

template <typename T>
ConstBinaryTreeIterator<T> ConstBinaryTreeIterator<T>::operator--(int)
{
    ConstBinaryTreeIterator<T> temp = *this;
    if (current > 0)
    {
        --current;
    }
    return temp;
}

template <typename T>
bool ConstBinaryTreeIterator<T>::operator!=(const ConstBinaryTreeIterator<T> &other) const
{
    if (nodes.empty() && other.nodes.empty())
    {
        return false;
    }
    if (nodes.empty() || other.nodes.empty())
    {
        return true;
    }
    return current != other.current;
}

template <typename T>
bool ConstBinaryTreeIterator<T>::operator==(const ConstBinaryTreeIterator<T> &other) const
{
    return !(*this != other);
}
