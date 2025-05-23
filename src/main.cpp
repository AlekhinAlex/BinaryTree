#include <iostream>
#include "../inc/binaryTree.hpp"

int main()
{
    BinaryTree<int> tree;
    //     5
    //    / \
    //   3   7
    //  / \
    // 2   4

    tree.insert(tree.getRoot(), 5);
    tree.insert(tree.getRoot(), 3);
    tree.insert(tree.getRoot(), 7);
    tree.insert(tree.getRoot(), 2);
    tree.insert(tree.getRoot(), 4);

    std::cout << "\nTree height: " << tree.getHeight() << std::endl;
    std::cout << "\nSearch 4: " << tree.search(5)->getData() << std::endl;

    tree.insert(tree.search(4), 77);

    std::cout << "\nSearch 77: " << tree.search(77)->getData() << std::endl;

    return 0;
}
