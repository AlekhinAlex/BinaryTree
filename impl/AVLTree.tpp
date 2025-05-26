#include "../inc/AVLTree.hpp"
#include <algorithm>

template <typename T>
class BinaryTree;

template <typename T>
int AVLTree<T>::getHeight(TreeNode<T> *node) const
{
    return node ? node->getHeight() : -1;
}

template <typename T>
int AVLTree<T>::getBalance(TreeNode<T> *node) const
{
    if (!node)
    {
        return 0;
    }
    return getHeight(node->getLeft()) - getHeight(node->getRight());
}

template <typename T>
TreeNode<T> *AVLTree<T>::rotateLeft(TreeNode<T> *x)
{
    TreeNode<T> *y = x->getRight();
    TreeNode<T> *T2 = y->getLeft();

    y->setLeft(x);
    x->setRight(T2);

    x->setHeight(1 + std::max(getHeight(x->getLeft()), getHeight(x->getRight())));
    y->setHeight(1 + std::max(getHeight(y->getLeft()), getHeight(y->getRight())));

    return y;
}

template <typename T>
TreeNode<T> *AVLTree<T>::rotateRight(TreeNode<T> *y)
{
    TreeNode<T> *x = y->getLeft();
    TreeNode<T> *T2 = x->getRight();

    x->setRight(y);
    y->setLeft(T2);

    y->setHeight(1 + std::max(getHeight(y->getLeft()), getHeight(y->getRight())));
    x->setHeight(1 + std::max(getHeight(x->getLeft()), getHeight(x->getRight())));

    return x;
}

template <typename T>
TreeNode<T> *AVLTree<T>::rotateLeftRight(TreeNode<T> *node)
{
    if (!node || !node->getLeft())
        return node;
    node->setLeft(rotateLeft(node->getLeft()));
    return rotateRight(node);
}

template <typename T>
TreeNode<T> *AVLTree<T>::rotateRightLeft(TreeNode<T> *node)
{
    if (!node || !node->getRight())
        return node;
    node->setRight(rotateRight(node->getRight()));
    return rotateLeft(node);
}

template <typename T>
TreeNode<T> *AVLTree<T>::insert(TreeNode<T> *node, const T &value)
{
    if (!node)
    {
        return new TreeNode<T>(value);
    }

    if (value < node->getData())
    {
        node->setLeft(insert(node->getLeft(), value));
    }
    else if (value > node->getData())
    {
        node->setRight(insert(node->getRight(), value));
    }
    else
    {
        return node;
    }

    node->setHeight(1 + std::max(getHeight(node->getLeft()), getHeight(node->getRight())));

    int balance = getBalance(node);

    if (balance > 1 && node->getLeft() && value < node->getLeft()->getData())
    {
        return rotateRight(node);
    }

    if (balance < -1 && node->getRight() && value > node->getRight()->getData())
    {
        return rotateLeft(node);
    }

    if (balance > 1 && node->getLeft() && value > node->getLeft()->getData())
    {
        return rotateLeftRight(node);
    }

    if (balance < -1 && node->getRight() && value < node->getRight()->getData())
    {
        return rotateRightLeft(node);
    }

    return node;
}

template <typename T>
void AVLTree<T>::insert(const T &value)
{
    this->isThreaded = false;
    updateRoot(insert(this->root, value));
}

template <typename T>
TreeNode<T> *AVLTree<T>::remove(TreeNode<T> *node, const T &value)
{
    if (!node)
    {
        return nullptr;
    }

    if (value < node->getData())
    {
        node->setLeft(remove(node->getLeft(), value));
    }
    else if (value > node->getData())
    {
        node->setRight(remove(node->getRight(), value));
    }
    else
    {
        if (!node->getLeft() || !node->getRight())
        {
            TreeNode<T> *temp = node->getLeft() ? node->getLeft() : node->getRight();
            if (!temp)
            {
                temp = node;
                node = nullptr;
            }
            else
            {
                node->setData(temp->getData());
                node->setLeft(temp->getLeft());
                node->setRight(temp->getRight());
            }
            delete temp;
        }
        else
        {
            TreeNode<T> *temp = node->getRight();
            while (temp->getLeft())
                temp = temp->getLeft();
            node->setData(temp->getData());
            node->setRight(remove(node->getRight(), temp->getData()));
        }
    }

    if (!node)
    {
        return nullptr;
    }

    node->setHeight(1 + std::max(getHeight(node->getLeft()), getHeight(node->getRight())));

    int balance = getBalance(node);

    if (balance > 1 && node->getLeft() && getBalance(node->getLeft()) >= 0)
    {
        return rotateRight(node);
    }

    if (balance > 1 && node->getLeft() && getBalance(node->getLeft()) < 0)
    {
        return rotateLeftRight(node);
    }

    if (balance < -1 && node->getRight() && getBalance(node->getRight()) <= 0)
    {
        return rotateLeft(node);
    }

    if (balance < -1 && node->getRight() && getBalance(node->getRight()) > 0)
    {
        return rotateRightLeft(node);
    }

    return node;
}

template <typename T>
void AVLTree<T>::remove(const T &value)
{
    updateRoot(remove(this->root, value));
    this->isThreaded = false;
}