# Scsh
World's most sh*tty programming language.

### Usage
- Build with `make`
- Copy the executable from `taget/`.
- Examples at [`examples/`](examples/).

```
USAGE:
  scsh [FILENAMES]         execute files listed as args
  scsh <flags> [FILENAMES] provide with additional flags
FLAGS:
  -r  --run  [FILENAME]    run files listed in file
  -t  --ast  [FILENAME]    save AST as JSON to file
  -tf --astf [FILENAME]    produce formatted JSON
  -h  --help               view this message
```

### Example use
```
# tested on examples/factorial.txt
scsh -tf ast.json examples/factorial.txt
```

### Docs
- Lexer interface at [`docs/LexerInterface.md`](docs/LexerInterface.md)
- Language specs at [`docs/LanguageSpec.md`](docs/LanguageSpec.md)
- Syntax specs at [`docs/LanguageSyntax.md`](docs/LanguageSyntax.md)
- Bytecode specs at [`ScshIrSpec.md`](https://github.com/AvirukBasak/scsh-runtime/blob/main/docs/ScshIrSpec.md)
- Contribution guidelines at [`docs/CONTRIBUTING.md`](docs/CONTRIBUTING.md)

### Tests
- Tested on [`tests/test.txt`](tests/test.txt).
- Lexer output at [`tests/Tokens.md`](tests/Tokens.md).
- AST output at [`tests/SyntaxTree.json`](tests/SyntaxTree.json).

### Todo
- Build AST management modules.
- Build the symbols table.
- Build the runtime.
