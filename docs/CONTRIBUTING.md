# Contribute to Shsc

Thank you for your interest in contributing to Shsc!
We welcome contributions from the community to make Shsc better.

Before you get started, please take a moment to read and follow these guidelines.

## Table of Contents
- [Project Overview](#project-overview)
- [Syntax](#syntax)
- [Module Structure](#module-structure)
- [Linker Errors](#linker-errors)
- [Naming Conventions](#naming-conventions)
- [Memory Management](#memory-management)
- [Address Sanitizer](#address-sanitizer)
- [Clangd LSP](#clangd)
- [Devtools Directory](#devtools-directory)
- [Contributing Guidelines](#contributing-guidelines)
- [Lexer Guidelines](LexerInterface.md)
- [Language Docs](LanguageDocs.md)

<!-- [Bytecode Spec](https://github.com/AvirukBasak/shsc-runtime/blob/main/docs/ShscIrSpec.md) -->

## Project Overview
Shsc is an interpreter written in C for a custom-designed programming language.

## Syntax
The syntax for this language can be found in the file [LanguageDocs.md](LanguageDocs.md).

## Module Structure
Modules in this C project have the `.c.h` extension and are directly included in the top-level `.c` file from lower-level directories.

Note that `.c.h` files are not compiled separately from the Makefile.

## Linker Errors
To avoid linker errors, ensure that you include the appropriate `.c.h` files in the respective top-level `.c` files.

If you encounter linker errors, double-check if you have missed any necessary `.c.h` files.

## Naming Conventions
- Lexer functions are prefixed with `lex_`.
- Parser functions are prefixed with `parse_`.
- Input-output wrappers are prefixed with `io_`.
- AST (Abstract Syntax Tree) functions are prefixed with `ast_`.
- Runtime functions are prefixed with `rt_`.
- Built-in API funcions are prefixed with `fn_`.
- Operator API functions are prefied with `op_`.
- Custom-defined types are suffixed with `_t`.
- Struct types follow the convention `prefix_TypeName_t`, where `TypeName` uses camel case and `prefix` can be any prefix associated with the type.
- Struct declarations are placed in files based on whether their inner member definitions need to be localized to that single file or visible globally.
- Constructors for struct types must be named `prefix_TypeName()`.
- Specialized constructors and functions can have names like `prefix_TypeName_something_something`, indicating that the function `something_something` is related to `TypeName_t` within the `prefix` namespace.
- The underscore (`_`) in function names and global variables is generally significant and is commonly used for namespacing purposes.
- You can even do `prexfixA_prefixB_prefixC_type_or_function`.
- For headers and source files dedicated to a struct type, name the file as the struct name.
- For eg, if struct type is `rt_Data_t`, files maybe named as `Data.h` and `Data.c.h`.

## The eval functions
These are the functions listed in the `src/runtime/eval.h` and defined in `src/runtime/*.c.h` files.

Each of these functions evaluate a part of the AST.

### Code evaluation
The following functions evaluate code and return a `rt_ControlStatus_t`. The control status is used to control the flow of the program.
- `rt_eval_Statements`
- `rt_eval_Statements_newscope`
- `rt_eval_Statement`
- `rt_eval_CompoundSt`
- `rt_eval_IfBlock`
- `rt_eval_ElseBlock`
- `rt_eval_WhileBlock`
- `rt_eval_ForBlock`

### Expression evaluation
The following functions evaluate expressions and **MUST** make a call to either `rt_VarTable_acc_setadr()` or `rt_VarTable_acc_setval()` to set the accumulator.

- `rt_eval_Expression`
- `rt_eval_Literal`
- `rt_eval_Identifier`
- `rt_eval_CommaSepList`
- `rt_eval_AssociativeList`

The `RT_ACC_DATA` macro is used to get the accumulator data **ONLY** if one of the above functions was called immediately before.

## Memory Management
If a function can call `free` upon a pointer without any casts and causing no error or warning, the function is said to own it.

- If a function returns a new heap pointer, it should be documented that the returned pointer is to be freed.
- Constructor and destructor functions should be used to allocate and free composite or struct based heap objects.
- A destructor function should take a pointer to a pointer and assign the original pointer to `NULL` once freed.
- If a function does not modify a passed heap pointer or object, the pointer **MUST** be marked as `const` in the formal parameters.
- If a function must make changes to a heap object **ONLY** then should the pointer be passed as non-`const`.

## Using the `RT_ACC_DATA` macro
Definitiion
```
rt_VarTable_acc_get()->adr
    ? rt_VarTable_acc_get()->adr
    : &rt_VarTable_acc_get()->val
```

Clearly, this is a very dangerous macro to use. This macro must be used **IF AND ONLY IF** it is immediately preceeded by one of the functions listed in the `src/runtime/eval.h` and defined in `src/runtime/*.c.h` files.

This is because the accumulator is a two-faced serpent. It can either be a pointer to a heap object or a direct value copy. This takes care of both l-values and r-values but in a very dangerous way.

In the event that it a pointer to a heap object, by chance if that scope is popped, the pointer will be dangling and the program will crash.


#### Explicitly casting to non-const
If you have a pointer to memory and want to explicitly pass ownership, even if you don't currently own it, you may explicitly cast it to non-`const`.
However, be cautious as this can result in poor code quality, so use it judiciously.

For example, a list of `const` struct pointers may be created, but the functions of the list can't free them coz they may still have other references.
So you may need to explicitly cast to non-`const` and free them from the list only if you're **SURE** that there is no other reference.

## Address Sanitizer
Using an address sanitizer is **mandatory** to ensure code quality and catch memory issues early.
Make sure to run the address sanitizer during development and testing.

The Makefile has a target `run-sanitize` for this purpose.

Debug builds are built with `-fsanitize=address`.

**WARNING** Using address sanitizer will significantly increase memory usage (like about 500+ MiB for a single loop).
For more information, see [`Memory Usage Tests`](memprofile/README.md#memory-usage-tests).

Note that you cannot run the address sanitizer on Windows.

## Clangd
This section will apply to you only if you're using `clangd` LSP.

You'll need to ignore clangd errors and warnings in `bison` generated files.
Clangd will use the `compile_flags.txt` file.

## Devtools directory
The `devtools` directory contains scripts and tools to help with development.
List of tools:
- `mk_header_guards.sh` Auto generate header guards for all files given a header prefix and the directory.
- `ren_files.sh` Bulk rename files by replacing a string in old filenames with a new string.
    Only works on files with extensions `.c`, `.h` or `.c.h`.
- `ren_idfs.sh` Bulk rename identifiers in files by replacing a string in old identifiers with a new string.
    Only works on files with extensions `.c`, `.h` or `.c.h`.
- `rm_trailing_ws.sh` Remove trailing whitespace from all `.c`, `.h` or `.c.h` files.
- `run_clangd.sh` Runs `clangd --check` on all `.c`, `.h` or `.c.h` files.
    This produces a rather large output, so it is recommended to redirect the output to a file.

## Expression AST
The functions `ast_Expression_Literal()`, `ast_Expression_Identifier()` and `ast_Expression_CommaSepList()` produce an `ast_Expression_t` with `op` set to `TOKOP_NOP`.

However `ast_Expression()` extracts out the data from the returned `ast_Expression_t` and stores it inside the internal union `ast_ExpressionUnion_t`.

Therefore, There's absolutely no way you'll ever find the `TOKOP_NOP` in any `ast_Expression_t` in the finally generated AST.

## Contributing Guidelines
To contribute to Shsc, please follow these guidelines:
1. Fork the repository and create a new branch for your contribution.
2. Make your changes or additions while adhering to the coding conventions and guidelines mentioned above.
3. Write clear and concise commit messages (alternatively, email the repo owner explaining your changes and include the commit link from the GitHub site in that email).
4. Submit a pull request, documenting the changes made and providing any necessary context.

We appreciate your contributions and look forward to working with you to improve Shsc!

If you have any questions or need assistance, feel free to reach out to the project maintainers.
