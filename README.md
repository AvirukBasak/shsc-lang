# Shsc
World's most sh*tty programming language.

### Build
For Unix and Unix-like OS users:
- Build with `make`
- Copy the executable from `taget/`.
- Alternatively just run `make install`.
- You might need root privileges to install.

For Windows users, you'll probably need to use `cygwin` or `git bash` to get `make` working.

### Usage
```
USAGE:
  shsc [FILENAMES]         execute files listed as args
  shsc <flags> [FILENAMES] provide with additional flags
FLAGS:
  -r  --run  [FILENAME]    run files listed in file
  -t  --ast  [FILENAME]    save AST as JSON to file
  -tf --astf [FILENAME]    produce formatted JSON
  -h  --help               view this message
  -v  --version            version info
```

Examples at [`examples/`](examples/).

### List File
 - Each line of the list file has a single file path
 - Spaces in file path is valid and quotes not required
 - If shsc fails to read one file, it'll skip to next file
 - If shsc fails to parse any file, it'll report error and exit

#### Example
The file paths should be relative to the directory where `shsc` will be executed.
```
file1.txt
file2.txt
file3.txt
file name with spaces.txt
file4.some_extension
```

### Example use
```
# tested using tests/build.txt
shsc -tf tests/SyntaxTree.json -r tests/build.txt
```

```
# tested on examples/factorial.txt
shsc -tf ast.json examples/factorial.txt
```

### Docs
- Lexer interface at [`docs/LexerInterface.md`](docs/LexerInterface.md)
- Language specs at [`docs/LanguageSpec.md`](docs/LanguageSpec.md)
- Syntax specs at [`docs/LanguageSyntax.md`](docs/LanguageSyntax.md)
- Bytecode specs at [`ShscIrSpec.md`](https://github.com/AvirukBasak/shsc-runtime/blob/main/docs/ShscIrSpec.md)
- Contribution guidelines at [`docs/CONTRIBUTING.md`](docs/CONTRIBUTING.md)

### Tests
- Tested on [`tests/test.txt`](tests/test.txt).
- Lexer output at [`tests/Tokens.md`](tests/Tokens.md).
- AST output at [`tests/SyntaxTree.json`](tests/SyntaxTree.json).

### Todo
- Implement various operators and type coercion systems.
- Switch `statements` to left recursive productions.
