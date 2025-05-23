#include "../inc/binaryTree.hpp"
#include <queue>

template <typename T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> &other)
{
    root = other.root ? other.root->clone() : nullptr;
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
    clear();
}

template <typename T>
TreeNode<T> *BinaryTree<T>::getRoot()
{
    return root;
}

template <typename T>
const TreeNode<T> *BinaryTree<T>::getRoot() const
{
    return root;
}

template <typename T>
void BinaryTree<T>::insert(const T &value)
{
    if (!root)
    {
        root = new TreeNode<T>(value);
        return;
    }

    std::queue<TreeNode<T> *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode<T> *current = q.front();
        q.pop();

        if (!current->getLeft())
        {
            current->setLeft(new TreeNode<T>(value));
            return;
        }
        else
        {
            q.push(current->getLeft());
        }

        if (!current->getRight())
        {
            current->setRight(new TreeNode<T>(value));
            return;
        }
        else
        {
            q.push(current->getRight());
        }
    }
}

template <typename T>
void BinaryTree<T>::insert(const TreeNode<T> *startingRoot, const T &value)
{
    if (!startingRoot)
    {
        if (!root)
        {
            root = new TreeNode<T>(value);
        }
        return;
    }

    std::queue<TreeNode<T> *> q;
    q.push(startingRoot);

    while (!q.empty())
    {
        TreeNode<T> *current = q.front();
        q.pop();

        if (!current->getLeft())
        {
            current->setLeft(new TreeNode<T>(value));
            return;
        }
        else
        {
            q.push(current->getLeft());
        }

        if (!current->getRight())
        {
            current->setRight(new TreeNode<T>(value));
            return;
        }
        else
        {
            q.push(current->getRight());
        }
    }
}

template <typename T>
const TreeNode<T> *BinaryTree<T>::search(const T &value) const
{
    if (!root)
        return nullptr;

    std::queue<TreeNode<T> *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode<T> *temp = q.front();
        q.pop();

        if (temp->getData() == value)
            return temp;

        if (temp->getLeft())
            q.push(temp->getLeft());

        if (temp->getRight())
            q.push(temp->getRight());
    }

    return nullptr;
}

template <typename T>
int BinaryTree<T>::getHeight() const
{
    return getHeightHelper(root);
}

template <typename T>
int BinaryTree<T>::getHeightHelper(const TreeNode<T> *node) const
{
    if (node == nullptr)
        return -1;

    int leftHeight = getHeightHelper(node->getLeft());
    int rightHeight = getHeightHelper(node->getRight());

    return std::max(leftHeight, rightHeight) + 1;
}

template <typename T>
bool BinaryTree<T>::isEmpty() const
{
    return root == nullptr;
}

template <typename T>
void BinaryTree<T>::clear()
{
    if (root)
    {
        delete root;
        root = nullptr;
    }
}
