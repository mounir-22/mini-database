@echo off
echo Building Mini Database Engine...

REM Create directories
if not exist obj mkdir obj
if not exist bin mkdir bin

REM Compile each source file
cl /c /Iinclude /Foobj\ src\main.c
cl /c /Iinclude /Foobj\ src\input_buffer.c
cl /c /Iinclude /Foobj\ src\meta_commands.c
cl /c /Iinclude /Foobj\ src\parser.c
cl /c /Iinclude /Foobj\ src\row.c
cl /c /Iinclude /Foobj\ src\pager.c
cl /c /Iinclude /Foobj\ src\table.c
cl /c /Iinclude /Foobj\ src\constants.c
cl /c /Iinclude /Foobj\ src\btree.c
cl /c /Iinclude /Foobj\ src\cursor.c
cl /c /Iinclude /Foobj\ src\execute.c

REM Link the executable
link /OUT:bin\minidb.exe obj\*.obj

echo Build complete! Run with: bin\minidb.exe test.db