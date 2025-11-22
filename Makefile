CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# Create directories if they don't exist
MKDIR_P = mkdir
ifeq ($(OS),Windows_NT)
    TARGET = $(BINDIR)/minidb.exe
    RM = rmdir /s /q
    MKDIR_P = mkdir
else
    TARGET = $(BINDIR)/minidb
    RM = rm -rf
endif

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Default target
all: directories $(TARGET)

# Create directories
directories:
	@if not exist "$(OBJDIR)" $(MKDIR_P) $(OBJDIR)
	@if not exist "$(BINDIR)" $(MKDIR_P) $(BINDIR)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

# Compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Clean build files
clean:
ifeq ($(OS),Windows_NT)
	@if exist "$(OBJDIR)" $(RM) $(OBJDIR)
	@if exist "$(BINDIR)" $(RM) $(BINDIR)
else
	$(RM) $(OBJDIR) $(BINDIR)
endif

# Run a simple test
test: $(TARGET)
	@echo Testing the database...
	@echo "insert 1 user1 person1@example.com" > test_commands.txt
	@echo "insert 2 user2 person2@example.com" >> test_commands.txt
	@echo "select" >> test_commands.txt
	@echo ".exit" >> test_commands.txt
	$(TARGET) test.db < test_commands.txt
	@del test_commands.txt test.db

.PHONY: all clean test directories