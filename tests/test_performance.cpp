#include <gtest/gtest.h>
#include "../inc/binaryTree.hpp"
#include "../inc/AVLTree.hpp"
#include <chrono>
#include <fstream>
#include <vector>
#include <random>
#include <unistd.h>
#include <limits.h>

void performance_test(const std::string &filename, size_t max_size, size_t step)
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != nullptr)
    {
        std::cout << "Current working directory: " << cwd << std::endl;
    }
    else
    {
        std::cerr << "Error getting current working directory" << std::endl;
    }

    std::ofstream ofs("../tests/" + filename);
    if (!ofs.is_open())
    {
        std::cerr << "Failed to open file: tests/" << filename << std::endl;
        return;
    }
    std::cout << "File opened successfully: tests/" << filename << std::endl;

    ofs << "size,binarytree_insert,avltree_insert\n";
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(1, 1e9);

    for (size_t n = step; n <= std::min(max_size, step * 2); n += step)
    {
        std::vector<int> data(n);
        for (size_t i = 0; i < n; ++i)
            data[i] = dist(rng);

        BinaryTree<int> bt;
        AVLTree<int> avl;

        auto t1 = std::chrono::high_resolution_clock::now();
        for (int x : data)
            bt.insert(x);
        auto t2 = std::chrono::high_resolution_clock::now();
        double bt_time = std::chrono::duration<double>(t2 - t1).count();

        t1 = std::chrono::high_resolution_clock::now();
        for (int x : data)
            avl.insert(x);
        t2 = std::chrono::high_resolution_clock::now();
        double avl_time = std::chrono::duration<double>(t2 - t1).count();

        ofs << n << "," << bt_time << "," << avl_time << "\n";
        std::cout << "Processed size: " << n << std::endl;
    }
    ofs.close();
    std::cout << "Data successfully written to: tests/" << filename << std::endl;
}

void performance_test_granular(const std::string &filename, size_t max_size, size_t step)
{
    std::ofstream ofs(filename);
    if (!ofs.is_open())
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    std::cout << "Writing data to: " << filename << std::endl;

    ofs << "size,binarytree_insert,avltree_insert\n";
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(1, 1e9);

    for (size_t n = step; n <= max_size; n += step)
    {
        std::vector<int> data(n);
        for (size_t i = 0; i < n; ++i)
            data[i] = dist(rng);

        BinaryTree<int> bt;
        AVLTree<int> avl;

        auto t1 = std::chrono::high_resolution_clock::now();
        for (int x : data)
            bt.insert(x);
        auto t2 = std::chrono::high_resolution_clock::now();
        double bt_time = std::chrono::duration<double>(t2 - t1).count();

        t1 = std::chrono::high_resolution_clock::now();
        for (int x : data)
            avl.insert(x);
        t2 = std::chrono::high_resolution_clock::now();
        double avl_time = std::chrono::duration<double>(t2 - t1).count();

        ofs << n << "," << bt_time << "," << avl_time << "\n";
        std::cout << "n=" << n << " done\n";
    }
    ofs.close();
    std::cout << "Data successfully written to: " << filename << std::endl;
}

TEST(PerformanceTest, SmallToLarge)
{
    // Reduced test size to avoid long test runs
    performance_test("performance_small_large.csv", 20000, 10000);
    SUCCEED();
}

TEST(PerformanceTest, GranularSmallToLarge)
{
    performance_test_granular("performance_granular.csv", 50000, 5000);
    SUCCEED();
}

// Для очень больших тестов используйте отдельный исполняемый файл test_performance_big.cpp
