**Last updated on July 12, 2023**

The following is a specification of the syntax and behaviour of the language.

Majority of this is yet to be implemented.

# Syntax Documentation

## File Structure
The interpreter accepts file paths as command-line arguments for the files you want to run. It parses each file and constructs a data structure that maps module names to a list of defined procedures.

## Module Declaration
Each file must start with the following syntax, indicating the module to which the subsequent procedures belong:
```
module module_name
```
Note that there should be no other tokens before the module declaration.

Also, after the module declaration, the same file can't have another module declaration.

Procedure definitions can be placed only after the module declaration.

## Default Main Module
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

## Procedure Declaration
Procedures can only appear after the module declaration.

The basic syntax for declaring a procedure is as follows:
```
proc procname start
    # Procedure code
end
```
The procedure name (`procname`) should be a valid identifier.

## Valid Identifiers
- Should start with either a letter or an underscore.
- Can have alphanumeric characters and underscores.

## Code Organization
Since this language doesn't recognize files, module declarations are used to organize code.
If multiple files have the same module declaration, all procedures will be stored under the same module name.

## Module Access
To access a procedure from a different module, use the following syntax:
```
modulename::procname
```
Replace `modulename` with the appropriate module name and `procname` with the name of the procedure you want to access.

## Entry Point
Program execution starts at `main::main`, i.e., the main procedure of the main module.

## Naming Collision
If there is a naming collision between procedures in the same module, the runtime will raise an error and stop execution.

## End of File
Ensure that each file ends with a newline character, or a syntax error will be thrown.

## Statements
All statements end with a newline.
A statement can be a variable declaration or an expression.

Each statement can have only one variable declaration.

Each variable declared must be given some value.

A good choice is to assign them to `false` (or `null` when that is introduced).

### Expressions
Expressions are basically C expressions with some additional operators.

One addition is the exponentiation operator (`**`).

### If Statements
#### Example 1:
```
if condition then
    # code
end
```

#### Example 2:
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

### While Loops
#### Example:
```
while condition do
    # code
end
```

### For Loops
There are 3 kinds of `for` loops.

#### Default Increment
Increment (or decrement) by 1 depending on the start and end values.
```
var start = 10
for i from start to 0 do
    # this will automatically do decrement by 1
end
```

#### Specified Increment
Increment (or decrement) by the value specified.
```
var end = 10
for i from 0 to end by 2 do
    # this will do an increment by 2
end
```

Note that the following will throw a [warning prompt](#warning-prompt).
```
var end = 10
for i from 0 to end by -2 do
    # this will do a decrement by 2
    # this is a potential infinite loop
end
```

#### List Iteration
```
var list = [ "this", 1, 5, "a", 1, 'i', 's', "t" ]
for i in list do
    # `i` will be a reference to the current element
    # this means the list can be modified using `i`
    # eg: i = "new value"
end
```

### Block Statement
Creates an unnamed scope.
It's pretty much useless.

### Ternary Expression
Follows Python syntax.
#### Example
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

## Warning Prompt

A warning prompt halts execution with a warning and asks the programmer to resume execution.
It can be disabled using the flag `-disable-warning-prompts`.

## Function Arguments
The following is an example of a factorial program that shows how to use function arguments.

#### Example
```
module main

# factorial(num)
proc factorial start
    if $[0] <= 1 then
        return 1
    else
        return $[0] * factorial($[0] - 1)
    end
end

proc main start
    var inp = input("Enter a number: ", i64)
    var res = factorial(inp)
    print("result = {res}\n")
end
```

Arguments to a function is defined by the actual parameters (i.e. at the caller side).

Functions have no prototypes or formal parameters.
