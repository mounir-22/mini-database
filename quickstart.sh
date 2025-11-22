#!/bin/bash

# Quick Start Script for Mini Database Engine
# This script helps new users get started quickly

echo "🚀 Mini Database Engine Quick Start"
echo "=================================="
echo

# Check if we're in the right directory
if [ ! -f "include/database.h" ]; then
    echo "❌ Error: Please run this script from the mini-database root directory"
    exit 1
fi

echo "📁 Project structure looks good!"

# Check for C compiler
if command -v gcc &> /dev/null; then
    COMPILER="gcc"
    echo "✅ Found GCC compiler"
elif command -v clang &> /dev/null; then
    COMPILER="clang" 
    echo "✅ Found Clang compiler"
else
    echo "❌ No C compiler found. Please install GCC or Clang first."
    echo "   See SETUP.md for installation instructions."
    exit 1
fi

# Check for make
if command -v make &> /dev/null; then
    BUILD_CMD="make all"
    echo "✅ Found Make utility"
else
    BUILD_CMD="$COMPILER -std=c99 -Wall -Wextra -g -Iinclude -o bin/minidb src/*.c"
    echo "⚠️  Make not found, will use direct compilation"
fi

echo

# Create directories
echo "📂 Creating build directories..."
mkdir -p bin obj

# Build the project
echo "🔨 Building the database engine..."
if eval $BUILD_CMD; then
    echo "✅ Build successful!"
else
    echo "❌ Build failed. Please check the error messages above."
    exit 1
fi

echo

# Run a quick test
echo "🧪 Running a quick test..."
echo -e "insert 1 alice alice@example.com\ninsert 2 bob bob@example.com\nselect\n.exit" | ./bin/minidb quickstart.db

echo
echo "🎉 Success! Your mini database engine is working!"
echo
echo "Next steps:"
echo "1. Try: ./bin/minidb mydatabase.db"
echo "2. Read the README.md for detailed usage"
echo "3. Check out tests/demo_commands.txt for examples"
echo "4. Explore the source code in src/"
echo
echo "Happy coding! 🚀"