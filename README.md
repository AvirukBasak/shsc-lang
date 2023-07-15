# Scheisse Script
World's most sh*tty scripting language.

### Usage
- Build with `make`
- Copy the executable from `taget/`.

```
USAGE:
  scsh [FILENAMES]               execute files listed as args
  scsh -b or --build [FILENAME]  execute files listed in file
  scsh -t or --ast [FILENAME]    save AST as JSON to file
  scsh -h or --help              view this message
```

### Docs
- Example code at [`tests/test.txt`](tests/test.txt).
- Syntax specs at [`docs/Syntax.md`](docs/Syntax.md).
- Contribution guidelines at [`docs/CONTRIBUTING.md`](docs/CONTRIBUTING.md).

### Tests
- Tested on [`tests/test.txt`](tests/test.txt).
- Lexer output at [`docs/TestResult.md`](docs/TestResult.md).
- AST output at [`docs/SyntaxTree.json`](docs/SyntaxTree.json).

### Todo
- Build AST management modules.
- Build the symbols table.
- Build the runtime.
