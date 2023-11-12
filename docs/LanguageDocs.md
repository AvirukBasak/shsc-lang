**Last updated on Nov 11, 2023**

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
        - [Lazy const](#lazy-const)
    - [Weak refs](#weak-refs)
        - [Weak ref behaviour](#weak-ref-behaviour)
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
- [Procedures](#procedures)
    - [Example](#example-2)
    - [Procedure arguments](#procedure-arguments)
    - [Arguments to `main:main`](#arguments-to-mainmain)
    - [Procedure context](#procedure-context)
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
        - [Circular references](#circular-references)
    - [Format strings](#format-strings)
    - [Lists](#lists)
        - [Example](#example-5)
    - [Maps](#maps)
        - [Example](#example-6)
- [Built-in procedures](#built-in-procedures)
    - [Globally available](#globally-available)
    - [Module `dbg`](#module-dbg)
    - [Module `io`](#module-io)
    - [Module `it`](#module-it)
    - [Module `chr`](#module-chr)
    - [Module `i64`](#module-i64)
    - [Module `f64`](#module-f64)
    - [Module `str`](#module-str)
    - [Module `lst`](#module-lst)
    - [Module `map`](#module-map)

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
```ruby
module module_name
```
Note that there should be no other tokens before the module declaration, not even newlines.

Also, after the module declaration, the same file can't have another module declaration.

Procedure definitions can be placed only after the module declaration.

### Default main module
If the very first line starts with a procedure declaration (without a module name provided), the runtime assumes the module to be `main` by default.

For example:
```ruby
proc procname start
    # Procedure code
end
```
is equivalent to:
```ruby
module main
proc procname start
    # Procedure code
end
```

### Module access
Modules don't need to be explicitly imported; they're only declared in **line 1** of the file.

To access a procedure from a different module, use the following syntax:
```ruby
modulename:procname
```
Replace `modulename` with the appropriate module name and `procname` with the name of the procedure you want to access.

### Procedure declaration
Procedures can only appear after the module declaration.

The basic syntax for declaring a procedure is as follows:
```ruby
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
For details, see [Procedure arguments](#procedure-arguments).

## Statements
All statements end with a newline.
A statement can be a variable declaration or an expression.

A statement can have only one variable declaration.

Any variable declared must be given some value.

A good choice is to assign them to `null`.

### Variable declaration
You'd use the `var` keyword to create a new variable in current scope.
```ruby
proc test start
    var x = 5
end
```

### Variable shadowing
If you use `var` again, the original variable will be destroyed and replaced by the new one.

```ruby
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
```ruby
proc test start
    var x = const 5
end
```
A constant cannot be shadowed.

#### Lazy const
Lazy `const` allows you to create a variable and later on make it constant.
```ruby
proc test start
    var x = "default value"
    x = const mod:get_some_value()
end
```

### Weak refs
You'd use the `weak` keyword to create a weak reference in current scope.
```ruby
proc test start
    var x = { a: "some data", b: {} }
    var x.b.circular = weak x
end
```

Weak references are useful for creating circular references.

Note that not using `weak` in a circular reference will cause a memory leak because the language uses reference counting GC. See [Circular references](#circular-references) for more details.

#### Weak ref behaviour
- Not using `weak` keyword automatically creates a strong reference.
- Thus, strong references can be made to objects via a weak reference. For example:
    ```ruby
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

#### Example
```ruby
x = 5; y = 7
io:print(x, y, lf)
```

## If statements
### Example 1:
```ruby
if condition then
    # code
end
```

### Example 2:
```ruby
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
```ruby
while condition do
    # code
end
```

## For Loops
There are 3 kinds of `for` loops.

### Default increment
Increment (or decrement) by 1 depending on the start and end values.
```ruby
var start = 10
for i from start to 0 do
    # this will automatically do decrement by 1
end
```

### Specified increment
Increment (or decrement) by the value specified.
```ruby
var end = 10
for i from 0 to end by 2 do
    # this will do an increment by 2
end
```

Note that the following will cause an error.
```ruby
var end = 10
for i from 0 to end by -2 do
    # this will do a decrement by 2
    # this is a potential infinite loop
end
```

### Iterable
This syntax works for maps, lists, and strings.
```ruby
var list = [ "this", 1, 5, "a", 1, 'i', 's', "t" ]
for i, e in list do
    # `e` is a copy of the item at index `i`
end
```

For maps, use
```ruby
for k, v in my_map do
    # `v` is a copy of the value for key `k`
end
```

For a shorter syntax, you may use the following
```ruby
for v in my_iterable do
    # `v` is a copy of the value
    # the syntax works for maps, lists, and strings
end
```

## Block statement
Creates an unnamed scope.
It's pretty much useless.

## Procedures
The following is an example of a factorial program that shows how to use procedures.

### Example
```ruby
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

### Procedure arguments

#### Example
Four ways to access the first (0th) argument to a procedure.
```ruby
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

### Arguments to `main:main`
The arguments to `main:main` are the command-line arguments passed to the interpreter.

### Procedure context
If the `.` or map membership operator is used to access a reference to a procedure, the procedure context object is set to the parent map.

Note that this works only if a procedure is accessed from a map using the `.` operator.

The context object can be accessed using the `this` keyword inside a procedure. This is useful for a limited form of object-oriented programming.

In case there is no context object, `this` will be `null`.

#### OOP Example
```ruby
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

```ruby
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

## Expressions
Expressions are basically C expressions with some additional operators.

Some additions include exponentiation operator (`**`) and floor division (`//`).

### Ternary expression
Follows Python syntax.

```ruby
expression if condition else expression
```

### Assignments
An assignment is possible only to an already existing variable.

The language supports `=` and all the shortcut assignments.

An assignment is a part of an expression, which means you can do the same operations as in C.

#### Example
```ruby
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
- `proc` i64 value indicating the proc type

The term `built-in` is more accurate for these and we will not call these *primitive*s.
The language has built-in support for complex composite data structures which can be used using the literals syntax.

### Memory management
Memory is managed by allocating data in the heap, and maintaining a reference count.

The reference count is updated when data is assigned among the variables and also the accumulator.

In case the reference count becomes `0`, the data is freed immediately.

### Memory allocation
New memory is allocated for every new literal, even if two literals are identical by value.

#### Example
```ruby
var x = "hello world"
var y = "hello world"
```

Results in two seperate copies of the string `"hello world"` being created for the seperate variables.

The same idea is followed for all other literals, including lists and maps.

### Memory ownership
Ownership in our case is being able to destroy the data (free memory).

The following takes memory ownership
- Any variable to whom data is assigned (until reassigned)
- Accumulator; or else procedure returns won't work (temporarily)

#### Accumulator
The language uses a temporary location called the `accumulator` to store the result of operations and return values.

#### Circular references
This language is unable to detect and manage circular references.
If a circular reference must be created, it must be a weak reference. See [Weak refs](#weak-refs) for more details.

Running `tostr` or `io:print` on an object having a circular reference will most likely result in stack overflow or Segmentation fault.

Avoid using same variables for weak and strong references.

Additionally, using non-weak circular references **WILL** cause memory leak.

### Format strings
```ruby
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
```ruby
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
```ruby
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
```ruby
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

## Built-in procedures
The language supports the following built-in procedures (within built-in modules)

#### Globally available
- `isnull(any)` returns true if data is `null`, else false
- `tostr(any)` stringifies a built-in; for lists and maps, it's JSON-like stringification; for circular references, it'll most likely result in stack overflow or segmentation fault
- `type(any)` returns one of the [global variables for types](#global-variables-for-types)

#### Module `dbg`
- `dbg:typename(any)` returns type name of data as string
- `dbg:rtsize(any)` returns size of data in bytes
- `dbg:refcnt(any)` returns total number of references to an object
- `dbg:id(any)` returns hex string of the memory address of an object
- `dbg:callproc(any, str, str, lst)` calls a procedure from a module; the first argument is the context object, the second argument is the module name, the third argument is the procedure name, and the fourth argument is the list of arguments to the procedure
- `dbg:filename()` returns filename of the source file where called
- `dbg:lineno()` returns line number of the source file where called

#### Module `io`
- `io:print(any, ...)` prints string form of data (calls `tostr`)
- `io:input(str, i64)` where the first argument is the prompt and the second argument is the type of input, see [Global variables for types](#global-variables-for-types)

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
- `chr:max(chr, i64, f64, ...)` returns the greater of the numbers
- `chr:min()` returns the smallest possible character
- `chr:min(chr, i64, f64, ...)` returns the smaller of the numbers

#### Module `i64`
- `i64:max()` returns the greatest possible i64
- `i64:max(chr, i64, f64, ...)` returns the greater of the numbers
- `i64:min()` returns the smallest possible i64
- `i64:min(chr, i64, f64, ...)` returns the smaller of the numbers

#### Module `f64`
- `f64:max()` returns the greatest possible f64
- `f64:max(chr, i64, f64, ...)` returns the greater of the numbers
- `f64:min()` returns the smallest possible f64
- `f64:min(chr, i64, f64, ...)` returns the smaller of the numbers

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
