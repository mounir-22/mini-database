@echo off
echo Validating Mini Database Engine source files...
echo.

echo Checking directory structure...
if not exist "include" echo ERROR: include directory missing && goto error
if not exist "src" echo ERROR: src directory missing && goto error
if not exist "tests" echo ERROR: tests directory missing && goto error

echo Checking header files...
if not exist "include\database.h" echo ERROR: database.h missing && goto error

echo Checking source files...
if not exist "src\main.c" echo ERROR: main.c missing && goto error
if not exist "src\input_buffer.c" echo ERROR: input_buffer.c missing && goto error
if not exist "src\meta_commands.c" echo ERROR: meta_commands.c missing && goto error
if not exist "src\parser.c" echo ERROR: parser.c missing && goto error
if not exist "src\row.c" echo ERROR: row.c missing && goto error
if not exist "src\pager.c" echo ERROR: pager.c missing && goto error
if not exist "src\table.c" echo ERROR: table.c missing && goto error
if not exist "src\constants.c" echo ERROR: constants.c missing && goto error
if not exist "src\btree.c" echo ERROR: btree.c missing && goto error
if not exist "src\cursor.c" echo ERROR: cursor.c missing && goto error
if not exist "src\execute.c" echo ERROR: execute.c missing && goto error

echo Checking documentation...
if not exist "README.md" echo WARNING: README.md missing
if not exist "SETUP.md" echo WARNING: SETUP.md missing

echo.
echo ✓ All essential files are present!
echo ✓ Project structure is complete!
echo.
echo Next steps:
echo 1. Install a C compiler (see SETUP.md)
echo 2. Build with: make all (or manual compilation)
echo 3. Run with: bin\minidb.exe test.db
echo.
goto end

:error
echo.
echo ❌ Validation failed! Please ensure all files are present.
echo.

:end
pause