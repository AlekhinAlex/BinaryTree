import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

def plot_performance(file_path, title, save_path):
    try:
        data = pd.read_csv(file_path)
        plt.figure(figsize=(10, 6))
        plt.plot(data['size'], data['binarytree_insert'], label='BinaryTree Insert')
        plt.plot(data['size'], data['avltree_insert'], label='AVLTree Insert')
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

# Read the performance data
df = pd.read_csv("performance_very_large.csv")

# Create a figure with two subplots
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))

# Plot 1: Insert Performance
ax1.plot(df['size'], df['binarytree_insert'], 'b-', label='BinaryTree')
ax1.plot(df['size'], df['avltree_insert'], 'r-', label='AVLTree')
ax1.set_xlabel('Number of elements')
ax1.set_ylabel('Time (seconds)')
ax1.set_title('Insert Performance: BinaryTree vs AVLTree')
ax1.legend()
ax1.grid(True)

# Plot 2: Performance Ratio
ratio = df['binarytree_insert'] / df['avltree_insert']
ax2.plot(df['size'], ratio, 'g-')
ax2.set_xlabel('Number of elements')
ax2.set_ylabel('BinaryTree time / AVLTree time')
ax2.set_title('Performance Ratio (BinaryTree/AVLTree)')
ax2.grid(True)

# Add a horizontal line at y=1 for reference
ax2.axhline(y=1, color='r', linestyle='--')

# Adjust layout and save
plt.tight_layout()
plt.savefig('performance_comparison.png')
plt.close()

# Create a logarithmic plot to better visualize differences
plt.figure(figsize=(10, 6))
plt.plot(df['size'], df['binarytree_insert'], 'b-', label='BinaryTree')
plt.plot(df['size'], df['avltree_insert'], 'r-', label='AVLTree')
plt.xlabel('Number of elements')
plt.ylabel('Time (seconds)')
plt.title('Insert Performance (Log Scale): BinaryTree vs AVLTree')
plt.legend()
plt.grid(True)
plt.yscale('log')
plt.savefig('performance_log_scale.png')
plt.close()

if __name__ == "__main__":
    plot_performance("performance_granular.csv", "Granular Performance Test", "granular_performance.png")
    plot_performance("performance_very_large.csv", "Very Large Performance Test", "very_large_performance.png")
