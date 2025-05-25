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
    isThreaded = false;
    TreeNode<T> *nodeToRemove = search(value);
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
    isThreaded = false;
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
    isThreaded = false;
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

    return nullptr;
}

template <typename T>
bool BinaryTree<T>::hasValue(const T &value) const
{
    return search(value) != nullptr;
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
    {
        return -1;
    }

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
    isThreaded = false;
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
    for (auto it = cbegin("inorder"); it != cend("inorder"); ++it)
    {
        os << *it << " ";
    }
}

template <typename T>
void BinaryTree<T>::inorderTraversal(const TreeNode<T> *node, std::ostream &os) const
{
    if (!node)
    {
        return;
    }

    for (auto it = cbegin(node, "inorder"); it != cend(node, "inorder"); ++it)
    {
        os << *it << " ";
    }
}

template <typename T>
void BinaryTree<T>::preorderTraversal(std::ostream &os) const
{
    for (auto it = cbegin("preorder"); it != cend("preorder"); ++it)
    {
        os << *it << " ";
    }
}

template <typename T>
void BinaryTree<T>::preorderTraversal(const TreeNode<T> *node, std::ostream &os) const
{
    if (!node)
    {
        return;
    }

    for (auto it = cbegin(node, "preorder"); it != cend(node, "preorder"); ++it)
    {
        os << *it << " ";
    }
}

template <typename T>
void BinaryTree<T>::postorderTraversal(std::ostream &os) const
{
    for (auto it = cbegin("postorder"); it != cend("postorder"); ++it)
    {
        os << *it << " ";
    }
}

template <typename T>
void BinaryTree<T>::postorderTraversal(const TreeNode<T> *node, std::ostream &os) const
{
    if (!node)
    {
        return;
    }

    for (auto it = cbegin(node, "postorder"); it != cend(node, "postorder"); ++it)
    {
        os << *it << " ";
    }
}

template <typename T>
const TreeNode<T> *BinaryTree<T>::getMaxNode() const
{
    if (!root)
    {
        return nullptr;
    }
    const TreeNode<T> *max = root;
    getMaxHelper(root, max);
    return max;
}

template <typename T>
TreeNode<T> *BinaryTree<T>::getMaxNode()
{
    if (!root)
    {
        return nullptr;
    }
    TreeNode<T> *max = root;
    getMaxHelper(root, max);
    return max;
}

template <typename T>
const T &BinaryTree<T>::getMax() const
{
    const TreeNode<T> *max = root;
    getMaxHelper(root, max);

    return max->getData();
}

template <typename T>
T &BinaryTree<T>::getMax()
{
    TreeNode<T> *max = root;
    getMaxHelper(root, max);

    return max->getData();
}

template <typename T>
void BinaryTree<T>::getMaxHelper(TreeNode<T> *node, TreeNode<T> *&max) const
{
    if (!node)
    {
        return;
    }
    if (node->getData() > max->getData())
    {
        max = node;
    }
    getMaxHelper(node->getLeft(), max);
    getMaxHelper(node->getRight(), max);
}

template <typename T>
const TreeNode<T> *BinaryTree<T>::getMinNode() const
{
    if (!root)
    {
        return nullptr;
    }
    const TreeNode<T> *min = root;
    getMinHelper(root, min);
    return min;
}

template <typename T>
TreeNode<T> *BinaryTree<T>::getMinNode()
{
    if (!root)
    {
        return nullptr;
    }
    TreeNode<T> *min = root;
    getMinHelper(root, min);
    return min;
}

template <typename T>
const T &BinaryTree<T>::getMin() const
{
    const TreeNode<T> *min = root;
    getMinHelper(root, min);

    return min->getData();
}

template <typename T>
T &BinaryTree<T>::getMin()
{
    TreeNode<T> *min = root;
    getMinHelper(root, min);

    return min->getData();
}

template <typename T>
void BinaryTree<T>::getMinHelper(TreeNode<T> *node, TreeNode<T> *&min) const
{
    if (!node)
    {
        return;
    }

    if (node->getData() < min->getData())
    {
        min = node;
    }
    getMinHelper(node->getLeft(), min);
    getMinHelper(node->getRight(), min);
}

template <typename T>
bool BinaryTree<T>::isBalanced() const
{
    return isBalancedHelper(root) != -1;
}

template <typename T>
int BinaryTree<T>::isBalancedHelper(const TreeNode<T> *node) const
{
    if (!node)
    {
        return 0;
    }

    int leftHeight = isBalancedHelper(node->getLeft());
    if (leftHeight == -1)
    {
        return -1;
    }

    int rightHeight = isBalancedHelper(node->getRight());
    if (rightHeight == -1)
    {
        return -1;
    }

    if (std::abs(leftHeight - rightHeight) > 1)
    {
        return -1;
    }

    return std::max(leftHeight, rightHeight) + 1;
}

template <typename T>
void BinaryTree<T>::inorderTraversal(TreeNode<T> *node, std::vector<TreeNode<T> *> &nodes)
{
    if (!node)
    {
        return;
    }
    inorderTraversal(node->getLeft(), nodes);
    nodes.push_back(node);
    inorderTraversal(node->getRight(), nodes);
}

template <typename T>
TreeNode<T> *BinaryTree<T>::buildBalancedTree(std::vector<TreeNode<T> *> &nodes, int start, int end)
{
    if (start > end)
    {
        return nullptr;
    }

    int mid = start + (end - start) / 2;
    TreeNode<T> *node = nodes[mid];
    node->getLeft() = buildBalancedTree(nodes, start, mid - 1);
    node->getRight() = buildBalancedTree(nodes, mid + 1, end);
    return node;
}

template <typename T>
void BinaryTree<T>::balance()
{
    if (!root)
        return;
    std::vector<TreeNode<T> *> nodes;
    inorderTraversal(root, nodes);
    root = buildBalancedTree(nodes, 0, nodes.size() - 1);
}

template <typename T>
BinaryTree<T> *BinaryTree<T>::subtree(const T &value) const
{
    const TreeNode<T> *node = search(value);
    if (!node)
    {
        throw std::runtime_error("Value not found in tree");
    }

    BinaryTree<T> *subtree = new BinaryTree<T>();
    subtree->root = node->clone();
    return subtree;
}

template <typename T>
bool BinaryTree<T>::operator==(const BinaryTree<T> &other) const
{
    if (this == &other)
    {
        return true;
    }
    if (!root || !other.root)
    {
        return root == other.root;
    }
    return *root == *other.root;
}

template <typename T>
bool BinaryTree<T>::operator!=(const BinaryTree<T> &other) const
{
    return !(*this == other);
}

template <typename T>
BinaryTree<T> &BinaryTree<T>::operator=(const BinaryTree<T> &other)
{
    if (this == &other)
    {
        return *this;
    }

    clear();
    if (other.root)
    {
        root = other.root->clone();
    }
    else
    {
        root = nullptr;
    }
    return *this;
}

template <typename T>
bool BinaryTree<T>::containsSubtree(const BinaryTree &other) const
{
    if (!other.root)
        return true;
    if (!root)
        return false;

    std::queue<const TreeNode<T> *> q;
    q.push(root);

    while (!q.empty())
    {
        const TreeNode<T> *current = q.front();
        q.pop();

        if (current->getData() == other.root->getData() && *current == *other.root)
        {
            return true;
        }

        if (current->getLeft())
            q.push(current->getLeft());
        if (current->getRight())
            q.push(current->getRight());
    }

    return false;
}

template <typename T>
void BinaryTree<T>::makeThreaded(const std::string &traversalOrder)
{
    if (!root)
    {
        return;
    }

    for (auto it = begin(); it != end(); ++it)
    {
        if (*it)
        {
            (*it)->clearThreads();
        }
    }

    std::vector<TreeNode<T> *> nodes;
    for (auto it = begin(traversalOrder); it != end(traversalOrder); ++it)
    {
        nodes.push_back(search(*it));
    }

    for (size_t i = 0; i < nodes.size(); i++)
    {
        if (!nodes[i]->getLeft())
        {
            if (i > 0)
            {
                nodes[i]->setLeftThread(nodes[i - 1]);
            }
        }

        if (!nodes[i]->getRight())
        {
            if (i < nodes.size() - 1)
            {
                nodes[i]->setRightThread(nodes[i + 1]);
            }
        }
    }

    isThreaded = true;
}

template <typename T>
void BinaryTree<T>::traverseThreaded(std::function<void(T)> visit) const
{
    if (!isThreaded)
    {
        throw std::logic_error("Tree is not threaded");
    }
    if (!root)
    {
        return;
    }
    TreeNode<T> *current = root;
    while (current && !current->hasLeftThread() && current->getLeft())
    {
        current = current->getLeft();
    }

    while (current)
    {
        visit(current->getData());

        if (current->hasRightThread())
        {
            current = current->getRight();
        }
        else
        {
            if (current->getRight())
            {
                current = current->getRight();
                while (!current->hasLeftThread() && current->getLeft())
                {
                    current = current->getLeft();
                }
            }
            else
            {
                current = nullptr;
            }
        }
    }
}

template <typename T>
void BinaryTree<T>::merge(const BinaryTree<T> &other)
{
    for (auto it = other.cbegin(); it != other.cend(); ++it)
    {
        this->insert(*it);
    }
}

template <typename T>
BinaryTree<T> *BinaryTree<T>::mergeImmutable(const BinaryTree<T> &other) const
{
    BinaryTree<T> *result = new BinaryTree<T>(*this);
    result->merge(other);
    return result;
}

template <typename T>
BinaryTree<T> BinaryTree<T>::operator+(const BinaryTree<T> &other) const
{
    return mergeImmutable(other);
}

template <typename T>
typename BinaryTree<T>::Iterator BinaryTree<T>::begin(std::string order)
{
    return Iterator(root, order);
}

template <typename T>
typename BinaryTree<T>::Iterator BinaryTree<T>::end(std::string order)
{
    Iterator it(nullptr, order);
    if (root)
    {
        it = Iterator(root, order);
        it.current = it.nodes.size();
    }
    return it;
}

template <typename T>
typename BinaryTree<T>::ConstIterator BinaryTree<T>::cbegin(std::string order) const
{
    return ConstIterator(root, order);
}

template <typename T>
typename BinaryTree<T>::ConstIterator BinaryTree<T>::cend(std::string order) const
{
    ConstIterator it(nullptr, order);
    if (root)
    {
        it = ConstIterator(root, order);
        it.current = it.nodes.size();
    }
    return it;
}

template <typename T>
BinaryTree<T> BinaryTree<T>::apply(std::function<T(T)> func) const
{
    BinaryTree<T> result;
    for (auto it = cbegin("preorder"); it != cend("preorder"); ++it)
    {
        result.insert(func(*it));
    }
    return result;
}

template <typename T>
BinaryTree<T> BinaryTree<T>::where(std::function<bool(T)> predicate) const
{
    BinaryTree<T> result;
    for (auto it = cbegin(); it != cend(); ++it)
    {
        if (predicate(*it))
        {
            result.insert(*it);
        }
    }
    return result;
}

template <typename T>
T BinaryTree<T>::reduce(std::function<T(T, T)> func, T initial) const
{
    T result = initial;
    for (auto it = cbegin(); it != cend(); ++it)
    {
        result = func(result, *it);
    }
    return result;
}

template <typename T>
std::string BinaryTree<T>::serialize(const std::string &traversalOrder) const
{
    std::vector<TreeNode<T> *> nodes;
    for (auto it = cbegin(traversalOrder); it != cend(traversalOrder); ++it)
    {
        nodes.push_back(*it);
    }

    std::string output = "{ \"threaded\": \"";

    if (traversalOrder == "preorder")
    {
        output += "Preorder: ";
    }
    else if (traversalOrder == "postorder")
    {
        output += "Postorder: ";
    }
    else
    {
        output += "Inorder: ";
    }

    for (const auto &node : nodes)
    {
        output += std::to_string(node->getData()) + " ";
    }

    output += "\" }";

    return output;
}

template <typename T>
void BinaryTree<T>::deserialize(const std::string &data, const std::string &format)
{
    clear();
    std::istringstream iss(data);
    std::string token;
    while (iss >> token)
    {
        if (token == "{")
        {
            continue;
        }
        else if (token == "}")
        {
            break;
        }
        else if (token == "null")
        {
            continue;
        }
        else
        {
            T value = static_cast<T>(std::stoi(token));
            insert(value);
        }
    }
    if (format == "inorder" || format == "preorder" || format == "postorder")
    {
        for (auto it = cbegin(format); it != cend(format); ++it)
        {
            insert(*it);
        }
    }
    else
    {
        throw std::invalid_argument("Unsupported format: " + format);
    }
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &tree)
{
    tree.print(os);
    return os;
}

template <typename T>
BinaryTree<T> *BinaryTree<T>::findByPath(const std::string &path) const
{
    TreeNode<T> *current = root;
    for (char dir : path)
    {
        if (!current)
            return nullptr;
        if (dir == 'L' || dir == 'l')
        {
            if (current->hasLeftThread())
                return nullptr;
            current = current->getLeft();
        }
        else if (dir == 'R' || dir == 'r')
        {
            if (current->hasRightThread())
                return nullptr;
            current = current->getRight();
        }
        else
        {
            return nullptr;
        }
    }
    if (!current)
    {
        return nullptr;
    }

    BinaryTree<T> *subtree = new BinaryTree<T>();
    subtree->root = current->clone();
    return subtree;
}