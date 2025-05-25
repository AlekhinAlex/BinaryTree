#include "../inc/AVLTree.hpp"
#include <algorithm>

// Forward declaration to resolve circular dependency
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

    // Update heights
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

    // Update heights
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

    // Update height of this node
    node->setHeight(1 + std::max(getHeight(node->getLeft()), getHeight(node->getRight())));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && node->getLeft() && value < node->getLeft()->getData())
    {
        return rotateRight(node);
    }

    // Right Right Case
    if (balance < -1 && node->getRight() && value > node->getRight()->getData())
    {
        return rotateLeft(node);
    }

    // Left Right Case
    if (balance > 1 && node->getLeft() && value > node->getLeft()->getData())
    {
        return rotateLeftRight(node);
    }

    // Right Left Case
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
        // Node with only one child or no child
        if (!node->getLeft() || !node->getRight())
        {
            TreeNode<T> *temp = node->getLeft() ? node->getLeft() : node->getRight();
            if (!temp)
            {
                // No child case
                temp = node;
                node = nullptr;
            }
            else
            {
                // One child case
                // Copy the contents of the non-empty child
                node->setData(temp->getData());
                node->setLeft(temp->getLeft());
                node->setRight(temp->getRight());
            }
            delete temp;
        }
        else
        {
            // Node with two children
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

    // Update height
    node->setHeight(1 + std::max(getHeight(node->getLeft()), getHeight(node->getRight())));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && node->getLeft() && getBalance(node->getLeft()) >= 0)
    {
        return rotateRight(node);
    }

    // Left Right Case
    if (balance > 1 && node->getLeft() && getBalance(node->getLeft()) < 0)
    {
        return rotateLeftRight(node);
    }

    // Right Right Case
    if (balance < -1 && node->getRight() && getBalance(node->getRight()) <= 0)
    {
        return rotateLeft(node);
    }

    // Right Left Case
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