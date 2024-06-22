**Last updated on June 22nd, 2024**

The following is a documentation of the syntax and behaviour of the language.

Arithmetic right shift and shift operations on `f64` LHS operand are buggy.

# Language Docs

This language is inspired by C, Python and Javascript.
However, it introduces its own unique features and has a limited set of datatypes.

Shsc is a dynamically and weakly typed language with coercion rules that make sense (unlike JS).

## Index
- [File Structure](#file-structure)
- [Code Organization](#code-organization)
    - [Indentation](#indentation)
    - [Module Declaration](#module-declaration)
    - [Pseudo Sub Modules](#pseudo-sub-modules)
    - [Default `main` Module](#default-main-module)
    - [Module Access](#module-access)
    - [Procedure Declaration](#procedure-declaration)
    - [Entry Point](#entry-point)
    - [Naming Collision](#naming-collision)
    - [End of File](#end-of-file)
- [Valid Identifiers](#valid-identifiers)
    - [The Dollar Operator](#the-dollar-operator)
- [Statements](#statements)
    - [Variable Declaration](#variable-declaration)
    - [Variable Re-declaration](#variable-re-declaration)
    - [Constants](#constants)
        - [Lazy Const](#lazy-const)
    - [Weak References](#weak-references)
        - [Weak ref Behaviour](#weak-ref-behaviour)
    - [Semicolons](#semicolons)
- [If Statements](#if-statements)
- [While Loops](#while-loops)
- [For Loops](#for-loops)
    - [Default Increment](#default-increment)
    - [Specified Increment](#specified-increment)
    - [Iterable](#iterable)
- [Block Statement](#block-statement)
- [Procedures](#procedures)
    - [Procedure Arguments](#procedure-arguments)
    - [Named Arguments](#named-arguments)
    - [Arguments to `main:main`](#arguments-to-mainmain)
    - [Procedure Context](#procedure-context)
    - [Rudimentary OOP](#rudimentary-oop)
- [Lambdas](#lambdas)
- [Interop with C](#interop-with-c)
- [Expressions](#expressions)
    - [Ternary Expression](#ternary-expression)
    - [Assignments](#assignments)
- [Data and Literals](#data-and-literals)
    - [Coercion Rules](#coercion-rules)
    - [Special Types](#special-types)
    - [Hidden Types](#hidden-types)
    - [Reserved Global Variables](#reserved-global-variables)
    - [The Global Types Map](#the-global-types-map)
    - [Memory Management](#memory-management)
    - [Memory Allocation](#memory-allocation)
    - [Memory Ownership](#memory-ownership)
        - [The Accumulator](#the-accumulator)
        - [Circular References](#circular-references)
    - [Format Strings](#format-strings)
    - [Lists](#lists)
    - [Maps](#maps)
        - [Map with `const` Keys](#map-with-const-keys)
        - [One-time Map Lock](#one-time-map-lock)
- [Built-in Procedures](#built-in-procedures)
    - [Globally available](#globally-available)
    - [Module `assert`](#module-assert)
    - [Module `dbg`](#module-dbg)
    - [Module `io`](#module-io)
    - [Module `it`](#module-it)
    - [Module `chr`](#module-chr)
    - [Module `i64`](#module-i64)
    - [Module `f64`](#module-f64)
    - [Module `str`](#module-str)
    - [Module `lst`](#module-lst)
    - [Module `map`](#module-map)

## File Structure
The interpreter accepts file paths as command-line arguments for the files you want to run.
It parses each file and constructs a data structure that maps module names to a list of defined procedures.

## Code Organization
Since this language doesn't recognize files, module declarations are used to organize code.
If multiple files have the same module declaration, all the procedures from those files will be stored under the same module name.

### Indentation
The parser ignores indentation and whitespaces completely.

Only newlines are significant for statement termination.

### Module Declaration
Each file must start with the following syntax, indicating the module to which the subsequent procedures belong:
```lua
module module_name
```
Note that there should be no other tokens before the module declaration, not even newlines.

Also, after the module declaration, the same file can't have another module declaration.

Procedure definitions can be placed only after the module declaration.

### Pseudo Sub Modules
Sub-module can be defined as follows
```lua
module Module:Submodule1:Submodule2
```

Procedures defined under sub-modules can be used as follows
```lua
Module:Submodule1:Submodule2:procedure()
```

**NOTE**: In case of sub-modules, `:` is used as a part of the module identifier rather than as an operator.
Therefore, in the above example the full module identifier is `Module:Submodule1:Submodule2`.

Previously this would be achieved using `Module_Submodule1_Submodule2` but that looks strange.

See [examples/oop](../examples/oop/)

### Default `main` Module
If the very first line starts with a procedure declaration (without a module name provided), the runtime assumes the module to be `main` by default.

For example:
```lua
proc procname start
    # Procedure code
end
```
is equivalent to:
```lua
module main
proc procname start
    # Procedure code
end
```

### Module Access
Modules don't need to be explicitly imported; they're only declared in **line 1** of the file.

To access a procedure from a different module, use the following syntax:
```lua
modulename:procname
```
Replace `modulename` with the appropriate module name and `procname` with the name of the procedure you want to access.

### Procedure Declaration
Procedures can only appear after the module declaration.

The basic syntax for declaring a procedure is as follows:
```lua
proc procname start
    # Procedure code
end
```
The procedure name (`procname`) should be a valid identifier.

### Entry Point
Program execution starts at `main:main`, i.e., the main procedure of the main module.

### Naming Collision
If there is a naming collision between procedures in the same module, the runtime will raise an error and stop execution.

### End of File
Ensure that each file ends with a newline character, or a syntax error will be thrown.

## Valid Identifiers
- Should start with either a letter or an underscore.
- Can have alphanumeric characters and underscores.
- Note that `$` is not a valid identifier character.

### The Dollar Operator
The dollar sign is used to access arguments to a procedure. In compiler terms `$` acts as a special operator.
For details, see [Procedure arguments](#procedure-arguments).

## Statements
All statements end with a newline.
A statement can be a variable declaration or an expression.

A statement can have only one variable declaration.

Any variable declared must be given some value.

A good choice is to assign them to `null`.

### Variable Declaration
You'd use the `var` keyword to create a new variable in current scope.
```lua
proc test start
    var x = 5
end
```

### Variable Re-declaration
If you use `var` again, the original variable will be destroyed and replaced by the new one.

```lua
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
```lua
proc test start
    var x = const 5
end
```
A constant cannot be shadowed.

#### Lazy Const
Lazy `const` allows you to create a variable and later on make it constant.
```lua
proc test start
    var x = "default value"
    x = const mod:get_some_value()
end
```

### Weak References
You'd use the `weak` keyword to create a weak reference in current scope.
```lua
proc test start
    var x = { a: "some data", b: {} }
    x.b.circular = weak x
end
```

Weak references are useful for creating circular references.

Note that not using `weak` in a circular reference will cause a memory leak because the language uses reference counting GC. See [Circular references](#circular-references) for more details.

#### Weak ref Behaviour
- Not using `weak` keyword automatically creates a strong reference.
- Thus, strong references can be made to objects via a weak reference. For example:
    ```lua
    var x = { a: "some data", b: {} }
    var y = weak x
    var z = y
    # x and z are strong references but y is weak
    ```
- The `weak` keyword can be used only after the `=` operator.
- It can be used in variable declaration as well as assignment.
- It can be used in conjunction with `const` keyword.

### Semicolons
Newlines or semicolons can be used to terminate a statement.

If semicolon is used, one can write multiple statements in a single line.

There's no up or downside in using either.
If used at the end of a statement, the parser makes no distinction b/w newlines or semicolons.

Even a combination of the two can be used wherever one desires.

**Example:**
```lua
x = 5; y = 7
io:print(x, y, lf)
```

## If Statements
**Example 1:**
```lua
if condition then
    # code
end
```

**Example 2:**
```lua
if condition then
    # code
else if condition then
    # code
else
    # code
end
```
You can also use `elif` instead of `else if`.

## While Loops
**Example:**
```lua
while condition do
    # code
end
```

## For Loops
There are 3 kinds of `for` loops.

### Default Increment
Increment (or decrement) by 1 depending on the start and end values.
```lua
var start = 10
for i from start to 0 do
    # this will automatically do decrement by 1
end
```

### Specified Increment
Increment (or decrement) by the value specified.
```lua
var end = 10
for i from 0 to end by 2 do
    # this will do an increment by 2
end
```

Note that the following will cause an error.
```lua
var end = 10
for i from 0 to end by -2 do
    # this will do a decrement by 2
    # this is a potential infinite loop
end
```

### Iterable
This syntax works for maps, lists, and strings.
```lua
var list = [ "this", 1, 5, "a", 1, 'i', 's', "t" ]
for i, e in list do
    # `e` is a copy of the item at index `i`
end
```

For maps, use
```lua
for k, v in my_map do
    # `v` is a copy of the value for key `k`
end
```

For a shorter syntax, you may use the following
```lua
for v in my_iterable do
    # `v` is a copy of the value
    # the syntax works for maps, lists, and strings
end
```

## Block Statement
Creates an unnamed scope.
It's pretty much useless.

## Procedures
The following is an example of a factorial program that shows how to use procedures.

**Example:**
```lua
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
    var inp = io:input("Enter a number: ", Types.I64)
    var res = factorial(inp)
    io:print(f"result = {res}\n")
end
```

### Procedure Arguments

**Example:**
Four ways to access the first (0th) argument to a procedure.
```lua
var x = $0
var y = $[0]
var z = $(0)
var w = args[0]
```

Arguments to a procedure is defined by the actual parameters (i.e. at the caller side).

Procedures have no prototypes or formal parameters.

Arguments are stored in the `args` built-in `lst` type variable.

However, you may access arguments using the syntax `$i` where `i` is and identifier or literal that evaluates to a valid `i64` index.

You may also use `$(expr)` or `$[expr]` where `expr` is an expression that evaluates to a valid `i64` index.

Of course, you may also use the `args` list to access the arguments, as in `args[expr]`.

### Named Arguments

**Example:**
```lua
proc foo(a, b, c)
    io:print(a, b, c, lf)
end

proc main()
    foo(1, 2, 3)
end
```

**Output:**
```
1 2 3
```

Named arguments are set to `null` if no argument is passed by the caller.
**Example:**
```lua
proc foo(a, b, c)
    io:print(a, b, c, lf)
end

proc main()
    foo(1, 2)
end
```

**Output:**
```
1 2 null
```

### Arguments to `main:main`
The arguments to `main:main` are the command-line arguments passed to the interpreter.

### Procedure Context
If the `.` or map membership operator is used to access a reference to a procedure, the procedure context object is set to the parent map.

Note that this works only if a procedure is accessed from a map using the `.` operator.

The context object can be accessed using the `this` keyword inside a procedure. This is useful for a limited form of object-oriented programming.

In case there is no context object, `this` will be `null`.

### Rudimentary OOP
```lua
module ComplexNo

proc init start
    # if no arguments are passed, default to 0
    if !it:len(args) then
        $0 = 0
        $1 = 0
    end
    # create new object from the arguments
    var z = {
        x: $0,
        y: $1
    }
    # bind proccedures to the object as methods
    z.show = show
    z.add = add
    return z
end

proc show start
    var x = this.x
    var y = this.y
    io:print(f"{x}+i{y}", lf)
end

proc add start
    var z = $0
    var x = this.x + z.x
    var y = this.y + z.y
    return init(x, y)
end
```

The following should be in a seperate file to respect the module declaration syntax.

```lua
module main

proc main start
    var x = ComplexNo:init(1, 2)
    var y = ComplexNo:init(4, 8)
    # x set as context object of the ComplexNo:add procedure
    var c = x.add(y)
    # similarly, c set as context object of the ComplexNo:show procedure
    c.show()
end
```

## Lambdas
Lambdas are anonymous procedures that can be assigned to variables.

Shsc lambdas do not support capturing variables from the outer scope.
All variables must be passed as arguments.

Lambdas also support context objects.

**Example:**
```lua
var add = (a, b) -> a + b
var long_proc = (a, b) -> {
    var x = a + b
    return x
}
io:print(add(5, 6), lf)
io:print(long_proc(5, 6), lf)
```

## Interop with C
Interoperability with C code via dynamic libraries is possible. For a better understanding see the repo [shsc-c-interop](https://github.com/AvirukBasak/shsc-c-interop).

## Expressions
Expressions are basically C expressions with some additional operators.

Some additions include exponentiation operator (`**`) and floor division (`//`).

### Ternary Expression
Follows Python syntax.

```lua
expression if condition else expression
```

### Assignments
An assignment is possible only to an already existing variable.

The language supports `=` and all the shortcut assignments.

An assignment is a part of an expression, which means you can do the same operations as in C.

**Example:**
```lua
x = y = x = 5
var u = (x = 4) if true else "hi"
```

## Data and literals
The language supports the following `built-in` literals.
- `bul` Boolean
- `chr` String character
- `i64` 64-bit signed integer
- `f64` 64-bit float
- `str` ASCII string
- `lst` Dynamic valued list
- `map` String to any hash map
- `null` Null data
- `proc` Pointer to existing procedure
- `lambda` Lambda (anonymous) function
- `libhandle` Shared library handle data

### Coercion Rules
- Any built-in can be coerced to a string.
- For lists and maps, coercion to string is JSON-like stringification.
- Certain string to primitive coercions may fail and raise an error.
- Any primitive type (except float) can be coerced to a bool.
- Float, int, and char can be coerced among themselves.
- Bool can be coerced to any type.

### Special Types
- `null` Null data
- Interpolable string aka format strings

### Hidden Types
- `interp_str` Is hardly ever used in the runtime. It may serve as a temporary type for format strings.
- `any` Is hardly used in the runtime, although `null` is a special kind of `any` object that points to `(void*) 0`.

### Reserved Global Variables
These variables must not be assigned to or else the user may face issues.
- `lf` chr value equal to `'\n'`
- `null` null data
- `globals` map of global variables
- `Types` map of type names to type values

### The Global Types Map
These variables must not be assigned to or else the user may face issues.
- `Types.BUL` i64 value indicating the bul type
- `Types.CHR` i64 value indicating the chr type
- `Types.I64` i64 value indicating the i64 type
- `Types.F64` i64 value indicating the f64 type
- `Types.STR` i64 value indicating the str type
- `Types.LST` i64 value indicating the lst type
- `Types.MAP` i64 value indicating the map type
- `Types.NULL` i64 value indicating the null type
- `Types.PROC` i64 value indicating the proc type
- `Types.LAMBDA` i64 value indicating the lambda type
- `Types.LIBHANDLE` i64 value indicating the libhandle type

The term `built-in` is more accurate for these and we will not call these *primitive*s.
The language has built-in support for complex composite data structures which can be used using the literals syntax.

### Memory Management
Memory is managed by allocating data in the heap, and maintaining a reference count.

The reference count is updated when data is assigned among the variables and also the accumulator.

In case the reference count becomes `0`, the data is freed immediately.

### Memory Allocation
New memory is allocated for every new literal, even if two literals are identical by value.

**Example:**
```lua
var x = "hello world"
var y = "hello world"
```

Results in two seperate copies of the string `"hello world"` being created for the seperate variables.

The same idea is followed for all other literals, including lists and maps.

### Memory Ownership
Ownership in our case is being able to destroy the data (free memory).

The following takes memory ownership
- Any variable to whom data is assigned (until reassigned)
- Accumulator; or else procedure returns won't work (temporarily)
- Intermediate results are owned by 2 internal temporary variables
- Global variables owned by the runtime

#### The Accumulator
The language uses a temporary location called the `accumulator` to store the result of operations and return values.

#### Circular References
This language is unable to detect and manage circular references.
If a circular reference must be created, it must be a weak reference. See [Weak refs](#weak-refs) for more details.

Running `tostr` or `io:print` on an object having a circular reference will most likely result in stack overflow or Segmentation fault.

Avoid using same variables for weak and strong references.

Additionally, using non-weak circular references **WILL** cause memory leak.

### Format Strings
```lua
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

**Example:**
```lua
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
```lua
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

**Example:**
```lua
proc test start
    var key5 = "key5"
    var my_map = {
        key1: true,
        key2: 78,
        "key3": 1222,
        "key4": {
            alpha: "hi",
            "beta": 67,
            "gamma": "\x05\x0a"
        },
        [key5]: "value5"
    }
    io:print(my_map, lf)
end
```
**Output:**
```
{"key1": true, "key2": 78, "key3": 1222, "key4": {"beta": 67, "alpha": "hi", "gamma": "\x05\n"}, "key5": "value5"}
```

Note how order of keys is not maintained.

Also note how data is stringified during conversion to string (printing).

#### Map with `const` Keys
A map can have `const` keys which prevent modification of the key.

**Example:**
```lua
proc main()
    var p = {}
    p.x = const 5
    p.x = 11
end
```

Note that keys can't be const marked using the map literal syntax. Instead it uses the [`lazy const`](#lazy-const) syntax.

**Output:**
```
shsc: test.shsc:4: cannot modify const variable
    at main:main (test.shsc:4)
```

#### One-time Map Lock
The function `map:lockonce(map, i64)` is used to lock a map. It takes a map and a locking ID as arguments.

Once locked, the map can't be unlocked.
Keys can't be added or removed from a locked map.
They can however be modified.

Difference between `map:lockonce` and using `const` is that the former allows modification of the map but disallows addition or removal of keys.
The latter diasllows modification of existing keys but allows addition or removal of keys.

A combination of both can be used to create a read-only map. An example of such a map is the [`Types`](#properties-of-types-map) map provided by the runtime.

**Example:**
```lua
proc main()
    var mp = {
        key1: true,
        key2: 78,
        "key3": 1222,
        "key4": {
            alpha: "hi",
            "beta": 67,
            "gamma": "\x05\x0a"
        }
    }

    map:lockonce(mp, 0xDEAD)
    mp.key1 = 112
    mp.key5 = "value5"
end

```

**Output:**
```
shsc: examples/lockonce.shsc:15: map is locked from modification with lock id 0xDEAD
    at main:main (examples/lockonce.shsc:15)
```

Note that a lock ID of `0xDEAF` indicates that the map is locked and reserved. It must not be used by the user.

## Built-in Procedures
The language supports the following built-in procedures (within built-in modules)

| -      | assert  | dbg      | io      | it    | chr     | i64 | f64 | str     | lst     | map      |
|--------|---------|----------|---------|-------|---------|-----|-----|---------|---------|----------|
| isnull | type    | typename | print   | len   | max     | max | max | equals  | equals  | -        |
| tostr  | equals  | refcnt   | input   | clone | min     | min | min | compare | compare | -        |
| type   | notnull | id       | fexists | -     | isdigit | -   | -   | tolower | -       | -        |
| cast   | -       | callproc | fread   | -     | isalpha | -   | -   | toupper | -       | -        |
| -      | -       | filename | fwrite  | -     | isalnum | -   | -   | append  | append  | set      |
| -      | -       | lineno   | fappend | -     | islower | -   | -   | insert  | insert  | get      |
| -      | -       | -        | libopen | -     | isupper | -   | -   | erase   | erase   | erase    |
| -      | -       | -        | libsym  | -     | isspace | -   | -   | concat  | concat  | concat   |
| -      | -       | -        | -       | -     | -       | -   | -   | reverse | reverse | -        |
| -      | -       | -        | -       | -     | -       | -   | -   | substr  | sublist | keys     |
| -      | -       | -        | -       | -     | -       | -   | -   | find    | find    | find     |
| -      | -       | -        | -       | -     | -       | -   | -   | split   | join    | lockonce |
| -      | -       | -        | -       | -     | -       | -   | -   | toi64   | -       | -        |
| -      | -       | -        | -       | -     | -       | -   | -   | tof64   | -       | -        |
| -      | -       | -        | -       | -     | -       | -   | -   | sort    | sort    | -        |

#### Globally Gvailable
- `isnull(any)` returns true if data is `null`, else false
- `tostr(any)` stringifies a built-in; for lists and maps, it's JSON-like stringification; for circular references, it'll most likely result in stack overflow or segmentation fault
- `type(any)` returns one of the [global variables for types](#global-variables-for-types)
- `cast(any, i64)` casts data to a type; the second argument is one of the [global variables for types](#global-variables-for-types)
- `max(any, ...)` returns the greatest of the arguments; returns `null` if no arguments are passed
- `max(lst)` returns the greatest of the items in the list; returns `null` if list is empty
- `min(any, ...)` returns the smallest of the arguments; returns `null` if no arguments are passed
- `min(lst)` returns the smallest of the items in the list; returns `null` if list is empty

#### Module `assert`
- `assert:type(any, i64)` returns true if data is of the specified type, else throws an error
- `assert:equals(any, any)` returns true if data is equal, else throws an error
- `assert:notnull(any)` returns true if data is not `null`, else throws an error

#### Module `dbg`
- `dbg:typename(any)` returns type name of data as string
- `dbg:rtsize(any)` returns size of data in bytes; may be never implemented considering the computation will require recursive dfs traversal of composite data structures
- `dbg:refcnt(any)` returns total number of references to an object
- `dbg:id(any)` returns hex string of the memory address of an object
- `dbg:callproc(any, str, str, lst)` calls a procedure from a module; the first argument is the context object, the second argument is the module name, the third argument is the procedure name, and the fourth argument is the list of arguments to the procedure
- `dbg:filename()` returns filename of the source file where called
- `dbg:lineno()` returns line number of the source file where called

#### Module `io`
File I/O functions will not create a file if it doesn't exist.

- `io:print(any, ...)` prints string form of data (calls `tostr`)
- `io:input(str, i64)` where the first argument is the prompt and the second argument is the type of input, see [global variables for types](#global-variables-for-types)
- `io:fexists(str)` returns true if file exists, else false
- `io:fread(str)` reads a file and returns a string; the first argument is the file path
- `io:fwrite(str, str)` writes a string to a file; the first argument is the file path
- `io:fappend(str, str)` appends a string to a file; the first argument is the file path
- `io:libopen(str)` opens a shared library and returns a handle object
- `io:libsym(libhandle, str)` returns a native lambda given handle and the name of the function

#### Module `it`
- `it:len(any)` returns length of list, string or map, else returns `1`
- `it:clone(any)` returns a shallow copy of the data

#### Module `chr`
- `chr:isdigit(chr)` returns true if character is a digit, else false
- `chr:isalpha(chr)` returns true if character is a letter, else false
- `chr:isalnum(chr)` returns true if character is a letter or digit, else false
- `chr:islower(chr)` returns true if character is a lowercase letter, else false
- `chr:isupper(chr)` returns true if character is an uppercase letter, else false
- `chr:isspace(chr)` returns true if character is a whitespace, else false
- `chr:max()` returns the greatest possible character
- `chr:max(chr, i64, f64, ...)` returns the greater of the numbers, calls `max` internally
- `chr:min()` returns the smallest possible character
- `chr:min(chr, i64, f64, ...)` returns the smaller of the numbers, calls `min` internally

#### Module `i64`
- `i64:max()` returns the greatest possible i64
- `i64:max(chr, i64, f64, ...)` returns the greater of the numbers, calls `max` internally
- `i64:min()` returns the smallest possible i64
- `i64:min(chr, i64, f64, ...)` returns the smaller of the numbers, calls `min` internally

#### Module `f64`
- `f64:max()` returns the greatest possible f64
- `f64:max(chr, i64, f64, ...)` returns the greater of the numbers, calls `max` internally
- `f64:min()` returns the smallest possible f64
- `f64:min(chr, i64, f64, ...)` returns the smaller of the numbers, calls `min` internally

#### Module `str`
`str:concat` is the only manupulative procedure that doesn't work in-place.
This means that it returns a new string instead of modifying the original string.

- `str:equals(str, str)` returns true if strings are equal, else false
- `str:compare(str, str)` returns positive if first string is greater, negative if first string is smaller, else 0
- `str:tolower(str)` converts a string to lowercase
- `str:toupper(str)` converts a string to uppercase
- `str:append(str, str)` appends second string to first string
- `str:append(str, chr)` appends a single character to first string
- `str:insert(str, i64, str)` inserts a string at index in first string
- `str:insert(str, i64, chr)` inserts a single character at index in first string
- `str:erase(str, i64, i64)` erases a substring; the second argument is the start index and the third argument is length of substring; if third argument exceeds length of string, it'll erase till end of string
- `str:concat(str, str)` concatenates two strings and returns a new string
- `str:reverse(str)` reverses a string
- `str:substr(str, i64, i64)` returns a substring; the second argument is the start index and the third argument is the length of substring; if third argument exceeds length of string, it'll return till end of string
- `str:find(str, str)` returns first index of substring, else -1
- `str:find(str, chr)` returns first index of character, else -1
- `str:split(str, str)` the second argument is the delimiter
- `str:split(str, chr)` the second argument is the delimiter
- `str:toi64(str)` converts a string to an i64
- `str:tof64(str)` converts a string to an f64
- `str:sort(str)` sorts a string in ascending order

#### Module `lst`
`lst:concat` is the only manupulative procedure that doesn't work in-place.
This means that it returns a new list instead of modifying the original list.

All list related procedures work using shallow copies, and no procedure is provided to create deep copies.

- `lst:equals(lst, lst)` returns true if lists are equal, else false
- `lst:compare(lst, lst)` returns positive if first list is greater, negative if first list is smaller, else 0
- `lst:append(lst, any)` appends an item to a list
- `lst:insert(lst, i64, any)` inserts an item at index in a list
- `lst:erase(lst, i64, i64)` erases a sublist; the second argument is the start index and the third argument is length of sublist; if third argument exceeds length of list, it'll erase till end of list
- `lst:concat(lst, lst)` concatenates two lists and returns a new list
- `lst:reverse(lst)` reverses a list
- `lst:sublist(lst, i64, i64)` returns a sublist; the second argument is the start index and the third argument is the length of sublist; if third argument exceeds length of list, it'll return till end of list
- `lst:find(lst, any)` returns first index of item, else -1
- `lst:join(lst, str)` joins a list of strings using the delimiter
- `lst:sort(lst)` sorts a list in ascending order

#### Module `map`
`map:concat` is the only manupulative procedure that doesn't work in-place.
This means that it returns a new map instead of modifying the original map.

However, all map related procedures work using shallow copies, and no procedure is provided to create deep copies.

- `map:set(map, str, any)` sets a key-value pair in a map; the first argument is the map, the second argument is the key, and the third argument is the value
- `map:get(map, str)` returns the value for a key in a map; the first argument is the map, and the second argument is the key
- `map:erase(map, str)` erases an item from a map; the first argument is the map, and the second argument is the key
- `map:concat(map, map)` concatenates two maps and returns a new map
- `map:find(map, str)` returns true if key exists, else false
- `map:keys(map)` returns a list of keys in a map
- `map:lockonce(map, i64)` locks a map; the first argument is the map, and the second argument is the locking ID
