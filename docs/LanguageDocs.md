**Last updated on Oct 19, 2023**

The following is a documentation of the syntax and behaviour of the language.

Some of this is yet to be implemented.

# Language Docs

This language is inspired by C, Python and Javascript.
However, it introduces its own unique features and has a limited set of datatypes.

Shsc is a dynamically and weakly typed language with coercion rules that make sense (unlike JS).

## Index
- [File structure](#file-structure)
- [Code organization](#code-organization)
    - [Indentation](#indentation)
    - [Module declaration](#module-declaration)
    - [Default main module](#default-main-module)
    - [Module access](#module-access)
    - [Procedure declaration](#procedure-declaration)
    - [Entry point](#entry-point)
    - [Naming collision](#naming-collision)
    - [End of file](#end-of-file)
- [Valid identifiers](#valid-identifiers)
    - [The dollar sign](#the-dollar-sign)
- [Statements](#statements)
    - [Variable declaration](#variable-declaration)
    - [Variable shadowing](#variable-shadowing)
    - [Constants](#constants)
    - [Semicolons](#semicolons)
        - [Example](#example)
- [If statements](#if-statements)
    - [Example 1](#example-1)
    - [Example 2](#example-2)
- [While loops](#while-loops)
    - [Example](#example-1)
- [For loops](#for-loops)
    - [Default increment](#default-increment)
    - [Specified increment](#specified-increment)
    - [Iterable](#iterable)
- [Block statement](#block-statement)
- [Functions](#functions)
    - [Example](#example-2)
    - [Function arguments](#function-arguments)
    - [Arguments to `main:main`](#arguments-to-mainmain)
- [Expressions](#expressions)
    - [Ternary expression](#ternary-expression)
    - [Assignments](#assignments)
        - [Example](#example-3)
- [Data and literals](#data-and-literals)
    - [Coercion Rules](#coercion-rules)
    - [Special types](#special-types)
    - [Hidden types](#hidden-types)
    - [Special global variables](#special-global-variables)
    - [Global variables for types](#global-variables-for-types)
    - [Memory management](#memory-management)
    - [Memory allocation](#memory-allocation)
        - [Example](#example-4)
    - [Memory ownership](#memory-ownership)
        - [Accumulator](#accumulator)
    - [Format strings](#format-strings)
    - [Lists](#lists)
        - [Example](#example-5)
    - [Maps](#maps)
        - [Example](#example-6)
- [Built-in functions](#built-in-functions)
    - [Global](#global)
    - [Module `dbg`](#module-dbg)
    - [Module `io`](#module-io)
    - [Module `it`](#module-it)

## File structure
The interpreter accepts file paths as command-line arguments for the files you want to run.
It parses each file and constructs a data structure that maps module names to a list of defined procedures.

## Code organization
Since this language doesn't recognize files, module declarations are used to organize code.
If multiple files have the same module declaration, all the procedures from those files will be stored under the same module name.

### Indentation
The parser ignores indentation and whitespaces completely.

Only newlines are significant for statement termination.

### Module declaration
Each file must start with the following syntax, indicating the module to which the subsequent procedures belong:
```
module module_name
```
Note that there should be no other tokens before the module declaration, not even newlines.

Also, after the module declaration, the same file can't have another module declaration.

Procedure definitions can be placed only after the module declaration.

### Default main module
If the very first line starts with a procedure declaration (without a module name provided), the runtime assumes the module to be `main` by default.

For example:
```
proc procname start
    # Procedure code
end
```
is equivalent to:
```
module main
proc procname start
    # Procedure code
end
```

### Module access
Modules don't need to be explicitly imported; they're only declared in **line 1** of the file.

To access a procedure from a different module, use the following syntax:
```
modulename:procname
```
Replace `modulename` with the appropriate module name and `procname` with the name of the procedure you want to access.

### Procedure declaration
Procedures can only appear after the module declaration.

The basic syntax for declaring a procedure is as follows:
```
proc procname start
    # Procedure code
end
```
The procedure name (`procname`) should be a valid identifier.

### Entry point
Program execution starts at `main:main`, i.e., the main procedure of the main module.

### Naming collision
If there is a naming collision between procedures in the same module, the runtime will raise an error and stop execution.

### End of file
Ensure that each file ends with a newline character, or a syntax error will be thrown.

## Valid identifiers
- Should start with either a letter or an underscore.
- Can have alphanumeric characters and underscores.
- Note that `$` is not a valid identifier character.

### The dollar sign
The dollar sign is used to access arguments to a procedure. In compiler terms `$` acts as a special operator.
For details, see [Function arguments](#function-arguments).

## Statements
All statements end with a newline.
A statement can be a variable declaration or an expression.

A statement can have only one variable declaration.

Any variable declared must be given some value.

A good choice is to assign them to `null`.

### Variable declaration
You'd use the `var` keyword to create a new variable in current scope.
```
proc test start
    var x = 5
end
```

### Variable shadowing
If you use `var` again, the original variable will be destroyed and replaced by the new one.

**WARNING:** Experimental feature; may not be released during the beta (if the project ever leaves alpha).
```
proc test start
    var x = 5
    io:print(x, lf)
    var x = 11
    io:print(x, lf)
end
```
**Output:**
```
5
11
```

### Constants
You'd use the `const` keyword to create a constant in current scope.
```
proc test start
    const x = 5
end
```
A constant cannot be shadowed.

### Semicolons
Newlines or semicolons can be used to terminate a statement.

If semicolon is used, one can write multiple statements in a single line.

There's no up or downside in using either.
If used at the end of a statement, the parser makes no distinction b/w newlines or semicolons.

Even a combination of the two can be used wherever one desires.

#### Example
```
x = 5; y = 7
io:print(x, y, lf)
```

## If statements
### Example 1:
```
if condition then
    # code
end
```

### Example 2:
```
if condition then
    # code
else if condition then
    # code
else
    # code
end
```
You can also use `elif` instead of `else if`.

## While loops
### Example
```
while condition do
    # code
end
```

## For Loops
There are 3 kinds of `for` loops.

### Default increment
Increment (or decrement) by 1 depending on the start and end values.
```
var start = 10
for i from start to 0 do
    # this will automatically do decrement by 1
end
```

### Specified increment
Increment (or decrement) by the value specified.
```
var end = 10
for i from 0 to end by 2 do
    # this will do an increment by 2
end
```

Note that the following will cause an error.
```
var end = 10
for i from 0 to end by -2 do
    # this will do a decrement by 2
    # this is a potential infinite loop
end
```

### Iterable
This syntax works for maps, lists, and strings.
```
var list = [ "this", 1, 5, "a", 1, 'i', 's', "t" ]
for i, e in list do
    # `e` is a copy of the item at index `i`
end
```

For maps, use
```
for k, v in my_map do
    # `v` is a copy of the value for key `k`
end
```

For a shorter syntax, you may use the following
```
for v in my_iterable do
    # `v` is a copy of the value
    # the syntax works for maps, lists, and strings
end
```

## Block statement
Creates an unnamed scope.
It's pretty much useless.

## Functions
The following is an example of a factorial program that shows how to use functions.

### Example
```
module main

# factorial(num)
proc factorial start
    var num = $0
    if num <= 1 then
        return 1
    else
        return num * factorial(num - 1)
    end
end

proc main start
    var inp = io:input("Enter a number: ", i64)
    var res = factorial(inp)
    io:print(f"result = {res}\n")
end
```

### Function arguments

#### Example
Four ways to access the first (0th) argument to a function.
```
var x = $0
var y = $[0]
var z = $(0)
var w = args[0]
```

Arguments to a function is defined by the actual parameters (i.e. at the caller side).

Functions have no prototypes or formal parameters.

Arguments are stored in the `args` built-in `lst` type variable.

However, you may access arguments using the syntax `$i` where `i` is and identifier or literal that evaluates to a valid `i64` index.

You may also use `$(expr)` or `$[expr]` where `expr` is an expression that evaluates to a valid `i64` index.

Of course, you may also use the `args` list to access the arguments, as in `args[expr]`.

### Arguments to `main:main`
The arguments to `main:main` are the command-line arguments passed to the interpreter.

## Expressions
Expressions are basically C expressions with some additional operators.

Some additions include exponentiation operator (`**`) and floor division (`//`).

### Ternary expression
Follows Python syntax.

```
expression if condition else expression
```

### Assignments
An assignment is possible only to an already existing variable.

The language supports `=` and all the shortcut assignments.

An assignment is a part of an expression, which means you can do the same operations as in C.

#### Example
```
x = y = x = 5
var u = (x = 4) if true else "hi"
```

## Data and literals
The language supports the following `built-in` literals.
- `bul` Boolean
- `chr` String character
- `i64` 64-bit integer
- `f64` 64-bit float
- `str` ASCII string
- `lst` Dynamic valued list
- `map` String to any hash map
- `null` Null data

### Coercion Rules
- Any built-in can be coerced to a string.
- For lists and maps, coercion to string is JSON-like stringification.
- Certain string to primitive coercions may fail and raise an error.
- Any primitive type (except float) can be coerced to a bool.
- Float, int, and char can be coerced among themselves.
- Bool can be coerced to any type.

### Special types
- `null` Null data
- Interpolable string aka format strings

### Hidden types
- `interp_str` Is hardly ever used in the runtime. It may serve as a temporary type for format strings.
- `any` Is hardly used in the runtime, although `null` is a special kind of `any` object that points to `(void*) 0`.

### Special global variables
These variables must not be assigned to or else the user may face issues.
- `lf` chr value equal to `'\n'`
- `null` null data

### Global variables for types
These variables must not be assigned to or else the user may face issues.
- `bul` i64 value indicating the bul type
- `chr` i64 value indicating the chr type
- `i64` i64 value indicating the i64 type
- `f64` i64 value indicating the f64 type
- `str` i64 value indicating the str type
- `lst` i64 value indicating the lst type
- `map` i64 value indicating the map type

The term `built-in` is more accurate for these and we will not call these *primitive*s.
The language has built-in support for complex composite data structures which can be used using the literals syntax.

### Memory management
Memory is managed by allocating data in the heap, and maintaining a reference count.

The reference count is updated when data is assigned among the variables and also the accumulator.

In case the reference count becomes `0`, the data is freed immediately.

### Memory allocation
New memory is allocated for every new literal, even if two literals are identical by value.

#### Example
```
var x = "hello world"
var y = "hello world"
```

Results in two seperate copies of the string `"hello world"` being created for the seperate variables.

The same idea is followed for all other literals, including lists and maps.

### Memory ownership
Ownership in our case is being able to destroy the data (free memory).

The following takes memory ownership
- Any variable to whom data is assigned (until reassigned)
- Accumulator; or else function returns won't work (temporarily)

#### Accumulator
The language uses a temporary location called the `accumulator` to store the result of operations and return values.

### Format strings
```
var x = "some data"
var y = 56
var z = f"The value of {x} is {y}"
```

Note that the syntax for format strings is `f"....{<identifier>}..."`.
The `{}` only accept variables and not expressions.

### Lists
The language supports lists in the same syntax as that of Python.
A single list can have multiple datatypes together.

Although named list, these literals are stored as an **array** of union of multiple types.
The type is dynamically inferred when an element is accessed.

#### Example
```
proc test start
    var list = ["xyz", 'a', "\n", "001", 'A', "\x41\x41"]
    var list = [
        [ 1, 2, 4, 5 ],
        [ 1, 2, 4, 5 ],
        [ 1, 2, 4, 5 ],
        [ 1, 2, 4, 5 ],
    ]
end
```
**Output:**
```
["xyz", 'a', "\n", "001", 'A', "AA"]
[[1, 2, 4, 5], [1, 2, 4, 5], [1, 2, 4, 5], [1, 2, 4, 5]]
```

Note how data is stringified during conversion to string (printing).

### Maps
Maps have syntax similar to Python and are implemented as hash maps of string to any data type.
Maps are built on the `khash` library.

If a non-string value is used as a key, the runtime will attempt to convert it to a string.
If that fails an error will occur, otherwise the data will be stored.

When accessing data, key is again converted into string.

#### Example
```
proc test start
    var my_map = {
        "key1": true,
        "key2": 78,
        "key3": 1222,
        "key4": {
            "alpha": "hi",
            "beta": 67,
            "gamma": "\x05\x0a"
        }
    }
    io:print(my_map, lf)
end
```
**Output:**
```
{"key1": true, "key2": 78, "key3": 1222, "key4": {"beta": 67, "alpha": "hi", "gamma": "\x05\n"}}
```

Note how order of keys is not maintained.

Also note how data is stringified during conversion to string (printing).

## Built-in functions
The language supports the following built-in functions (within built-in modules)
#### Global
- `isnull` returns true if data is `null`, else false
- `tostr` stringifies a built-in
- `type` returns one of the [global variables for types](#global-variables-for-types)

#### Module `dbg`
- `dbg:typename` returns identifier name of one of the [global variables for types](#global-variables-for-types)
- `dbg:refcnt` returns total number of references to an object

#### Module `io`
- `io:print` prints string form of data (calls `tostr`)
- `io:input` takes input from stdin

#### Module `it`
- `it:len` returns length of list, string or map, else returns `1`
