import React, { useEffect, useState } from 'react';
import { createTree } from './treeApi';
import TreeView from './components/TreeView';
import TypeSelector from './components/TypeSelector';
import ComplexInput from './components/ComplexInput';
import PersonInput from './components/PersonInput';
import FunctionalOperations from './components/FunctionalOperations';
import { motion, AnimatePresence } from 'framer-motion';

function App() {
    const [tree, setTree] = useState(null);
    const [treeType, setTreeType] = useState('AVLTreeInt');
    const [serializedTree, setSerializedTree] = useState('');
    const [inputValue, setInputValue] = useState('');
    const [removeValue, setRemoveValue] = useState('');
    const [searchValue, setSearchValue] = useState('');
    const [searchResult, setSearchResult] = useState(null);
    const [traversal, setTraversal] = useState('inorder');
    const [loading, setLoading] = useState(true);
    const [error, setError] = useState('');
    const [operationMsg, setOperationMsg] = useState('');
    const [module, setModule] = useState(null);

    useEffect(() => {
        setLoading(true);
        createTree()
            .then((mod) => {
                setModule(mod);
                let t;
                if (treeType === 'AVLTreeInt') t = new mod.AVLTreeInt();
                else if (treeType === 'BinaryTreeInt') t = new mod.BinaryTreeInt();
                else if (treeType === 'AVLTreeComplex') t = new mod.AVLTreeComplex();
                else if (treeType === 'BinaryTreeComplex') t = new mod.BinaryTreeComplex();
                else if (treeType === 'AVLTreePerson') t = new mod.AVLTreePerson();
                else if (treeType === 'BinaryTreePerson') t = new mod.BinaryTreePerson();
                setTree(t);
                setSerializedTree('');
                setLoading(false);
            })
            .catch((e) => {
                setError('WebAssembly load error: ' + e.message);
                setLoading(false);
            });
    }, [treeType]);

    const updateSerialized = (t = tree) => {
        if (t) setSerializedTree(t.serialize(traversal));
    };

    const handleInsert = (value = inputValue) => {
        if (tree && value) {
            try {
                let insertValue = value;
                
                // If it's a string and we're dealing with integer trees
                if (typeof value === 'string' && (treeType === 'AVLTreeInt' || treeType === 'BinaryTreeInt')) {
                    insertValue = parseInt(value, 10);
                }
                
                // For BinaryTree types, use level-order insertion
                if (treeType.startsWith('BinaryTree')) {
                    // Insert at root level for level-order insertion
                    tree.insert(insertValue, tree.getRoot ? tree.getRoot() : null);
                } else {
                    // For AVL trees, use normal insertion
                    tree.insert(insertValue);
                }
                updateSerialized();
                setInputValue('');
                setOperationMsg('Inserted successfully');
            } catch (e) {
                setOperationMsg('Insert error: ' + e.message);
            }
        }
    };

    const handleRemove = (value = removeValue) => {
        if (tree && value) {
            try {
                let removeVal = value;
                
                // If it's a string and we're dealing with integer trees
                if (typeof value === 'string' && (treeType === 'AVLTreeInt' || treeType === 'BinaryTreeInt')) {
                    removeVal = parseInt(value, 10);
                }
                
                tree.remove(removeVal);
                updateSerialized();
                setRemoveValue('');
                setOperationMsg('Removed successfully');
            } catch (e) {
                setOperationMsg('Remove error: ' + e.message);
            }
        }
    };

    const handleSearch = (value = searchValue) => {
        if (tree && value) {
            try {
                let searchVal = value;
                
                // If it's a string and we're dealing with integer trees
                if (typeof value === 'string' && (treeType === 'AVLTreeInt' || treeType === 'BinaryTreeInt')) {
                    searchVal = parseInt(value, 10);
                }
                
                const found = tree.hasValue ? tree.hasValue(searchVal) : tree.find(searchVal);
                setSearchResult(found);
                setOperationMsg(found ? 'Value found' : 'Value not found');
            } catch (e) {
                setOperationMsg('Search error: ' + e.message);
            }
        }
    };

    const handleClear = () => {
        if (tree) {
            tree.clear();
            setSerializedTree('');
            setOperationMsg('Tree cleared');
        }
    };

    const handleBalance = () => {
        if (tree && tree.balance) {
            try {
                console.log('Before balance:', tree.serialize(traversal));
                tree.balance();
                setTimeout(() => {
                    updateSerialized();
                    console.log('After balance:', tree.serialize(traversal));
                }, 0);
                setOperationMsg('Tree balanced');
            } catch (e) {
                setOperationMsg('Balance error: ' + e.message);
            }
        }
    };

    const handleMin = () => {
        if (tree && tree.getMin) {
            try {
                setOperationMsg('Min value: ' + tree.getMin());
            } catch (e) {
                setOperationMsg('Min error: ' + e.message);
            }
        }
    };

    const handleMax = () => {
        if (tree && tree.getMax) {
            try {
                setOperationMsg('Max value: ' + tree.getMax());
            } catch (e) {
                setOperationMsg('Max error: ' + e.message);
            }
        }
    };

    const handleTraversalChange = (e) => {
        setTraversal(e.target.value);
        setTimeout(() => updateSerialized(), 0);
    };

    return (
        <div style={{ padding: 0, margin: 0, minHeight: '100vh', background: 'linear-gradient(135deg, #1a1a1a 0%, #2d2d2d 100%)', fontFamily: 'Segoe UI, Arial, sans-serif' }}>
            <motion.header
                initial={{ opacity: 0, y: -30 }}
                animate={{ opacity: 1, y: 0 }}
                transition={{ duration: 0.6 }}
                style={{
                    background: 'linear-gradient(135deg, #1f1c2c, #928dab)',
                    color: '#ffffff',
                    padding: '3rem 1rem',
                    textAlign: 'center',
                    boxShadow: '0 4px 20px rgba(0, 0, 0, 0.4)',
                    borderBottom: '1px solid rgba(255,255,255,0.1)',
                }}
            >
                <h1
                    style={{
                        margin: 0,
                        fontWeight: 800,
                        fontSize: 'clamp(2rem, 5vw, 3rem)',
                        letterSpacing: '1px',
                        background: 'linear-gradient(90deg, #ffecd2, #fcb69f)',
                        WebkitBackgroundClip: 'text',
                        WebkitTextFillColor: 'transparent',
                    }}
                >
                    Binary Search Tree & AVL Tree
                </h1>
                <p
                    style={{
                        marginTop: '1rem',
                        fontSize: 'clamp(1rem, 2vw, 1.25rem)',
                        color: 'rgba(255, 255, 255, 0.8)',
                        fontWeight: 300,
                    }}
                >
                    Interactive C++ tree structures in your browser
                </p>
            </motion.header>

            <motion.main
                initial={{ opacity: 0, y: 40 }}
                animate={{ opacity: 1, y: 0 }}
                transition={{ duration: 0.7, delay: 0.3 }}
                style={{
                    maxWidth: 720,
                    margin: '40px auto',
                    background: '#1e1e1e',
                    borderRadius: 20,
                    boxShadow: '0 8px 32px rgba(255, 255, 255, 0.9)',
                    padding: '32px 24px',
                    color: '#e0e0e0',
                }}
            >
                {loading && (
                    <p style={{ color: '#8ec5fc', fontWeight: 600, marginBottom: 16 }}>
                        🌀 Loading WebAssembly...
                    </p>
                )}
                {error && (
                    <p style={{ color: '#ff5252', fontWeight: 600, marginBottom: 16 }}>
                        ❌ {error}
                    </p>
                )}

                {!loading && !error && (
                    <>
                        <section style={{ display: 'flex', gap: 16, flexWrap: 'wrap', marginBottom: 24 }}>
                            <TypeSelector treeType={treeType} setTreeType={setTreeType} />
                            <div style={{ flex: 1, minWidth: 220 }}>
                                <label style={{ fontWeight: 600, marginBottom: 6, display: 'block' }}>🔁 Traversal</label>
                                <select value={traversal} onChange={handleTraversalChange} style={selectStyle}>
                                    <option value="inorder">Inorder</option>
                                    <option value="preorder">Preorder</option>
                                    <option value="postorder">Postorder</option>
                                </select>
                            </div>
                        </section>

                        {/* Show appropriate input based on tree type */}
                        {treeType.includes('Complex') ? (
                            <ComplexInput 
                                onInsert={handleInsert}
                                onRemove={handleRemove}
                                onSearch={handleSearch}
                            />
                        ) : treeType.includes('Person') ? (
                            <PersonInput 
                                onInsert={handleInsert}
                                onRemove={handleRemove}
                                onSearch={handleSearch}
                            />
                        ) : (
                            // Integer input
                            [{
                                value: inputValue, setValue: setInputValue, placeholder: 'Insert value', handler: handleInsert, style: buttonStyles.insert, icon: '➕ Insert'
                            }, {
                                value: removeValue, setValue: setRemoveValue, placeholder: 'Remove value', handler: handleRemove, style: buttonStyles.remove, icon: '🗑️ Remove'
                            }, {
                                value: searchValue, setValue: setSearchValue, placeholder: 'Search value', handler: handleSearch, style: buttonStyles.search, icon: '🔍 Search'
                            }].map(({ value, setValue, placeholder, handler, style, icon }, i) => (
                                <section key={i} style={inputGroupStyle}>
                                    <input type="number" value={value} onChange={e => setValue(e.target.value)} placeholder={placeholder} style={inputStyle} />
                                    <motion.button whileHover={{ scale: 1.05 }} whileTap={{ scale: 0.95 }} onClick={() => handler()} style={style}>
                                        {icon}
                                    </motion.button>
                                </section>
                            ))
                        )}

                        <section style={{ display: 'flex', gap: 16, margin: '24px 0', flexWrap: 'wrap' }}>
                            <ActionButton onClick={handleClear} label="🧹 Clear Tree" style={buttonStyles.clear} />
                            {treeType === 'BinaryTreeInt' && (
                                <ActionButton onClick={handleBalance} label="⚖️ Balance" style={buttonStyles.balance} />
                            )}
                            <ActionButton onClick={handleMin} label="📉 Min" style={buttonStyles.info} />
                            <ActionButton onClick={handleMax} label="📈 Max" style={buttonStyles.info} />
                        </section>

                        <AnimatePresence>
                            {operationMsg && (
                                <motion.div
                                    key="msg"
                                    initial={{ opacity: 0, y: 20 }}
                                    animate={{ opacity: 1, y: 0 }}
                                    exit={{ opacity: 0, y: 20 }}
                                    transition={{ duration: 0.3 }}
                                    style={messageBox('#8ec5fc')}
                                >
                                    ℹ️ {operationMsg}
                                </motion.div>
                            )}
                        </AnimatePresence>

                        <AnimatePresence>
                            {searchResult !== null && (
                                <motion.div
                                    key="result"
                                    initial={{ opacity: 0, y: 20 }}
                                    animate={{ opacity: 1, y: 0 }}
                                    exit={{ opacity: 0, y: 20 }}
                                    transition={{ duration: 0.3 }}
                                    style={messageBox(
                                        searchResult ? '#4caf50' : '#ff5252',
                                        searchResult ? '#1b5e2033' : '#ff174433'
                                    )}
                                >
                                    {searchResult ? '✅ Found' : '❌ Not Found'}
                                </motion.div>
                            )}
                        </AnimatePresence>

                        <TreeView serializedTree={serializedTree} />
                        
                        {/* Add functional operations component */}
                        <FunctionalOperations 
                            tree={tree} 
                            updateTree={(newTree) => {
                                setTree(newTree);
                                updateSerialized(newTree);
                            }}
                            setOperationMsg={setOperationMsg}
                        />
                    </>
                )}
            </motion.main>

            <motion.footer
                initial={{ opacity: 0 }}
                animate={{ opacity: 1 }}
                transition={{ delay: 0.8 }}
                style={{
                    textAlign: 'center',
                    color: '#9e9e9e',
                    marginTop: "100",
                    bottom: 0,
                    width: '100%',

                    fontSize: 14,
                    padding: '24px 0',
                }}
            >
                <span style={{ opacity: 0.7 }}>
                    &copy; {new Date().getFullYear()} WebAssembly Tree Demo — Built with ❤️ using C++ & WebAssembly<br />
                    Developed by <strong style={{ color: '#8ec5fc' }}>Alex Alekhin</strong>
                </span>
            </motion.footer>
        </div>
    );
}

export default App;

// Reusable animated action button
const ActionButton = ({ onClick, label, style }) => (
    <motion.button whileHover={{ scale: 1.05 }} whileTap={{ scale: 0.95 }} onClick={onClick} style={style}>
        {label}
    </motion.button>
);

const selectStyle = {
    width: '100%',
    padding: '10px 12px',
    borderRadius: 10,
    background: '#2a2a2a',
    border: '1px solid #444',
    color: '#f0f0f0',
    fontSize: 16,
};

const inputStyle = {
    flex: 2,
    padding: '12px 14px',
    borderRadius: 10,
    background: '#2a2a2a',
    border: '1px solid #444',
    color: '#e0e0e0',
    fontSize: 16,
    minWidth: 200,
};

const inputGroupStyle = {
    display: 'flex',
    gap: 12,
    marginBottom: 20,
    flexWrap: 'wrap',
};

const buttonBase = {
    transition: 'transform 0.2s ease',
    border: 'none',
    borderRadius: 10,
    padding: '12px 20px',
    fontWeight: 600,
    fontSize: 16,
    color: '#fff',
    cursor: 'pointer',
    flex: 1,
    minWidth: 120,
};

const buttonStyles = {
    insert: {
        ...buttonBase,
        background: 'linear-gradient(135deg, #2196f3, #1e88e5)',
    },
    remove: {
        ...buttonBase,
        background: 'linear-gradient(135deg, #e53935, #b71c1c)',
    },
    search: {
        ...buttonBase,
        background: 'linear-gradient(135deg, #43a047, #2e7d32)',
    },
    clear: {
        ...buttonBase,
        background: 'linear-gradient(135deg, #757575, #424242)',
    },
    balance: {
        ...buttonBase,
        background: 'linear-gradient(135deg, #ffb300, #f57c00)',
    },
    info: {
        ...buttonBase,
        background: 'linear-gradient(135deg, #2196f3, #1e88e5)',
    },
};

const messageBox = (color, bg = '#2a2a2a') => ({
    background: bg,
    border: `1px solid ${color}`,
    borderRadius: 10,
    padding: '12px 16px',
    marginBottom: 20,
    fontWeight: 600,
    color: color,
});
