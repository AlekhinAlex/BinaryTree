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
TreeNode<T> *BinaryTree<T>::findParent(TreeNode<T> *node) const
{
    if (!root || !node || node == root)
    {
        return nullptr;
    }

    std::queue<TreeNode<T> *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode<T> *current = q.front();
        q.pop();

        if (current->getLeft() == node || current->getRight() == node)
        {
            return current;
        }

        if (current->getLeft())
        {
            q.push(current->getLeft());
        }

        if (current->getRight())
        {
            q.push(current->getRight());
        }
    }

    return nullptr;
}

template <typename T>
void BinaryTree<T>::remove(const T &value)
{
    TreeNode<T> *nodeToRemove = this->search(value);
    if (!nodeToRemove)
    {
        throw std::runtime_error("Value not found");
    }

    // Find the deepest rightmost node
    std::queue<TreeNode<T> *> q;
    TreeNode<T> *temp = nullptr;
    q.push(root);
    while (!q.empty())
    {
        temp = q.front();
        q.pop();
        if (temp->getLeft() != nullptr)
        {
            q.push(temp->getLeft());
        }
        if (temp->getRight() != nullptr)
        {
            q.push(temp->getRight());
        }
    }

    // Find parent of the deepest node
    TreeNode<T> *parent = findParent(temp);

    if (nodeToRemove == temp)
    {
        if (parent)
        {
            if (parent->getLeft() == temp)
            {
                parent->setLeft(nullptr);
            }
            else
            {
                parent->setRight(nullptr);
            }
        }
        else
        {
            root = nullptr;
        }

        temp->setLeft(nullptr);
        temp->setRight(nullptr);
        delete temp;
        return;
    }

    T dataDeepestRight = temp->getData();

    if (parent)
    {
        if (parent->getLeft() == temp)
        {
            parent->setLeft(nullptr);
        }
        else
        {
            parent->setRight(nullptr);
        }
    }

    nodeToRemove->setData(dataDeepestRight);
    temp->setLeft(nullptr);
    temp->setRight(nullptr);
    delete temp;
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
void BinaryTree<T>::insert(const T &value, TreeNode<T> *startingRoot)
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
    {
        return nullptr;
    }

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
TreeNode<T> *BinaryTree<T>::search(const T &value)
{
    if (!root)
    {
        return nullptr;
    }

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

    throw std::runtime_error("Value not found in tree");
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

template <typename T>
void BinaryTree<T>::print(std::ostream &os) const
{
    if (!root)
    {
        os << "Empty tree" << std::endl;
        return;
    }

    std::queue<const TreeNode<T> *> q;
    q.push(root);

    int level = 0;
    int nodesInCurrentLevel = 1;
    int nodesInNextLevel = 0;

    os << "Level " << level << ": ";

    while (!q.empty())
    {
        const TreeNode<T> *current = q.front();
        q.pop();
        nodesInCurrentLevel--;

        if (current)
        {
            os << current->getData() << " ";
            q.push(current->getLeft());
            q.push(current->getRight());
            nodesInNextLevel += 2;
        }
        else
        {
            os << "null ";
            q.push(nullptr);
            q.push(nullptr);
        }

        if (nodesInCurrentLevel == 0)
        {
            os << std::endl;
            level++;
            nodesInCurrentLevel = nodesInNextLevel;
            nodesInNextLevel = 0;

            // Stop if the next level has only null nodes
            bool hasNonNullNode = false;
            for (size_t i = 0; i < q.size(); i++)
            {
                const TreeNode<T> *node = q.front();
                q.pop();
                if (node)
                {
                    hasNonNullNode = true;
                }
                q.push(node);
            }

            if (!hasNonNullNode)
            {
                break;
            }

            os << "Level " << level << ": ";
        }
    }
}

template <typename T>
void BinaryTree<T>::inorderTraversal(std::ostream &os) const
{
    inorderTraversal(root, os);
}

template <typename T>
void BinaryTree<T>::inorderTraversal(const TreeNode<T> *node, std::ostream &os) const
{
    if (!node)
    {
        return;
    }

    inorderTraversal(node->getLeft(), os);
    os << node->getData() << " ";
    inorderTraversal(node->getRight(), os);
}

template <typename T>
void BinaryTree<T>::preorderTraversal(std::ostream &os) const
{
    preorderTraversal(root, os);
}

template <typename T>
void BinaryTree<T>::preorderTraversal(const TreeNode<T> *node, std::ostream &os) const
{
    if (!node)
    {
        return;
    }

    os << node->getData() << " ";
    preorderTraversal(node->getLeft(), os);
    preorderTraversal(node->getRight(), os);
}

template <typename T>
void BinaryTree<T>::postorderTraversal(std::ostream &os) const
{
    postorderTraversal(root, os);
}

template <typename T>
void BinaryTree<T>::postorderTraversal(const TreeNode<T> *node, std::ostream &os) const
{
    if (!node)
    {
        return;
    }

    postorderTraversal(node->getLeft(), os);
    postorderTraversal(node->getRight(), os);
    os << node->getData() << " ";
}
