# Language Spec

The syntax of the language is inspired partly by Python, JavaScript, and Go. However, it introduces its own unique features and has a limited set of datatypes.

## Behavior
- Execution starts at the `main::main()` procedure of the main module.
- The `main` procedure receives command-line arguments as function arguments.
- Function arguments are accessible using the special `$[index]` syntax.

## Modules
Modules don't need to be explicitly imported; they are declared in the first line of the file.

If a module declaration is absent, the procedures are automatically placed in a module called `main`.

The runtime loads modules from the files passed as command-line arguments to the interpreter.

Functions from other modules can be accessed using the syntax `module_name::function_name()`.

If the requested module is not loaded, it will raise an error and exit.

Verbose information can be printed to provide initial information on what modules are loaded.

## Policies
- Dynamically typed (type is inferred at runtime).
- Weakly typed (sensible type coercion is performed).
- Error is raised if type coercion is impossible.
- Objects are treated as objects; not everything is an object.
- Support for libc functions.
- Apart from primitive datatypes, everything else should be implemented as objects.
- Syntax aims to be sensible and intuitive.
- Should not resemble JavaScript.

## Coercion Rules
- Any primitive can be coerced to a string.
- Certain string to primitive coercions may fail and raise an error.
- Any primitive type (except float) can be coerced to a bool.
- Float, int, and char can be coerced among themselves.
- Bool can be coerced to any type.

## Expressions
Expressions are written using standard mathematical notation, such as:
```
r * (cos(a) + sin(b)) - pow(E, sin(ab))
```

## Assignment
Variables can be assigned using the following syntax:
```
var x = r * (cos(a) + sin(b)) - pow(E, sin(ab))
x = x + 11
```

## Functions
Function declarations follow the syntax:
```
proc cos start
    return sin(PI/2 + $[0])
end
```

## Conditional Statements
Conditional statements are written using the following syntax:
```
if x == 5 then
    x = x + 7
else
    x = x + 8
end
```

## Loops
Loops can be implemented using the following constructs:
```
while x < 10 do
    x = x + 1
end

for i from 0 to 17 by 2 do
    print(i+1)
end
```

## Data Memory Model
- Primitives are managed in a pseudo stack, which is a contiguous array-like stack maintained in the heap.
- Objects are reference counted and automatically managed.

## Datatypes
The language has the following primitive types:
- bool
- char
- int (int64_t)
- float (float64_t)
- string (immutable)

## Strings
The current form of strings is purely immutable and may have limited functionality. Template strings can be used to provide some string manipulation features.

## OOP Model (if added)
If object-oriented programming is introduced, the following changes will occur:
- The `string` primitive type will be replaced by a `string` class.
- An `array` class will be added for arrays.
- Basic data structure classes may be introduced.

Objects will always be passed as references and reference counted.
