# Shsc

[![Beta](https://img.shields.io/badge/Version-2.4%20Beta-deepgreen.svg)](https://github.com/AvirukBasak/shsc-lang/releases/tag/v2.4)

A scripting language inspired by C, Python and Javascript.

To learn more about the language, read [`docs/LanguageDocs.md`](docs/LanguageDocs.md).

### Online Interpreter
Run your codes online at [shsc-online-repl.vercel.app](https://shsc-online-repl.vercel.app).

#### Screenshot
<img width="935" height="726" alt="image" src="https://github.com/user-attachments/assets/eef0a512-f817-4b21-b3a0-6a070924d924" />

### Build
- Dependencies:
    - `make` To build
    - `bison` To generate parser
    - A C compiler (e.g. GCC or Clang)

### Clone
```
git clone https://github.com/AvirukBasak/shsc-lang.git
cd shsc-lang
git submodule update --init
git pull --recurse-submodules
```

#### Linux
- Build with `install.sh`
- Executable path is `target/shsc-rel`

#### Windows

On Windows you can use either of the following toolsets with specific benefits or drawbacks:

| Tool Set                                                        | Recommended     | GNU Make | GDB | Clang | Address Sanitizer (General) | Address Sanitizer (Detect Leaks) |
|-----------------------------------------------------------------|-----------------|----------|-----|-------|-----------------------------|----------------------------------|
| [`w64devkit`](https://github.com/skeeto/w64devkit/releases)     | For Usage       | Yes      | Yes | No    | No                          | No                               |
| [`LLVM MinGW`](https://github.com/mstorsjo/llvm-mingw/releases) | For Development | No       | No  | Yes   | Yes                         | No                               |

##### Additional Links
- [`GNU Make`](https://gnuwin32.sourceforge.net/packages/make.htm) as build tool
- [`Bison`](https://github.com/lexxmark/winflexbison/releases) for generating parser

##### Steps
- Extract the files and place them in some folder
- Add the necessary paths to the user PATH
- The user PATH is accessible via `Add or modify user environment variables` or something.
- Open CMD in project root
- Run `install.sh`

### VSCode Syntax Highlighting
See [`Shsc Syntax Highlighting`](https://github.com/AvirukBasak/shsc-syntax-highlighting)

### Usage
```
Usage:
  shsc [options] file... -args args...
Options:
  [-v    | --version]                   Show version
  [-h    | --help   ]                   Show this help message
  [-r    | --run    ]   listfile        Run scripts listed in the listfile
  [-t    | --ast    ]   outfile file... Parse file and save AST as JSON in outfile
  [-tf   | --astf   ]   outfile file... Parse file and save  formatted AST as JSON in outfile
  [-ldbg | --lex-debug] file...         Scan file and print lexer debug output
Notes:
  > file... - one or more shsc code files
  > args... - arguments passed to the main:main shsc method; are optional
  > flag -args can be added after file... or after listfile in case of --run
  > passing a dash (-) anywhere as filename will read from stdin or write to stdout
```

Examples at [`examples/`](examples/).

### Run Shsc Script
```
make run ARGS="examples/fibonacci.txt"
```

or, if properly loaded in `PATH` environment variable
```
shsc examples/fibonacci.txt
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
 - Paths are relative to directory of list file
 - Spaces in file path is valid and quotes not required
 - If shsc fails to read or parse any file, it'll report error and exit

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

### Other Example Use
Run the tests using the list file
```
# tested using examples/inheritance/listfile list file
shsc -r examples/inheritance/listfile -args abc 123 1 2 3
```
Output the AST to a file
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
