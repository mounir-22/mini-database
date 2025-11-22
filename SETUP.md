# Setting Up C Development Environment for Windows

This guide explains how to set up a C compiler to build the Mini Database Engine project.

## Option 1: Install MinGW-W64 (Recommended)

### Using Chocolatey (if available):
```powershell
# Install Chocolatey first if not available:
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))

# Install MinGW-W64
choco install mingw
```

### Manual Installation:
1. Download MinGW-W64: https://www.mingw-w64.org/downloads/
2. Or download from MSYS2: https://www.msys2.org/
3. Add to PATH: `C:\msys64\mingw64\bin` (or wherever installed)

### Verify Installation:
```bash
gcc --version
make --version
```

## Option 2: Visual Studio Build Tools

### Install Visual Studio Community:
1. Download: https://visualstudio.microsoft.com/downloads/
2. Install with "Desktop development with C++" workload
3. Open "Developer Command Prompt for VS"

### Build with MSVC:
```cmd
# In Developer Command Prompt:
cd C:\myenv\c\mini-database
build.bat
```

## Option 3: Windows Subsystem for Linux (WSL)

### Install WSL:
```powershell
wsl --install
```

### Install Ubuntu and build tools:
```bash
sudo apt update
sudo apt install build-essential
cd /mnt/c/myenv/c/mini-database
make all
```

## Building the Project

### Once you have a C compiler:

#### With Make (MinGW/WSL):
```bash
make all
```

#### With manual compilation:
```bash
gcc -std=c99 -Wall -Wextra -g -Iinclude -o bin/minidb.exe src/*.c
```

#### Test the build:
```bash
make test
```

### Running the Database:
```bash
./bin/minidb.exe mydatabase.db
```

## Troubleshooting

### Common Issues:

1. **"gcc not found"**
   - Check PATH environment variable
   - Restart terminal after installation

2. **"make not found"**
   - Install make separately or use manual compilation

3. **Compilation errors**
   - Ensure all source files are present
   - Check include paths

### Alternative: Online C Compilers

For quick testing, you can use:
- **Replit**: https://replit.com/
- **Compiler Explorer**: https://godbolt.org/
- **OnlineGDB**: https://www.onlinegdb.com/

Copy the source files to these platforms for testing.

## Next Steps

Once compiled successfully:
1. Run `./bin/minidb.exe test.db`
2. Try the example commands from README.md
3. Explore the code structure
4. Add your own features!

For development, consider using VS Code with the C/C++ extension for better IntelliSense and debugging support.