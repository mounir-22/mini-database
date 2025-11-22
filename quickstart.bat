@echo off
echo 🚀 Mini Database Engine Quick Start
echo ==================================
echo.

REM Check if we're in the right directory
if not exist "include\database.h" (
    echo ❌ Error: Please run this script from the mini-database root directory
    pause
    exit /b 1
)

echo 📁 Project structure looks good!

REM Check for GCC
gcc --version >nul 2>&1
if %errorlevel%==0 (
    set COMPILER=gcc
    echo ✅ Found GCC compiler
    goto :build_check
)

REM Check for Clang
clang --version >nul 2>&1
if %errorlevel%==0 (
    set COMPILER=clang
    echo ✅ Found Clang compiler
    goto :build_check
)

REM Check for MSVC
cl >nul 2>&1
if %errorlevel%==0 (
    set COMPILER=cl
    echo ✅ Found MSVC compiler
    goto :build_check
)

echo ❌ No C compiler found. Please install one of:
echo    - MinGW-W64 (recommended)
echo    - Visual Studio Build Tools
echo    - Clang
echo.
echo See SETUP.md for installation instructions.
pause
exit /b 1

:build_check
echo.

REM Create directories
echo 📂 Creating build directories...
if not exist bin mkdir bin
if not exist obj mkdir obj

REM Build the project
echo 🔨 Building the database engine...

if "%COMPILER%"=="gcc" (
    %COMPILER% -std=c99 -Wall -Wextra -g -Iinclude -o bin/minidb.exe src/*.c
) else if "%COMPILER%"=="clang" (
    %COMPILER% -std=c99 -Wall -Wextra -g -Iinclude -o bin/minidb.exe src/*.c
) else if "%COMPILER%"=="cl" (
    cl /std:c99 /W4 /Iinclude /Febin/minidb.exe src/*.c
)

if %errorlevel%==0 (
    echo ✅ Build successful!
) else (
    echo ❌ Build failed. Please check the error messages above.
    pause
    exit /b 1
)

echo.

REM Run a quick test
echo 🧪 Running a quick test...
(
echo insert 1 alice alice@example.com
echo insert 2 bob bob@example.com
echo select
echo .exit
) | bin\minidb.exe quickstart.db

echo.
echo 🎉 Success! Your mini database engine is working!
echo.
echo Next steps:
echo 1. Try: bin\minidb.exe mydatabase.db
echo 2. Read the README.md for detailed usage
echo 3. Check out tests\demo_commands.txt for examples
echo 4. Explore the source code in src\
echo.
echo Happy coding! 🚀
echo.
pause