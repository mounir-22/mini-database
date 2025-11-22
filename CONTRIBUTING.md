# Contributing to Mini Database Engine

Thank you for your interest in contributing to this project! Here are some guidelines to help you get started.

## Development Setup

1. **Clone the repository**:
   ```bash
   git clone https://github.com/mounir-22/mini-database.git
   cd mini-database
   ```

2. **Set up development environment**:
   - Follow the instructions in `SETUP.md` to install a C compiler
   - Ensure you have `make` or use the provided `build.bat`

3. **Build the project**:
   ```bash
   make all
   ```

4. **Run tests**:
   ```bash
   make test
   ```

## How to Contribute

### Reporting Issues
- Use GitHub Issues to report bugs or suggest features
- Include steps to reproduce the issue
- Provide system information (OS, compiler version)

### Submitting Changes
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Make your changes
4. Add tests for new functionality
5. Ensure all tests pass
6. Commit your changes (`git commit -m 'Add amazing feature'`)
7. Push to the branch (`git push origin feature/amazing-feature`)
8. Open a Pull Request

## Code Style Guidelines

### C Code Style
- Use 4 spaces for indentation (no tabs)
- Keep lines under 100 characters
- Use meaningful variable and function names
- Add comments for complex logic
- Follow existing code formatting patterns

### Example:
```c
// Good
void serialize_row(Row* source, void* destination) {
    memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
    memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
    memcpy(destination + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

// Bad
void ser_row(Row*s,void*d){memcpy(d+ID_OFFSET,&(s->id),ID_SIZE);/*...*/ }
```

## Project Structure

- `include/` - Header files
- `src/` - Source code implementation
- `tests/` - Test files and examples
- `docs/` - Additional documentation

## Areas for Contribution

### High Priority
- [ ] Node splitting for B-tree growth
- [ ] WHERE clause implementation
- [ ] UPDATE and DELETE operations
- [ ] Comprehensive test suite
- [ ] Memory leak detection

### Medium Priority
- [ ] Query optimization
- [ ] Secondary indices
- [ ] Transaction support
- [ ] Better error messages
- [ ] Performance benchmarks

### Advanced Features
- [ ] Network protocol support
- [ ] Concurrent access
- [ ] Write-ahead logging
- [ ] Backup/restore functionality

## Testing

### Running Tests
```bash
# Run all tests
make test

# Manual testing
echo -e "insert 1 test test@example.com\nselect\n.exit" | ./bin/minidb test.db
```

### Adding Tests
- Add test cases to `tests/` directory
- Include both positive and negative test cases
- Test edge cases and error conditions
- Update test documentation

## Documentation

- Keep README.md up to date
- Document new features and APIs
- Add examples for new functionality
- Update architecture diagrams if needed

## Questions?

Feel free to open an issue for questions or reach out to the maintainers.

Happy coding! 🚀