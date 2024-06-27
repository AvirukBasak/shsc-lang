# Shsc

[![Beta](https://img.shields.io/badge/Version-2.2%20Beta-deepgreen.svg)](https://github.com/AvirukBasak/shsc-lang/releases/tag/v2.0)

A scripting language inspired by C, Python and Javascript.

To learn more about the language, read [`docs/LanguageDocs.md`](docs/LanguageDocs.md).

### Build
- Dependencies:
    - `make` To build
    - `bison` To generate parser
    - A C compiler (eg `gcc`)
#### Linux
- Build with `install.sh`
- Executable path is `target/shsc-rel`

#### Windows
- Download [`Git Bash`](https://git-scm.com/)
- Install Git Bash. Now you can run bash on Windows.
- Download [`Make`](https://gnuwin32.sourceforge.net/packages/make.htm)
- Download [`Bison`](https://github.com/lexxmark/winflexbison/releases)
- Download [`MinGW`](https://github.com/skeeto/w64devkit/releases)
- Extract the files and place them in some folder
- Add the necessary paths to the user PATH
- The user PATH is accessible via `Add or modify user environment variables` or something.
- Open Git Bash in project root
- Run `install.sh`

For Windows users, you'll need to use `cygwin` or `git bash` to get `make` working.
Idk if you can compile it on MSVC so give it a shot and maybe contribute an `md` on it.

### VSCode Syntax Highlighting
See [`Shsc Syntax Highlighting`](https://github.com/AvirukBasak/shsc-syntax-highlighting)

### Usage
```
USAGE:
  shsc              [FILENAMES] execute files listed as args
  shsc <flags>      [FILENAMES] provide with additional flags
FLAGS:
  -r    --run       [FILENAME]  run files listed in file
  -t    --ast       [FILENAME]  save AST as JSON to file
  -ldbg --lex-debug [FILENAME]  produce formatted JSON
  -tf   --astf      [FILENAME]  produce formatted JSON
  -h    --help                  view this message
  -v    --version               version info
```

Examples at [`examples/`](examples/).

### Run Shsc script
```
make run ARGS="examples/helloworld.txt"
```

or, if properly loaded in `PATH` environment variable
```
shsc examples/helloworld.txt
```

**NOTE**: File extension means nothing to the interpreter as long as the code inside is valid. However, the syntax highlighting plugin will work only for `.shsc` files.

### Features Added
- [x] Modules
- [x] Procedure definitions
- [x] Procedure calls
- [x] Function arguments
- [x] Call stack
- [x] Lambda functions
- [x] Interop with C
- [x] Variables
- [x] Destructuring
- [x] Constants
- [x] Weak references
- [x] Local scopes
- [x] Function scopes
- [x] Error stack traces
- [x] Contextual functions (OOP)
- [x] Literals
    - [x] `bul` Boolean
    - [x] `chr` Char
    - [x] `i64` Int 64-bit
    - [x] `f64` Float 64-bit
    - [x] `str`  String
    - [x] `interp_str` Format string
    - [x] `lst` List
    - [x] `map` Hash map
- [x] Reference counted GC
- [x] Range based for
- [x] Iterable based for
- [x] While
- [x] Break and continue
- [x] If-else
- [ ] Arithmetic right shift
- [ ] Shift for `f64` LHS
- [x] All other operators
- [x] `&&`, `||` and ternary operator short-circuiting
- [x] Built-in functions

### List File
 - List file is specified using the `--run` flag
 - This loads multiple files for execution under a single runtime
 - Each line of the list file has a single shsc file path
 - Spaces in file path is valid and quotes not required
 - If shsc fails to read one file, it'll skip to next file
 - If shsc fails to parse any file, it'll report error and exit

#### Example
The file paths should be relative to the directory where `shsc` will be executed.
```
file1.txt
file2.shsc
file3.txt
file name with spaces.txt
file4.some_extension
file that has no extension
```

### Example use
```
# tested using tests/build.txt list file
shsc -r tests/build.txt
```

```
# tested on examples/factorial.txt
shsc -tf ast.json examples/factorial.txt
```

### Docs
- Lexer interface at [`docs/LexerInterface.md`](docs/LexerInterface.md)
- Language docs at [`docs/LanguageDocs.md`](docs/LanguageDocs.md)
- Bytecode specs at [`ShscIrSpec.md`](https://github.com/AvirukBasak/shsc-runtime/blob/main/docs/ShscIrSpec.md)
- Contribution guidelines at [`docs/CONTRIBUTING.md`](docs/CONTRIBUTING.md)
- Memory usage test [`docs/memprofile`](docs/memprofile)

### Tests
- Tested on [`tests/test.txt`](tests/test.txt).
- Lexer output at [`tests/Tokens.md`](tests/Tokens.md).
- AST output at [`tests/SyntaxTree.json`](tests/SyntaxTree.json).

### Todo
- Complete the features todo list above
