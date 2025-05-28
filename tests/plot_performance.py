import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import os

def plot_performance(file_path, title, save_path):
    try:
        data = pd.read_csv(file_path)
        plt.figure(figsize=(10, 6))
        
        # Проверяем порядок столбцов
        if 'avltree_insert' in data.columns and 'binarytree_insert' in data.columns:
            plt.plot(data['size'], data['avltree_insert'], 'r-', label='AVLTree Insert')
            
            # Проверяем, есть ли отрицательные значения (маркеры пропущенных измерений)
            if (data['binarytree_insert'] > 0).any():
                valid_data = data[data['binarytree_insert'] > 0]
                plt.plot(valid_data['size'], valid_data['binarytree_insert'], 'b-', label='BinaryTree Insert')
                
        elif 'avltree_search' in data.columns and 'binarytree_search' in data.columns:
            plt.plot(data['size'], data['avltree_search'], 'r-', label='AVLTree Search')
            plt.plot(data['size'], data['binarytree_search'], 'b-', label='BinaryTree Search')
        
        plt.xlabel('Size')
        plt.ylabel('Time (s)')
        plt.title(title)
        plt.legend()
        plt.grid()
        plt.savefig(save_path)
        plt.close()
    except FileNotFoundError:
        print(f"File not found: {file_path}")
    except Exception as e:
        print(f"An error occurred: {e}")

def plot_ratio(file_path, title, save_path):
    try:
        data = pd.read_csv(file_path)
        plt.figure(figsize=(10, 6))
        
        # Проверяем наличие колонки ratio
        if 'ratio' in data.columns:
            # Фильтруем отрицательные значения
            valid_data = data[data['ratio'] > 0]
            if not valid_data.empty:
                plt.plot(valid_data['size'], valid_data['ratio'], 'g-')
                plt.xlabel('Number of elements')
                plt.ylabel('BinaryTree time / AVLTree time')
                plt.title(f'{title} (BinaryTree/AVLTree)')
                plt.grid(True)
                plt.axhline(y=1, color='r', linestyle='--')
                plt.savefig(save_path)
                plt.close()
        # Если нет колонки ratio, вычисляем соотношение
        elif 'avltree_insert' in data.columns and 'binarytree_insert' in data.columns:
            # Фильтруем отрицательные значения
            valid_data = data[(data['binarytree_insert'] > 0) & (data['avltree_insert'] > 0)]
            if not valid_data.empty:
                ratio = valid_data['binarytree_insert'] / valid_data['avltree_insert']
                plt.plot(valid_data['size'], ratio, 'g-')
                plt.xlabel('Number of elements')
                plt.ylabel('BinaryTree time / AVLTree time')
                plt.title(f'{title} (BinaryTree/AVLTree)')
                plt.grid(True)
                plt.axhline(y=1, color='r', linestyle='--')
                plt.savefig(save_path)
                plt.close()
        elif 'avltree_search' in data.columns and 'binarytree_search' in data.columns:
            ratio = data['binarytree_search'] / data['avltree_search']
            plt.plot(data['size'], ratio, 'g-')
            plt.xlabel('Number of elements')
            plt.ylabel('BinaryTree time / AVLTree time')
            plt.title(f'{title} (BinaryTree/AVLTree)')
            plt.grid(True)
            plt.axhline(y=1, color='r', linestyle='--')
            plt.savefig(save_path)
            plt.close()
    except FileNotFoundError:
        print(f"File not found: {file_path}")
    except Exception as e:
        print(f"An error occurred: {e}")

def plot_log_scale(file_path, title, save_path):
    try:
        data = pd.read_csv(file_path)
        plt.figure(figsize=(10, 6))
        
        # Проверяем порядок столбцов
        if 'avltree_insert' in data.columns and 'binarytree_insert' in data.columns:
            plt.plot(data['size'], data['avltree_insert'], 'r-', label='AVLTree Insert')
            
            # Проверяем, есть ли отрицательные значения (маркеры пропущенных измерений)
            if (data['binarytree_insert'] > 0).any():
                valid_data = data[data['binarytree_insert'] > 0]
                plt.plot(valid_data['size'], valid_data['binarytree_insert'], 'b-', label='BinaryTree Insert')
                
        elif 'avltree_search' in data.columns and 'binarytree_search' in data.columns:
            plt.plot(data['size'], data['avltree_search'], 'r-', label='AVLTree Search')
            plt.plot(data['size'], data['binarytree_search'], 'b-', label='BinaryTree Search')
            
        plt.xlabel('Number of elements')
        plt.ylabel('Time (seconds)')
        plt.title(f'{title} (Log Scale)')
        plt.legend()
        plt.grid(True)
        plt.yscale('log')
        plt.savefig(save_path)
        plt.close()
    except FileNotFoundError:
        print(f"File not found: {file_path}")
    except Exception as e:
        print(f"An error occurred: {e}")

def plot_avl_only(file_path, title, save_path):
    """Строит график только для AVL-дерева, полезно для больших размеров"""
    try:
        data = pd.read_csv(file_path)
        plt.figure(figsize=(10, 6))
        
        if 'avltree_insert' in data.columns:
            plt.plot(data['size'], data['avltree_insert'], 'r-', label='AVLTree Insert')
            
            # Добавляем линию тренда для проверки логарифмической сложности
            x = data['size'].values
            y = data['avltree_insert'].values
            
            # Логарифмическая модель: y = a * log(x) + b
            log_x = np.log(x)
            coeffs = np.polyfit(log_x, y, 1)
            trend = coeffs[0] * log_x + coeffs[1]
            
            plt.plot(x, trend, 'g--', label=f'Trend: {coeffs[0]:.4f} * log(n) + {coeffs[1]:.4f}')
            
            plt.xlabel('Number of elements')
            plt.ylabel('Time (seconds)')
            plt.title(f'{title} - AVL Tree Only')
            plt.legend()
            plt.grid(True)
            plt.savefig(save_path)
            plt.close()
    except FileNotFoundError:
        print(f"File not found: {file_path}")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    # Проверяем наличие файлов
    files_to_process = [
        ("performance_insert_improved.csv", "Insert Performance"),
        ("performance_search.csv", "Search Performance"),
        ("performance_sorted_insert.csv", "Sorted Insert Performance"),
        ("large_sorted_performance.csv", "Large Sorted Performance"),
        ("medium_sorted_performance.csv", "Medium Sorted Performance"),
        ("small_sorted_comparison.csv", "Small Sorted Comparison"),
        ("large_reverse_sorted_performance.csv", "Large Reverse Sorted Performance")
    ]
    
    for file_info in files_to_process:
        file_path, title = file_info
        if os.path.exists(file_path):
            base_name = file_path.split('.')[0]
            plot_performance(file_path, title, f"{base_name}_comparison.png")
            plot_ratio(file_path, title, f"{base_name}_ratio.png")
            plot_log_scale(file_path, title, f"{base_name}_log_scale.png")
            
            # Для больших файлов также строим график только для AVL-дерева
            if file_path.startswith("large_"):
                plot_avl_only(file_path, title, f"{base_name}_avl_only.png")
        else:
            print(f"File {file_path} not found, skipping...")
