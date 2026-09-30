/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./src/**/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {
      colors: {
        'drdo-blue': '#1e3a8a',
        'drdo-gray': '#f3f4f6',
      }
    },
  },
  plugins: [],
}
