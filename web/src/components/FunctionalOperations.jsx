import React, { useState } from 'react';
import { motion } from 'framer-motion';

export default function FunctionalOperations({ tree, updateTree, setOperationMsg }) {
    const [applyOperation, setApplyOperation] = useState('multiply');
    const [applyValue, setApplyValue] = useState(2);
    const [whereOperation, setWhereOperation] = useState('greater');
    const [whereValue, setWhereValue] = useState(5);
    const [reduceOperation, setReduceOperation] = useState('sum');
    const [reduceInitial, setReduceInitial] = useState(0);
    const [pathValue, setPathValue] = useState('LR');

    const handleApply = () => {
        if (!tree || !tree.apply) {
            setOperationMsg('Apply operation not supported for this tree type');
            return;
        }

        try {
            const mapper = (value) => {
                // Check if we're dealing with a complex number
                if (value && typeof value === 'object' && 're' in value && 'im' in value) {
                    // Handle complex number operations
                    switch (applyOperation) {
                        case 'multiply':
                            return {
                                re: value.re * applyValue,
                                im: value.im * applyValue
                            };
                        case 'add':
                            return {
                                re: value.re + applyValue,
                                im: value.im
                            };
                        case 'subtract':
                            return {
                                re: value.re - applyValue,
                                im: value.im
                            };
                        case 'divide':
                            return {
                                re: value.re / applyValue,
                                im: value.im / applyValue
                            };
                        case 'square':
                            // (a+bi)² = a² - b² + 2abi
                            return {
                                re: value.re * value.re - value.im * value.im,
                                im: 2 * value.re * value.im
                            };
                        default:
                            return value;
                    }
                } 
                // Handle Person objects
                else if (value && typeof value === 'object' && 'name' in value && 'age' in value) {
                    switch (applyOperation) {
                        case 'multiply':
                            return {
                                name: value.name,
                                age: value.age * applyValue
                            };
                        case 'add':
                            return {
                                name: value.name,
                                age: value.age + applyValue
                            };
                        case 'subtract':
                            return {
                                name: value.name,
                                age: value.age - applyValue
                            };
                        case 'divide':
                            return {
                                name: value.name,
                                age: Math.floor(value.age / applyValue)
                            };
                        case 'square':
                            return {
                                name: value.name,
                                age: value.age * value.age
                            };
                        default:
                            return value;
                    }
                }
                // Regular number operations
                else {
                    switch (applyOperation) {
                        case 'multiply': return value * applyValue;
                        case 'add': return value + applyValue;
                        case 'subtract': return value - applyValue;
                        case 'divide': return Math.floor(value / applyValue);
                        case 'square': return value * value;
                        default: return value;
                    }
                }
            };

            const newTree = tree.apply(mapper);
            updateTree(newTree);
            setOperationMsg(`Applied ${applyOperation} operation`);
        } catch (e) {
            setOperationMsg(`Apply error: ${e.message}`);
        }
    };

    const handleWhere = () => {
        if (!tree || !tree.where) {
            setOperationMsg('Where operation not supported for this tree type');
            return;
        }

        try {
            const predicate = (value) => {
                // Check if we're dealing with a complex number
                if (value && typeof value === 'object' && 're' in value && 'im' in value) {
                    const magnitude = Math.sqrt(value.re * value.re + value.im * value.im);
                    
                    switch (whereOperation) {
                        case 'greater': return magnitude > whereValue;
                        case 'less': return magnitude < whereValue;
                        case 'equal': return magnitude === whereValue;
                        case 'notEqual': return magnitude !== whereValue;
                        case 'even': return magnitude % 2 === 0;
                        case 'odd': return magnitude % 2 !== 0;
                        default: return true;
                    }
                }
                // Handle Person objects
                else if (value && typeof value === 'object' && 'name' in value && 'age' in value) {
                    switch (whereOperation) {
                        case 'greater': return value.age > whereValue;
                        case 'less': return value.age < whereValue;
                        case 'equal': return value.age === whereValue;
                        case 'notEqual': return value.age !== whereValue;
                        case 'even': return value.age % 2 === 0;
                        case 'odd': return value.age % 2 !== 0;
                        default: return true;
                    }
                }
                // Regular number operations
                else {
                    switch (whereOperation) {
                        case 'greater': return value > whereValue;
                        case 'less': return value < whereValue;
                        case 'equal': return value === whereValue;
                        case 'notEqual': return value !== whereValue;
                        case 'even': return value % 2 === 0;
                        case 'odd': return value % 2 !== 0;
                        default: return true;
                    }
                }
            };

            const newTree = tree.where(predicate);
            updateTree(newTree);
            setOperationMsg(`Applied where ${whereOperation} filter`);
        } catch (e) {
            setOperationMsg(`Where error: ${e.message}`);
        }
    };

    const handleReduce = () => {
        if (!tree || !tree.reduce) {
            setOperationMsg('Reduce operation not supported for this tree type');
            return;
        }

        try {
            const reducer = (acc, value) => {
                // Check if we're dealing with complex numbers
                if (acc && typeof acc === 'object' && 're' in acc && 'im' in acc &&
                    value && typeof value === 'object' && 're' in value && 'im' in value) {
                    
                    switch (reduceOperation) {
                        case 'sum':
                            return {
                                re: acc.re + value.re,
                                im: acc.im + value.im
                            };
                        case 'multiply':
                            // (a+bi)(c+di) = (ac-bd) + (ad+bc)i
                            return {
                                re: acc.re * value.re - acc.im * value.im,
                                im: acc.re * value.im + acc.im * value.re
                            };
                        case 'max':
                            // Compare magnitudes for complex numbers
                            const accMag = Math.sqrt(acc.re * acc.re + acc.im * acc.im);
                            const valMag = Math.sqrt(value.re * value.re + value.im * value.im);
                            return accMag >= valMag ? acc : value;
                        case 'min':
                            // Compare magnitudes for complex numbers
                            const accMag2 = Math.sqrt(acc.re * acc.re + acc.im * acc.im);
                            const valMag2 = Math.sqrt(value.re * value.re + value.im * value.im);
                            return accMag2 <= valMag2 ? acc : value;
                        default:
                            return acc;
                    }
                }
                // Handle Person objects
                else if (acc && typeof acc === 'object' && 'name' in acc && 'age' in acc &&
                         value && typeof value === 'object' && 'name' in value && 'age' in value) {
                    
                    switch (reduceOperation) {
                        case 'sum':
                            return {
                                name: acc.name + "+" + value.name,
                                age: acc.age + value.age
                            };
                        case 'multiply':
                            return {
                                name: acc.name + "*" + value.name,
                                age: acc.age * value.age
                            };
                        case 'max':
                            return acc.age >= value.age ? acc : value;
                        case 'min':
                            return acc.age <= value.age ? acc : value;
                        default:
                            return acc;
                    }
                }
                // Regular number operations
                else {
                    switch (reduceOperation) {
                        case 'sum': return acc + value;
                        case 'multiply': return acc * value;
                        case 'max': return Math.max(acc, value);
                        case 'min': return Math.min(acc, value);
                        default: return acc;
                    }
                }
            };

            // Create appropriate initial value based on tree type
            let initialValue;
            
            // Check if we're dealing with a complex tree
            if (tree.getMin && typeof tree.getMin() === 'object' && 're' in tree.getMin()) {
                initialValue = { re: parseFloat(reduceInitial), im: 0 };
            }
            // Check if we're dealing with a person tree
            else if (tree.getMin && typeof tree.getMin() === 'object' && 'name' in tree.getMin()) {
                initialValue = { name: "Initial", age: parseInt(reduceInitial) };
            }
            // Regular number tree
            else {
                initialValue = parseInt(reduceInitial);
            }

            const result = tree.reduce(reducer, initialValue);
            
            // Format the result for display
            let displayResult;
            if (typeof result === 'object') {
                if ('re' in result && 'im' in result) {
                    displayResult = `${result.re}${result.im >= 0 ? '+' : ''}${result.im}i`;
                } else if ('name' in result && 'age' in result) {
                    displayResult = `${result.name} (${result.age})`;
                } else {
                    displayResult = JSON.stringify(result);
                }
            } else {
                displayResult = result;
            }
            
            setOperationMsg(`Reduce result (${reduceOperation}): ${displayResult}`);
        } catch (e) {
            setOperationMsg(`Reduce error: ${e.message}`);
        }
    };

    const handleFindByPath = () => {
        if (!tree || !tree.findByPath) {
            setOperationMsg('FindByPath operation not supported for this tree type');
            return;
        }

        try {
            const subtree = tree.findByPath(pathValue);
            if (subtree) {
                updateTree(subtree);
                setOperationMsg(`Found subtree at path: ${pathValue}`);
            } else {
                setOperationMsg(`No subtree found at path: ${pathValue}`);
            }
        } catch (e) {
            setOperationMsg(`FindByPath error: ${e.message}`);
        }
    };

    const handleMakeThreaded = () => {
        if (!tree || !tree.makeThreaded) {
            setOperationMsg('Threading not supported for this tree type');
            return;
        }

        try {
            tree.makeThreaded('inorder');
            setOperationMsg('Tree is now threaded (inorder)');
        } catch (e) {
            setOperationMsg(`Threading error: ${e.message}`);
        }
    };

    return (
        <div style={{ marginTop: 32, padding: '16px 0', borderTop: '1px solid #444' }}>
            <h3 style={{ color: '#8ec5fc', marginBottom: 16 }}>Advanced Operations</h3>

            <div style={{ display: 'grid', gridTemplateColumns: 'repeat(auto-fill, minmax(300px, 1fr))', gap: 16, marginBottom: 24 }}>
                {/* Apply Section */}
                <div style={operationCardStyle}>
                    <h4 style={operationTitleStyle}>Apply</h4>
                    <div style={operationContentStyle}>
                        <div style={{ display: 'flex', gap: 8, marginBottom: 12 }}>
                            <select 
                                value={applyOperation} 
                                onChange={(e) => setApplyOperation(e.target.value)}
                                style={selectStyle}
                            >
                                <option value="multiply">Multiply</option>
                                <option value="add">Add</option>
                                <option value="subtract">Subtract</option>
                                <option value="divide">Divide</option>
                                <option value="square">Square</option>
                            </select>
                            <input 
                                type="number" 
                                value={applyValue} 
                                onChange={(e) => setApplyValue(parseInt(e.target.value))}
                                style={inputStyle}
                                placeholder="Value"
                            />
                        </div>
                        <motion.button 
                            whileHover={{ scale: 1.05 }} 
                            whileTap={{ scale: 0.95 }}
                            onClick={handleApply}
                            style={buttonStyle}
                        >
                            Apply to All
                        </motion.button>
                    </div>
                </div>

                {/* Where Section */}
                <div style={operationCardStyle}>
                    <h4 style={operationTitleStyle}>Filter</h4>
                    <div style={operationContentStyle}>
                        <div style={{ display: 'flex', gap: 8, marginBottom: 12 }}>
                            <select 
                                value={whereOperation} 
                                onChange={(e) => setWhereOperation(e.target.value)}
                                style={selectStyle}
                            >
                                <option value="greater">Greater Than</option>
                                <option value="less">Less Than</option>
                                <option value="equal">Equal To</option>
                                <option value="notEqual">Not Equal To</option>
                                <option value="even">Even Numbers</option>
                                <option value="odd">Odd Numbers</option>
                            </select>
                            {whereOperation !== 'even' && whereOperation !== 'odd' && (
                                <input 
                                    type="number" 
                                    value={whereValue} 
                                    onChange={(e) => setWhereValue(parseInt(e.target.value))}
                                    style={inputStyle}
                                    placeholder="Value"
                                />
                            )}
                        </div>
                        <motion.button 
                            whileHover={{ scale: 1.05 }} 
                            whileTap={{ scale: 0.95 }}
                            onClick={handleWhere}
                            style={buttonStyle}
                        >
                            Filter Tree
                        </motion.button>
                    </div>
                </div>

                {/* Reduce Section */}
                <div style={operationCardStyle}>
                    <h4 style={operationTitleStyle}>Reduce</h4>
                    <div style={operationContentStyle}>
                        <div style={{ display: 'flex', gap: 8, marginBottom: 12 }}>
                            <select 
                                value={reduceOperation} 
                                onChange={(e) => setReduceOperation(e.target.value)}
                                style={selectStyle}
                            >
                                <option value="sum">Sum</option>
                                <option value="multiply">Multiply</option>
                                <option value="max">Maximum</option>
                                <option value="min">Minimum</option>
                            </select>
                            <input 
                                type="number" 
                                value={reduceInitial} 
                                onChange={(e) => setReduceInitial(e.target.value)}
                                style={inputStyle}
                                placeholder="Initial Value"
                            />
                        </div>
                        <motion.button 
                            whileHover={{ scale: 1.05 }} 
                            whileTap={{ scale: 0.95 }}
                            onClick={handleReduce}
                            style={buttonStyle}
                        >
                            Calculate
                        </motion.button>
                    </div>
                </div>

                {/* FindByPath Section */}
                <div style={operationCardStyle}>
                    <h4 style={operationTitleStyle}>Find By Path</h4>
                    <div style={operationContentStyle}>
                        <div style={{ display: 'flex', gap: 8, marginBottom: 12 }}>
                            <input 
                                type="text" 
                                value={pathValue} 
                                onChange={(e) => setPathValue(e.target.value)}
                                style={{...inputStyle, flex: 1}}
                                placeholder="Path (e.g. LR)"
                            />
                        </div>
                        <motion.button 
                            whileHover={{ scale: 1.05 }} 
                            whileTap={{ scale: 0.95 }}
                            onClick={handleFindByPath}
                            style={buttonStyle}
                        >
                            Find Subtree
                        </motion.button>
                    </div>
                </div>

                {/* Threading Section */}
                <div style={operationCardStyle}>
                    <h4 style={operationTitleStyle}>Threading</h4>
                    <div style={operationContentStyle}>
                        <motion.button 
                            whileHover={{ scale: 1.05 }} 
                            whileTap={{ scale: 0.95 }}
                            onClick={handleMakeThreaded}
                            style={buttonStyle}
                        >
                            Make Threaded
                        </motion.button>
                    </div>
                </div>
            </div>
        </div>
    );
}

const operationCardStyle = {
    background: '#2a2a2a',
    borderRadius: 12,
    overflow: 'hidden',
    boxShadow: '0 4px 12px rgba(0, 0, 0, 0.2)',
};

const operationTitleStyle = {
    margin: 0,
    padding: '12px 16px',
    background: '#333',
    color: '#8ec5fc',
    fontSize: 16,
    fontWeight: 600,
};

const operationContentStyle = {
    padding: 16,
};

const selectStyle = {
    flex: 2,
    padding: '10px 12px',
    borderRadius: 8,
    background: '#222',
    border: '1px solid #444',
    color: '#e0e0e0',
    fontSize: 14,
};

const inputStyle = {
    flex: 1,
    padding: '10px 12px',
    borderRadius: 8,
    background: '#222',
    border: '1px solid #444',
    color: '#e0e0e0',
    fontSize: 14,
};

const buttonStyle = {
    width: '100%',
    padding: '10px 16px',
    borderRadius: 8,
    background: 'linear-gradient(135deg, #2196f3, #1e88e5)',
    border: 'none',
    color: '#fff',
    fontWeight: 600,
    fontSize: 14,
    cursor: 'pointer',
};