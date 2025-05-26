import React from 'react';

export default function TypeSelector({ treeType, setTreeType }) {
    return (
        <div style={{ flex: 1, minWidth: 220 }}>
            <label style={{ fontWeight: 600, marginBottom: 6, display: 'block' }}>🌲 Tree Type</label>
            <select 
                value={treeType} 
                onChange={e => setTreeType(e.target.value)} 
                style={selectStyle}
            >
                <option value="AVLTreeInt">AVL Tree (Int)</option>
                <option value="BinaryTreeInt">Binary Search Tree (Int)</option>
                <option value="AVLTreeComplex">AVL Tree (Complex)</option>
                <option value="BinaryTreeComplex">Binary Search Tree (Complex)</option>
                <option value="AVLTreePerson">AVL Tree (Person)</option>
                <option value="BinaryTreePerson">Binary Search Tree (Person)</option>
            </select>
        </div>
    );
}

const selectStyle = {
    width: '100%',
    padding: '10px 12px',
    borderRadius: 10,
    background: '#2a2a2a',
    border: '1px solid #444',
    color: '#f0f0f0',
    fontSize: 16,
};