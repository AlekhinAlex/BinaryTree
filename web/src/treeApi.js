export async function createTree() {
  if (!window.TreeModule) {
    await new Promise((resolve, reject) => {
      const script = document.createElement('script');
      script.src = './tree.js';
      script.onload = resolve;
      script.onerror = reject;
      document.body.appendChild(script);
    });
  }
  const module = await window.TreeModule();
  return module;
}