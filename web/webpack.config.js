const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const CopyWebpackPlugin = require('copy-webpack-plugin');

// Get the repository name from package.json homepage
const packageJson = require('./package.json');
const repoName = packageJson.homepage ? 
  new URL(packageJson.homepage).pathname : 
  '';

module.exports = {
  entry: './src/index.js',
  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: 'bundle.js',
    clean: true, // очищать dist при сборке
    publicPath: process.env.NODE_ENV === 'production' ? repoName + '/' : '/'
  },
  module: {
    rules: [
      {
        test: /\.jsx?$/,
        exclude: /node_modules/,
        use: {
          loader: 'babel-loader',
        },
      },
    ],
  },
  resolve: {
    extensions: ['.js', '.jsx'],
  },
  devServer: {
    static: path.join(__dirname, 'public'),
    compress: true,
    port: 8080,
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: './public/index.html',
    }),
    new CopyWebpackPlugin({
      patterns: [
        { from: 'public/tree.js', to: 'tree.js' },
        { from: 'public/tree.wasm', to: 'tree.wasm' },
      ],
    }),
  ],
};