export async function createTree() {
  // Simple direct approach to load the WebAssembly module
  if (!window.TreeModule) {
    try {
      await new Promise((resolve, reject) => {
        // Get the repository name from the current URL or from window.publicPath
        let baseUrl = '';
        if (window.location.hostname === 'alekhinalex.github.io') {
          baseUrl = window.publicPath || '/BinaryTree';
          if (!baseUrl.endsWith('/')) {
            baseUrl += '/';
          }
        }
        
        console.log('Loading WebAssembly from base URL:', baseUrl);
        
        // Create script element
        const script = document.createElement('script');
        script.src = `${baseUrl}tree.js`;
        script.async = true;
        
        // Set WASM binary path for the loader to find
        window.wasmBinaryFile = `${baseUrl}tree.wasm`;
        
        // Handle load events
        script.onload = () => {
          console.log('WebAssembly script loaded successfully');
          resolve();
        };
        script.onerror = (e) => {
          console.error('Failed to load WebAssembly script:', e);
          reject(new Error(`Failed to load WebAssembly from ${script.src}`));
        };
        
        // Add to document
        document.body.appendChild(script);
      });
    } catch (error) {
      console.error('WebAssembly loading error:', error);
      throw new Error(`WebAssembly loading error: ${error.message}`);
    }
  }
  
  try {
    // Initialize the module
    if (typeof window.TreeModule !== 'function') {
      throw new Error('TreeModule is not properly loaded');
    }
    
    return await window.TreeModule();
  } catch (error) {
    console.error('TreeModule initialization error:', error);
    throw new Error(`TreeModule initialization error: ${error.message}`);
  }
}
