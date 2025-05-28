#include <gtest/gtest.h>
#include "../inc/binaryTree.hpp"
#include "../inc/AVLTree.hpp"
#include <chrono>
#include <fstream>
#include <vector>
#include <iomanip>
#include <iostream>

// Функция для тестирования вставки отсортированных данных
void sorted_performance_test(const std::string &filename, size_t max_size, size_t step)
{
    std::ofstream ofs("../tests/" + filename);
    if (!ofs.is_open())
    {
        std::cerr << "Failed to open file: tests/" << filename << std::endl;
        return;
    }
    std::cout << "File opened successfully: tests/" << filename << std::endl;

    ofs << "size,avltree_insert,binarytree_insert,ratio\n";

    for (size_t n = step; n <= max_size; n += step)
    {
        std::cout << "Testing size: " << n << std::endl;

        // Создаем отсортированные данные
        std::vector<int> data(n);
        for (size_t i = 0; i < n; ++i)
            data[i] = i;

        // Измеряем время для AVL-дерева
        AVLTree<int> avl;
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int x : data)
            avl.insert(x);
        auto t2 = std::chrono::high_resolution_clock::now();
        double avl_time = std::chrono::duration<double>(t2 - t1).count();

        // Для больших размеров ограничиваем тестирование обычного дерева
        double bt_time = 0.0;
        double ratio = 0.0;

        // Для обычного дерева ограничиваем размер, чтобы избежать слишком долгого выполнения
        if (n <= 50000)
        {
            BinaryTree<int> bt;
            t1 = std::chrono::high_resolution_clock::now();
            for (int x : data)
                bt.insert(x);
            t2 = std::chrono::high_resolution_clock::now();
            bt_time = std::chrono::duration<double>(t2 - t1).count();
            ratio = bt_time / avl_time;
        }
        else
        {
            // Для больших размеров экстраполируем время на основе квадратичной сложности
            // Используем последнее известное соотношение
            bt_time = -1; // Маркер, что время не измерялось
            ratio = -1;   // Маркер, что соотношение не вычислялось
        }

        ofs << n << "," << std::fixed << std::setprecision(6)
            << avl_time << "," << bt_time << "," << ratio << "\n";

        std::cout << "Size: " << n
                  << ", AVL time: " << avl_time << "s"
                  << ", BT time: " << (bt_time > 0 ? std::to_string(bt_time) + "s" : "skipped")
                  << ", Ratio: " << (ratio > 0 ? std::to_string(ratio) + "x" : "N/A")
                  << std::endl;
    }

    ofs.close();
    std::cout << "Data successfully written to: tests/" << filename << std::endl;
}

// Функция для тестирования вставки данных в обратном порядке
void reverse_sorted_performance_test(const std::string &filename, size_t max_size, size_t step)
{
    std::ofstream ofs("../tests/" + filename);
    if (!ofs.is_open())
    {
        std::cerr << "Failed to open file: tests/" << filename << std::endl;
        return;
    }
    std::cout << "File opened successfully: tests/" << filename << std::endl;

    ofs << "size,avltree_insert,binarytree_insert,ratio\n";

    for (size_t n = step; n <= max_size; n += step)
    {
        std::cout << "Testing size: " << n << std::endl;

        // Создаем данные в обратном порядке
        std::vector<int> data(n);
        for (size_t i = 0; i < n; ++i)
            data[i] = n - i - 1;

        // Измеряем время для AVL-дерева
        AVLTree<int> avl;
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int x : data)
            avl.insert(x);
        auto t2 = std::chrono::high_resolution_clock::now();
        double avl_time = std::chrono::duration<double>(t2 - t1).count();

        // Для больших размеров ограничиваем тестирование обычного дерева
        double bt_time = 0.0;
        double ratio = 0.0;

        // Для обычного дерева ограничиваем размер, чтобы избежать слишком долгого выполнения
        if (n <= 50000)
        {
            BinaryTree<int> bt;
            t1 = std::chrono::high_resolution_clock::now();
            for (int x : data)
                bt.insert(x);
            t2 = std::chrono::high_resolution_clock::now();
            bt_time = std::chrono::duration<double>(t2 - t1).count();
            ratio = bt_time / avl_time;
        }
        else
        {
            bt_time = -1;
            ratio = -1;
        }

        ofs << n << "," << std::fixed << std::setprecision(6)
            << avl_time << "," << bt_time << "," << ratio << "\n";

        std::cout << "Size: " << n
                  << ", AVL time: " << avl_time << "s"
                  << ", BT time: " << (bt_time > 0 ? std::to_string(bt_time) + "s" : "skipped")
                  << ", Ratio: " << (ratio > 0 ? std::to_string(ratio) + "x" : "N/A")
                  << std::endl;
    }

    ofs.close();
    std::cout << "Data successfully written to: tests/" << filename << std::endl;
}

// Тест для больших отсортированных данных
TEST(SortedPerformanceTest, LargeAscending)
{
    // Тестируем на размерах от 10^5 до 10^7
    sorted_performance_test("large_sorted_performance.csv", 10000000, 1000000);
    SUCCEED();
}

// Тест для больших данных в обратном порядке
TEST(SortedPerformanceTest, LargeDescending)
{
    // Тестируем на размерах от 10^5 до 10^7
    reverse_sorted_performance_test("large_reverse_sorted_performance.csv", 10000000, 1000000);
    SUCCEED();
}

// Более детальный тест для средних размеров
TEST(SortedPerformanceTest, MediumAscending)
{
    // Тестируем на размерах от 10^4 до 10^5 с меньшим шагом
    sorted_performance_test("medium_sorted_performance.csv", 100000, 10000);
    SUCCEED();
}

// Тест для сравнения с обычным деревом на малых размерах
TEST(SortedPerformanceTest, SmallComparison)
{
    // Тестируем на размерах, где обычное дерево еще может работать
    sorted_performance_test("small_sorted_comparison.csv", 50000, 5000);
    SUCCEED();
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}