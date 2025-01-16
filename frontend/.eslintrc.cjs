module.exports = {
  root: true,
  parser: '@typescript-eslint/parser',
  parserOptions: {
    ecmaVersion: 2020,
    sourceType: 'module',
    ecmaFeatures: {
      jsx: true,
    },
  },
  plugins: ['react', '@typescript-eslint', 'prettier'],
  extends: [
    'eslint:recommended',
    'plugin:react/recommended',
    'plugin:@typescript-eslint/recommended',
    'plugin:prettier/recommended', // Integra ESLint con Prettier
  ],
  rules: {
    'prettier/prettier': 'error', // Marca como error si no sigue las reglas de Prettier
    semi: ['error', 'always'], // Asegura que el punto y coma siempre se use
    'react/react-in-jsx-scope': 'off', // No es necesario importar React en Vite + JSX
  },
  settings: {
    react: {
      version: 'detect',
    },
  },
};
