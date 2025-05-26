import React, { useState } from 'react';
import { motion } from 'framer-motion';

export default function ComplexInput({ onInsert, onRemove, onSearch }) {
    const [realPart, setRealPart] = useState(0);
    const [imagPart, setImagPart] = useState(0);
    const [operation, setOperation] = useState('insert');

    const handleSubmit = () => {
        const complexValue = { re: parseFloat(realPart), im: parseFloat(imagPart) };
        
        switch(operation) {
            case 'insert':
                onInsert(complexValue);
                break;
            case 'remove':
                onRemove(complexValue);
                break;
            case 'search':
                onSearch(complexValue);
                break;
            default:
                break;
        }
    };

    return (
        <div style={{ marginBottom: 20 }}>
            <div style={{ display: 'flex', gap: 12, marginBottom: 12 }}>
                <input
                    type="number"
                    value={realPart}
                    onChange={(e) => setRealPart(e.target.value)}
                    placeholder="Real part"
                    style={inputStyle}
                />
                <span style={{ color: '#e0e0e0', alignSelf: 'center' }}>+</span>
                <input
                    type="number"
                    value={imagPart}
                    onChange={(e) => setImagPart(e.target.value)}
                    placeholder="Imaginary part"
                    style={inputStyle}
                />
                <span style={{ color: '#e0e0e0', alignSelf: 'center' }}>i</span>
            </div>
            
            <div style={{ display: 'flex', gap: 12 }}>
                <select 
                    value={operation} 
                    onChange={(e) => setOperation(e.target.value)}
                    style={selectStyle}
                >
                    <option value="insert">Insert</option>
                    <option value="remove">Remove</option>
                    <option value="search">Search</option>
                </select>
                
                <motion.button
                    whileHover={{ scale: 1.05 }}
                    whileTap={{ scale: 0.95 }}
                    onClick={handleSubmit}
                    style={getButtonStyle(operation)}
                >
                    {getButtonLabel(operation)}
                </motion.button>
            </div>
        </div>
    );
}

const inputStyle = {
    flex: 1,
    padding: '12px 14px',
    borderRadius: 10,
    background: '#2a2a2a',
    border: '1px solid #444',
    color: '#e0e0e0',
    fontSize: 16,
};

const selectStyle = {
    flex: 1,
    padding: '12px 14px',
    borderRadius: 10,
    background: '#2a2a2a',
    border: '1px solid #444',
    color: '#e0e0e0',
    fontSize: 16,
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
};

function getButtonStyle(operation) {
    switch(operation) {
        case 'insert':
            return {
                ...buttonBase,
                background: 'linear-gradient(135deg, #2196f3, #1e88e5)',
            };
        case 'remove':
            return {
                ...buttonBase,
                background: 'linear-gradient(135deg, #e53935, #b71c1c)',
            };
        case 'search':
            return {
                ...buttonBase,
                background: 'linear-gradient(135deg, #43a047, #2e7d32)',
            };
        default:
            return buttonBase;
    }
}

function getButtonLabel(operation) {
    switch(operation) {
        case 'insert': return '➕ Insert';
        case 'remove': return '🗑️ Remove';
        case 'search': return '🔍 Search';
        default: return 'Submit';
    }
}