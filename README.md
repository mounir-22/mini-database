# Mini Database Engine in C

A complete implementation of a mini database engine written in C, demonstrating core database concepts including B-trees, paging, and SQL parsing.

## 🏗️ Project Structure

```
mini-database/
├── include/
│   └── database.h          # Main header with all declarations
├── src/
│   ├── main.c              # Entry point and REPL
│   ├── input_buffer.c      # Input handling
│   ├── meta_commands.c     # Meta commands (.exit, .btree, etc.)
│   ├── parser.c            # SQL command parsing
│   ├── row.c               # Row serialization/deserialization
│   ├── pager.c             # Page management and disk I/O
│   ├── table.c             # Database open/close operations
│   ├── constants.c         # B-tree and node size constants
│   ├── btree.c             # B-tree node operations
│   ├── cursor.c            # Table cursor for navigation
│   └── execute.c           # Command execution
├── obj/                    # Compiled object files
├── bin/                    # Final executable
├── tests/                  # Test files
├── Makefile               # Build configuration
└── build.bat              # Windows build script
```

## 🛠️ Features Implemented

### Core Database Operations
- **INSERT** - Add new records with duplicate key detection
- **SELECT** - Retrieve all records in sorted order
- **Meta Commands** - `.exit`, `.btree`, `.constants`

### Low-Level Systems Features
- **Custom Memory Management** - Manual malloc/free with page caching
- **Binary File Format** - Fixed-size pages (4KB) with B-tree storage
- **B-Tree Implementation** - Efficient sorted storage and retrieval
- **Page Management** - Disk I/O with in-memory page caching
- **Row Serialization** - Binary format with fixed schemas

### Architecture Components
1. **REPL Shell** - Interactive command line interface
2. **SQL Parser** - Converts text commands to structured data
3. **B-Tree Engine** - Core storage and indexing
4. **Pager System** - Virtual memory management
5. **Cursor System** - Iterator pattern for table traversal

## 📋 Requirements

### Option 1: GCC/MinGW (Recommended)
- GCC compiler with C99 support
- Make utility (for Makefile)

### Option 2: Microsoft Visual Studio
- Visual Studio Build Tools
- cl.exe compiler

### Option 3: WSL (Windows Subsystem for Linux)
- Ubuntu/Debian with build-essential

## 🚀 Building the Project

### With GCC/MinGW:
```bash
make all
```

### With Microsoft Visual Studio:
First open a "Developer Command Prompt", then:
```cmd
build.bat
```

### Manual compilation:
```bash
gcc -Wall -Wextra -std=c99 -g -Iinclude -o bin/minidb src/*.c
```

## 💡 Usage Examples

### Start the database:
```bash
./bin/minidb mydatabase.db
```

### Basic operations:
```sql
db > insert 1 alice alice@example.com
Executed.

db > insert 2 bob bob@example.com  
Executed.

db > select
(1, alice, alice@example.com)
(2, bob, bob@example.com)
Executed.

db > .exit
```

### Meta commands:
```sql
db > .constants
Constants:
ROW_SIZE: 293
COMMON_NODE_HEADER_SIZE: 6
LEAF_NODE_HEADER_SIZE: 10
LEAF_NODE_CELL_SIZE: 297
LEAF_NODE_SPACE_FOR_CELLS: 4086
LEAF_NODE_MAX_CELLS: 13

db > .btree
Tree:
- leaf (size 2)
  - 1
  - 2
```

## 🧪 Testing

Run the test suite:
```bash
make test
```

Manual testing:
```bash
echo -e "insert 1 test test@example.com\nselect\n.exit" | ./bin/minidb test.db
```

## 🎯 What This Project Demonstrates

### Systems Programming Skills
- **Memory Management**: Custom allocation, page caching
- **File I/O**: Low-level read/write operations
- **Data Structures**: B-tree implementation from scratch
- **Binary Formats**: Row serialization and page layout

### Database Concepts
- **ACID Properties**: Atomic operations, data consistency
- **Indexing**: B-tree for O(log n) lookups
- **Storage Engine**: Page-based storage management
- **Query Processing**: Parse → Plan → Execute pipeline

### C Programming Mastery
- **Pointer Manipulation**: Complex data structure navigation
- **Memory Layout**: Understanding of structs and alignment
- **Error Handling**: Comprehensive error checking
- **Modular Design**: Clean separation of concerns

## 🚧 Future Enhancements

Ready for your portfolio? Consider adding:

### Database Features
- [ ] WHERE clauses with comparison operators
- [ ] UPDATE and DELETE operations  
- [ ] Multiple column indices
- [ ] JOIN operations between tables
- [ ] Transactions and rollback

### Performance Optimizations
- [ ] Node splitting for B-tree growth
- [ ] Page compression
- [ ] Write-ahead logging (WAL)
- [ ] Connection pooling
- [ ] Query optimization

### Advanced Features
- [ ] Network protocol (TCP server)
- [ ] Concurrent connections
- [ ] Data types (strings, dates, floats)
- [ ] Stored procedures
- [ ] Backup/restore functionality

## 📝 Architecture Notes

### Data Flow
1. **Input** → Parser → Statement Object
2. **Statement** → Execution Engine → B-tree Operations  
3. **B-tree** → Cursor → Page Access
4. **Pages** → Pager → Disk I/O

### Memory Layout
```
Page Structure:
[Node Header][Cell 0][Cell 1]...[Cell N]

Cell Structure:  
[Key (4 bytes)][Value (289 bytes)]

Row Structure:
[ID (4)][Username (33)][Email (256)]
```

### File Format
```
Database File:
[Page 0: Root Node][Page 1][Page 2]...[Page N]

Each page = 4096 bytes
Max cells per leaf = 13 rows
```

## 🎓 Learning Resources

To understand this project better, study:
- **Database Internals** by Alex Petrov
- **SQLite source code** (similar architecture)
- **Introduction to Algorithms** (B-tree chapter)
- **Operating Systems concepts** (file systems)

## 💼 Portfolio Value

This project demonstrates:
✅ **Real systems programming** - Not just algorithms  
✅ **Production-quality code** - Memory safety, error handling  
✅ **Database expertise** - Core CS knowledge  
✅ **Independent learning** - Complex project from scratch  
✅ **Performance awareness** - O(log n) operations, caching

Perfect for interviews at systems companies (databases, storage, infrastructure).

---

**Built with ❤️ and pure C** - No frameworks, just fundamental computer science principles.