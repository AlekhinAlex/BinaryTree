import React from 'react';

// Новый способ: строим дерево по структуре (если есть), иначе по массиву (старый способ)
function buildTreeFromStructure(nodeObj) {
    if (!nodeObj || nodeObj.value === undefined) return null;
    return {
        value: nodeObj.value,
        left: buildTreeFromStructure(nodeObj.left),
        right: buildTreeFromStructure(nodeObj.right)
    };
}

// Строим дерево по level order (ширина в ширину)
function buildTreeFromLevelOrder(values) {
    if (!values || !values.length) return null;
    // Если есть null-ы, используем их для структуры
    const nodes = values.map(v => {
        if (v === null || v === 'null' || v === undefined) return null;

        // Handle complex numbers like "-1+0i"
        if (typeof v === 'string' && v.includes('i')) {
            // Extract both real and imaginary parts for display
            const complexMatch = v.match(/^(-?\d+(?:\.\d+)?)([+-]\d+(?:\.\d+)?)i$/);
            const imagOnlyMatch = v.match(/^([+-]?\d+(?:\.\d+)?)i$/);
            const realOnlyMatch = v.match(/^(-?\d+(?:\.\d+)?)$/);

            let displayValue = v;
            if (complexMatch) {
                displayValue = `${complexMatch[1]}${complexMatch[2]}i`;
            } else if (imagOnlyMatch) {
                displayValue = `0${imagOnlyMatch[1] >= 0 ? '+' : ''}${imagOnlyMatch[1]}i`;
            } else if (realOnlyMatch) {
                displayValue = `${realOnlyMatch[1]}+0i`;
            }

            return { value: v, displayValue };
        }

        // Handle JSON objects (for Complex and Person)
        if (typeof v === 'string' && v.startsWith('{') && v.endsWith('}')) {
            try {
                const obj = JSON.parse(v);
                if (obj) {
                    // For Complex objects
                    if (typeof obj.re !== 'undefined' && typeof obj.im !== 'undefined') {
                        const displayValue = `${obj.re}${obj.im >= 0 ? '+' : ''}${obj.im}i`;
                        return { value: v, displayValue };
                    }
                    // For Person objects
                    if (typeof obj.name !== 'undefined' && typeof obj.age !== 'undefined') {
                        const displayValue = `${obj.name} (${obj.age})`;
                        return { value: v, displayValue };
                    }
                }
            } catch (e) {
                // Not a valid JSON, continue with default handling
            }
        }

        return { value: v };
    });

    let i = 0;
    for (let j = 0; j < nodes.length; ++j) {
        if (nodes[j] !== null) {
            const leftIdx = 2 * j + 1;
            const rightIdx = 2 * j + 2;
            if (leftIdx < nodes.length) nodes[j].left = nodes[leftIdx];
            if (rightIdx < nodes.length) nodes[j].right = nodes[rightIdx];
        }
    }
    return nodes[0];
}

function buildTree(values, structure, mode = 'level') {
    if (structure) {
        return buildTreeFromStructure(structure);
    }
    if (mode === 'level') {
        return buildTreeFromLevelOrder(values);
    }
    // fallback: старый способ (балансировка)
    if (!values.length) return null;
    function helper(arr) {
        if (!arr.length) return null;
        const mid = Math.floor(arr.length / 2);
        return {
            value: arr[mid],
            left: helper(arr.slice(0, mid)),
            right: helper(arr.slice(mid + 1)),
        };
    }
    return helper(values);
}

// Calculate depth of a binary tree
function getTreeDepth(node) {
    if (!node) return 0;
    return 1 + Math.max(getTreeDepth(node.left), getTreeDepth(node.right));
}

// Recursive SVG tree renderer
function renderTreeSVG(node, x, y, dx, dy, level = 0, lines = [], nodes = []) {
    if (!node) return { lines, nodes };

    const lineColor = '#666';
    const nodeFill = 'url(#bubble-dark)';
    const nodeStroke = '#8ec5fc';
    const textColor = '#e0e0e0';

    if (node.left) {
        const lx = x - dx / (level + 2);
        const ly = y + dy;
        lines.push(
            <line
                key={`line-L-${x}-${y}`}
                x1={x}
                y1={y}
                x2={lx}
                y2={ly}
                stroke={lineColor}
                strokeWidth={2}
            />
        );
        renderTreeSVG(node.left, lx, ly, dx, dy, level + 1, lines, nodes);
    }

    if (node.right) {
        const rx = x + dx / (level + 2);
        const ry = y + dy;
        lines.push(
            <line
                key={`line-R-${x}-${y}`}
                x1={x}
                y1={y}
                x2={rx}
                y2={ry}
                stroke={lineColor}
                strokeWidth={2}
            />
        );
        renderTreeSVG(node.right, rx, ry, dx, dy, level + 1, lines, nodes);
    }

    nodes.push(
        <g key={`node-${x}-${y}`}>
            <circle cx={x} cy={y} r={22} fill={nodeFill} stroke={nodeStroke} strokeWidth={2} />
            {/* Enhanced rendering for complex and person */}
            {(() => {
                const v = node.displayValue || node.value;
                // Handle Complex numbers
                if (typeof v === 'string' && (v.includes('i') || v.includes('"re"'))) {
                    const c = parseComplex(v);
                    if (c) {
                        return (
                            <text x={x} y={y - 2} textAnchor="middle" fontSize={14} fontWeight={600} fill={textColor}>
                                <tspan fill="#8ec5fc">{c.real}</tspan>
                                <tspan fill="#ffb300">{c.imag}</tspan>
                                <tspan fill="#bdbdbd">i</tspan>
                            </text>
                        );
                    }
                }
                // Handle Person objects
                if (typeof v === 'string' && (v.includes('(') || v.includes('"name"'))) {
                    const p = parsePerson(v);
                    if (p) {
                        return (
                            <text x={x} y={y - 4} textAnchor="middle" fontSize={13} fontWeight={600}>
                                <tspan fill="#8ec5fc">{p.name}</tspan>
                                <tspan x={x} y={y + 10} fill="#ffb300">{p.age}</tspan>
                            </text>
                        );
                    }
                }
                // Default rendering
                return (
                    <text x={x} y={y + 6} textAnchor="middle" fontSize={18} fontWeight={600} fill={textColor}>
                        {String(v)}
                    </text>
                );
            })()}
        </g>
    );
    return { lines, nodes };
}

function parsePerson(str) {
    // Example: "Alice (25)" or "Bob (30)"
    const match = str.match(/^(.+?) \((\d+)\)$/);
    if (match) {
        return { name: match[1], age: match[2] };
    }

    // Handle JSON format for Person objects
    try {
        if (str.startsWith('{') && str.endsWith('}')) {
            const obj = JSON.parse(str);
            if (obj && typeof obj.name !== 'undefined' && typeof obj.age !== 'undefined') {
                return { name: obj.name, age: obj.age };
            }
        }
    } catch (e) {
        // Parsing failed, not a valid JSON
    }

    return null;
}

function parseComplex(str) {
    // Example: "1+2i", "-1-3i", "2i", "3"
    const match = str.match(/^(-?\d+(?:\.\d+)?)([+-]\d+(?:\.\d+)?)i$/);
    if (match) {
        return { real: match[1], imag: match[2] };
    }
    // Pure imaginary: "2i"
    const imagOnly = str.match(/^([+-]?\d+(?:\.\d+)?)i$/);
    if (imagOnly) {
        return { real: '0', imag: imagOnly[1] };
    }
    // Pure real: "3"
    const realOnly = str.match(/^(-?\d+(?:\.\d+)?)$/);
    if (realOnly) {
        return { real: realOnly[1], imag: '+0' };
    }

    // Handle JSON format for Complex objects
    try {
        if (str.startsWith('{') && str.endsWith('}')) {
            const obj = JSON.parse(str);
            if (obj && typeof obj.re !== 'undefined' && typeof obj.im !== 'undefined') {
                return {
                    real: obj.re.toString(),
                    imag: (obj.im >= 0 ? '+' : '') + obj.im.toString()
                };
            }
        }
    } catch (e) {
        // Parsing failed, not a valid JSON
    }

    return null;
}


export default function TreeView({ serializedTree }) {
    const [jsonOpen, setJsonOpen] = React.useState(false);

    let values = [];
    let jsonObj = null;
    let structure = null;
    try {
        const obj = JSON.parse(serializedTree);
        if (obj && Array.isArray(obj.values)) {
            // Преобразуем строки 'null' в null
            values = obj.values.map(v => (v === 'null' ? null : v));
            jsonObj = obj;
            if (obj.structure) {
                structure = obj.structure;
            }
        }
    } catch {
        values = serializedTree ? serializedTree.split(/\s+/).filter(Boolean) : [];
    }
    // Строим дерево по level order (ширина в ширину)
    const tree = buildTree(values, structure, 'level');
    const depth = getTreeDepth(tree);
    const nodeSpacingX = 80;
    const nodeSpacingY = 70;
    const treeWidth = Math.max(480, nodeSpacingX * Math.pow(2, depth - 1));
    const treeHeight = nodeSpacingY * depth + 60;

    let svgContent = null;
    if (tree) {
        const { lines, nodes } = renderTreeSVG(tree, treeWidth / 2, 40, treeWidth / 2.2, nodeSpacingY);
        svgContent = (
            <svg
                viewBox={`0 0 ${treeWidth} ${treeHeight}`}
                width="100%"
                height={treeHeight}
                style={{ display: 'block', margin: '0 auto', maxWidth: '100%' }}
            >
                <defs>
                    <linearGradient id="bubble-dark" x1="0" y1="0" x2="1" y2="1">
                        <stop offset="0%" stopColor="#2d2d2d" />
                        <stop offset="100%" stopColor="#404040" />
                    </linearGradient>
                </defs>
                {lines}
                {nodes}
            </svg>
        );
    }

    return (
        <div style={{
            margin: '0 auto',
            maxWidth: 600,
            padding: '24px 0 0 0',
            background: 'none',
            minHeight: 320
        }}>
            <h2 style={{
                color: '#8ec5fc',
                fontWeight: 600,
                marginBottom: 18,
                fontSize: 22,
                letterSpacing: 0.5,
                textAlign: 'center'
            }}>
                {jsonObj && jsonObj.traversal ? `Tree (${jsonObj.traversal})` : 'Tree'}
            </h2>

            {tree ? (
                <div style={{
                    overflowX: 'auto',
                    margin: '0 auto 18px auto',
                    background: 'none',
                    borderRadius: 10,
                    padding: 0,
                    boxShadow: 'none',
                    display: 'flex',
                    justifyContent: 'center',
                    alignItems: 'center',
                    minHeight: 120
                }}>
                    {svgContent}
                </div>
            ) : (
                <div style={{ color: '#888', fontSize: 16, margin: '24px 0', textAlign: 'center' }}>🌳 Tree is empty</div>
            )}

            <div style={{
                fontSize: 13,
                color: '#bdbdbd',
                marginTop: 18,
                textAlign: 'left',
                maxWidth: 520,
                margin: '0 auto'
            }}>
                <button
                    style={{
                        background: 'none',
                        border: 'none',
                        color: '#8ec5fc',
                        fontWeight: 500,
                        fontSize: 13,
                        cursor: 'pointer',
                        padding: 0,
                        marginBottom: 8,
                        outline: 'none',
                        display: 'flex',
                        alignItems: 'center',
                        gap: 4
                    }}
                    onClick={() => setJsonOpen(o => !o)}
                >
                    {jsonOpen ? '▼' : '▶'} <span>{jsonOpen ? 'Hide JSON' : 'Show JSON'}</span>
                </button>
                {jsonOpen && (
                    <pre style={{
                        margin: 0,
                        fontSize: 13,
                        color: '#bdbdbd',
                        background: 'none',
                        whiteSpace: 'pre-wrap',
                        lineHeight: 1.5,
                        padding: 0
                    }}>
                        {jsonObj ? JSON.stringify(jsonObj, null, 2) : serializedTree}
                    </pre>
                )}
            </div>
        </div>
    );
}
