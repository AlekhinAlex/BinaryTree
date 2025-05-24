#pragma once

#include "treeNode.hpp"
#include "iterators.hpp"
#include <iostream>
#include <vector>
#include <functional>

template <typename T>
class BinaryTree
{
private:
    TreeNode<T> *root;

    TreeNode<T> *applyHelper(const TreeNode<T> *node, std::function<T(T)> func) const;
    TreeNode<T> *whereHelper(const TreeNode<T> *node, std::function<bool(T)> predicate) const;
    void threadedTraversalHelper(TreeNode<T> *node, std::vector<TreeNode<T> *> &nodes, const std::string &order);
    void serializeHelper(const TreeNode<T> *node, std::ostream &os, const std::string &format) const;
    TreeNode<T> *deserializeHelper(std::istream &is, const std::string &format);
    bool containsSubtreeHelper(const TreeNode<T> *treeNode, const TreeNode<T> *subNode) const;

public:
    BinaryTree();
    BinaryTree(const BinaryTree &other);
    ~BinaryTree();

    const TreeNode<T> *getRoot() const;
    TreeNode<T> *getRoot();

    const TreeNode<T> *getMaxNode() const;
    TreeNode<T> *getMaxNode();
    const T &getMax() const;
    T &getMax();
    void getMaxHelper(TreeNode<T> *node, TreeNode<T> *&max) const;

    const TreeNode<T> *getMinNode() const;
    TreeNode<T> *getMinNode();
    const T &getMin() const;
    T &getMin();
    void getMinHelper(TreeNode<T> *node, TreeNode<T> *&min) const;

    void insert(const T &value, TreeNode<T> *root); //? Do I need this
    void insert(const T &value);

    void remove(const T &value);

    const TreeNode<T> *search(const T &value) const;
    TreeNode<T> *search(const T &value);

    TreeNode<T> *findParent(TreeNode<T> *node) const;

    //? MB remake for convinient printing into app
    void print(std::ostream &os = std::cout) const;

    bool hasValue(const T &value) const;

    void balance();
    void inorderTraversal(TreeNode<T> *node, std::vector<TreeNode<T> *> &nodes);
    TreeNode<T> *buildBalancedTree(std::vector<TreeNode<T> *> &nodes, int start, int end);
    bool isBalanced() const;
    int isBalancedHelper(const TreeNode<T> *node) const;

    // L - root - R
    void inorderTraversal(std::ostream &os = std::cout) const;
    void inorderTraversal(const TreeNode<T> *node, std::ostream &os = std::cout) const;

    // root - L - R
    void preorderTraversal(std::ostream &os = std::cout) const;
    void preorderTraversal(const TreeNode<T> *node, std::ostream &os = std::cout) const;

    // L - R - root
    void postorderTraversal(std::ostream &os = std::cout) const;
    void postorderTraversal(const TreeNode<T> *node, std::ostream &os = std::cout) const;

    BinaryTree<T> *subtree(const T &value) const;
    bool containsSubtree(const BinaryTree &sub) const;

    int getHeight() const;
    int getHeightHelper(const TreeNode<T> *node) const;
    bool isEmpty() const;

    void clear();

    bool operator==(const BinaryTree<T> &other) const;
    bool operator!=(const BinaryTree<T> &other) const;
    BinaryTree<T> &operator=(const BinaryTree<T> &other);

    BinaryTree<T> apply(std::function<T(T)> func) const;
    BinaryTree<T> where(std::function<bool(T)> predicate) const;
    T reduce(std::function<T(T, T)> func, T initial) const;

    void makeThreaded(const std::string &traversalOrder = "inorder");
    void traverseThreaded(std::function<void(T)> visit) const;

    std::string serialize(const std::string &format = "default") const;
    void deserialize(const std::string &data, const std::string &format = "default");

    BinaryTree<T> merge(const BinaryTree<T> &other) const;

    BinaryTree<T> operator+(const BinaryTree<T> &other) const;
    friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &tree);

public:
    using Iterator = BinaryTreeIterator<T>;
    using ConstIterator = ConstBinaryTreeIterator<T>;

    Iterator begin();
    Iterator end();
    ConstIterator cbegin() const;
    ConstIterator cend() const;
};

#include "../impl/binaryTree.tpp"
