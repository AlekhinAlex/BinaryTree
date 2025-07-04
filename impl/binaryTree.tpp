#include "../inc/binaryTree.hpp"
#include <queue>
#include <sstream>
#include <algorithm>
#include <typeinfo>
#include <unordered_set>

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
        return nullptr;

    return node->getParent(root);
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
    if (isThreaded)
    {
        std::queue<TreeNode<T> *> q;
        if (root)
        {
            q.push(root);
            while (!q.empty())
            {
                TreeNode<T> *current = q.front();
                q.pop();

                TreeNode<T> *leftChild = current->hasLeftThread() ? nullptr : current->getLeft();
                TreeNode<T> *rightChild = current->hasRightThread() ? nullptr : current->getRight();

                current->clearThreads();

                if (leftChild)
                    q.push(leftChild);
                if (rightChild)
                    q.push(rightChild);
            }
        }
        isThreaded = false;
    }

    if (!root)
    {
        root = new TreeNode<T>(value);
        return;
    }

    TreeNode<T> *current = root;
    while (true)
    {
        if (value < current->getData())
        {
            if (!current->getLeft())
            {
                current->setLeft(new TreeNode<T>(value));
                return;
            }
            current = current->getLeft();
        }
        else
        {
            if (!current->getRight())
            {
                current->setRight(new TreeNode<T>(value));
                return;
            }
            current = current->getRight();
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

    if (root->getData() == value)
    {
        return root;
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
    return root ? root->getHeight() : throw std::runtime_error("Tree is empty");
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
        }

        if (nodesInCurrentLevel == 0)
        {
            os << std::endl;
            level++;
            nodesInCurrentLevel = nodesInNextLevel;
            nodesInNextLevel = 0;

            if (nodesInCurrentLevel == 0)
                break;

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
    if (!root)
    {
        throw std::runtime_error("Tree is empty");
    }
    const TreeNode<T> *max = root;
    getMaxHelper(root, max);

    return max->getData();
}

template <typename T>
T &BinaryTree<T>::getMax()
{
    if (!root)
    {
        throw std::runtime_error("Tree is empty");
    }
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
    if (!root)
    {
        throw std::runtime_error("Tree is empty");
    }
    const TreeNode<T> *min = root;
    getMinHelper(root, min);

    return min->getData();
}

template <typename T>
T &BinaryTree<T>::getMin()
{
    if (!root)
    {
        throw std::runtime_error("Tree is empty");
    }
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
        return 0;
    int lh = isBalancedHelper(node->getLeft());
    if (lh == -1)
        return -1;
    int rh = isBalancedHelper(node->getRight());
    if (rh == -1)
        return -1;
    if (std::abs(lh - rh) > 1)
        return -1;
    return 1 + std::max(lh, rh);
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
    node->setLeft(buildBalancedTree(nodes, start, mid - 1));
    node->setRight(buildBalancedTree(nodes, mid + 1, end));
    return node;
}

template <typename T>
TreeNode<T> *BinaryTree<T>::buildBalancedTreeFromValues(const std::vector<T> &values, int start, int end)
{
    if (start > end)
        return nullptr;
    int mid = start + (end - start) / 2;
    TreeNode<T> *node = new TreeNode<T>(values[mid]);
    node->setLeft(buildBalancedTreeFromValues(values, start, mid - 1));
    node->setRight(buildBalancedTreeFromValues(values, mid + 1, end));
    return node;
}

template <typename T>
void BinaryTree<T>::balance()
{
    if (!root)
        return;
    std::vector<T> values;
    std::function<void(TreeNode<T> *)> inorder = [&](TreeNode<T> *node)
    {
        if (!node)
            return;
        inorder(node->getLeft());
        values.push_back(node->getData());
        inorder(node->getRight());
    };
    inorder(root);
    clear();
    root = buildBalancedTreeFromValues(values, 0, values.size() - 1);
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
        isThreaded = true;
        threadedOrder = traversalOrder;
        return;
    }

    std::queue<TreeNode<T> *> q;
    q.push(root);
    while (!q.empty())
    {
        TreeNode<T> *current = q.front();
        q.pop();
        current->clearThreads();
        if (current->getLeft())
        {
            q.push(current->getLeft());
        }
        if (current->getRight())
        {
            q.push(current->getRight());
        }
    }

    std::vector<TreeNode<T> *> nodes;
    if (traversalOrder == "preorder")
    {
        std::function<void(TreeNode<T> *)> preorder = [&](TreeNode<T> *node)
        {
            if (!node)
                return;
            nodes.push_back(node);
            if (!node->hasLeftThread())
                preorder(node->getLeft());
            if (!node->hasRightThread())
                preorder(node->getRight());
        };
        preorder(root);
    }
    else if (traversalOrder == "postorder")
    {
        std::function<void(TreeNode<T> *)> postorder = [&](TreeNode<T> *node)
        {
            if (!node)
                return;
            if (!node->hasLeftThread())
                postorder(node->getLeft());
            if (!node->hasRightThread())
                postorder(node->getRight());
            nodes.push_back(node);
        };
        postorder(root);
    }
    else
    {
        std::function<void(TreeNode<T> *)> inorder = [&](TreeNode<T> *node)
        {
            if (!node)
            {
                return;
            }
            if (!node->hasLeftThread())
            {
                inorder(node->getLeft());
            }
            nodes.push_back(node);
            if (!node->hasRightThread())
            {
                inorder(node->getRight());
            }
        };
        inorder(root);
    }

    for (size_t i = 0; i < nodes.size() - 1; i++)
    {
        if (!nodes[i]->getRight() || nodes[i]->hasRightThread())
        {
            nodes[i]->setRightThread(nodes[i + 1]);
        }
    }

    isThreaded = true;
    threadedOrder = traversalOrder;
}

template <typename T>
void BinaryTree<T>::traverseThreaded(std::function<void(T)> visit) const
{
    if (!isThreaded)
        throw std::logic_error("Tree is not threaded");
    if (!root)
        return;

    TreeNode<T> *current = const_cast<TreeNode<T> *>(root);

    if (threadedOrder == "inorder")
    {
        while (current && current->getLeft() && !current->hasLeftThread())
            current = current->getLeft();

        while (current)
        {
            visit(current->getData());

            if (current->hasRightThread())
                current = current->getRightThread();
            else
            {
                current = current->getRight();
                while (current && current->getLeft() && !current->hasLeftThread())
                    current = current->getLeft();
            }
        }
    }
    else if (threadedOrder == "preorder")
    {
        while (current)
        {
            visit(current->getData());

            if (current->getLeft() && !current->hasLeftThread())
                current = current->getLeft();
            else if (current->hasRightThread())
                current = current->getRightThread();
            else
                current = current->getRight();
        }
    }
    else if (threadedOrder == "postorder")
    {
        std::vector<TreeNode<T> *> nodes;
        std::function<void(TreeNode<T> *)> collectNodes = [&](TreeNode<T> *node)
        {
            if (!node)
                return;
            if (!node->hasLeftThread())
                collectNodes(node->getLeft());
            if (!node->hasRightThread())
                collectNodes(node->getRight());
            nodes.push_back(node);
        };
        collectNodes(const_cast<TreeNode<T> *>(root));

        for (auto node : nodes)
        {
            visit(node->getData());
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
    BinaryTree<T> result(*this);
    result.merge(other);
    return result;
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
    // For level-order traversal (needed for visualization)
    std::vector<T> values;
    std::vector<bool> isNull;

    if (!root)
    {
        std::string output = "{\n";
        output += "  \"type\": \"binary_tree\",\n";
        output += "  \"traversal\": \"" + traversalOrder + "\",\n";
        output += "  \"values\": [],\n";
        output += "  \"size\": 0,\n";
        output += "  \"isThreaded\": " + std::string(isThreaded ? "true" : "false") + "\n";
        output += "}";
        return output;
    }

    // Use level-order traversal for visualization
    std::queue<TreeNode<T> *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode<T> *current = q.front();
        q.pop();

        if (current)
        {
            values.push_back(current->getData());
            isNull.push_back(false);

            q.push(current->getLeft());
            q.push(current->getRight());
        }
        else
        {
            values.push_back(T());
            isNull.push_back(true);
        }
    }

    // Remove trailing nulls
    while (!values.empty() && isNull.back())
    {
        values.pop_back();
        isNull.pop_back();
    }

    std::string output = "{\n";
    output += "  \"type\": \"binary_tree\",\n";
    output += "  \"traversal\": \"" + traversalOrder + "\",\n";
    output += "  \"values\": [";

    for (size_t i = 0; i < values.size(); i++)
    {
        if (isNull[i])
        {
            output += "\"null\"";
        }
        else
        {
            std::stringstream ss;
            ss << values[i];
            output += "\"" + ss.str() + "\"";
        }

        if (i < values.size() - 1)
        {
            output += ", ";
        }
    }

    output += "],\n";
    output += "  \"size\": " + std::to_string(values.size()) + ",\n";
    output += "  \"isThreaded\": " + std::string(isThreaded ? "true" : "false") + "\n";
    output += "}";

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
            T value;
            std::istringstream tokenStream(token);
            tokenStream >> value;
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
    if (!root || path.empty())
        return nullptr;

    TreeNode<T> *current = root;
    for (char direction : path)
    {
        if (direction == 'L')
        {
            if (!current->getLeft())
                return nullptr;
            current = current->getLeft();
        }
        else if (direction == 'R')
        {
            if (!current->getRight())
                return nullptr;
            current = current->getRight();
        }
        else
        {
            return nullptr;
        }
    }

    BinaryTree<T> *subtree = new BinaryTree<T>();
    subtree->root = current->clone();

    return subtree;
}

template <typename T>
typename BinaryTree<T>::ConstIterator BinaryTree<T>::cbegin(const TreeNode<T> *node, std::string order) const
{
    return ConstIterator(node, order);
}

template <typename T>
typename BinaryTree<T>::ConstIterator BinaryTree<T>::cend(const TreeNode<T> *node, std::string order) const
{
    ConstIterator it(nullptr, order);
    if (node)
    {
        it = ConstIterator(node, order);
        it.current = it.nodes.size();
    }
    return it;
}