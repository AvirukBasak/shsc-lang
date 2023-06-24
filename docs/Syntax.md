## Syntax

Syntax is inspired partly by Python, JS and Go.
However, unlike them, this language has a very few datatypes.

Composite data types will be implemented as classes when OOP is introduced.

#### Behaviour
- Execution starts at procedure main of the main module, i.e. `main::main()`.
- The main procedure will carry the CLI args as function arguments.
- Function arguments are accessible using the special `$[index]` syntax.

#### Modules
Modules don't require to be imported, only declared in the first line of the file.

If not, those procedures are put automatically in a module called `main`.

The runtime loads as modules the files passed as CLI arguments to the interpreter.

Functions from modules can be accessed by the syntax `module_name::function_name()`.

If the module was not loaded, it'll error out and exit.

Printing verbose information may provide intial information on what is loaded.

#### Policies
- Dynamically typed (type inferred at runtime).
- Weakly typed (sensible type coercion).
- Error if type coercion is impossible.
- Objects are objects, everything is not.
- Support for libc functions.
- Apart from primitive datatypes, everything else should be objects.
- Syntax should be sensible.
- Should not become JS.

#### Coercion rules
- Any primitive can be coerced to string.
- Certain string to primitive coercions may fail and cause error.
- Any primitive type except float can be coerced to bool.
- Float, int and char can be coerced among themselves
- Bool can be coerced to any type.

#### Expressions
```
r * (cos(a) + sin(b)) - pow(E, sin(ab))
```

#### Assignment
```
var x = r * (cos(a) + sin(b)) - pow(E, sin(ab))
x = x + 11
```

#### Functions
```
proc cos start
    return sin(PI/2 + $[1])
end
```

#### Conditional statements
```
if x == 5 then
    x = x + 7
else
    x = x + 8
end
```

#### Loops
```
while x < 10 do
    x = x + 1
end

for i from 0 to 17 by 2 do
    print(i+1)
end
```

#### Data memory model
- Primitives: pseudo stack, auto managed
- Objects: reference counted, auto managed

A pseudo stack is a contiguous (array type) stack maintained in the heap.

#### Datatypes
The following 5 arr the primitive types:
- bool
- char
- int (int64_t)
- float (float64_t)
- string

#### Strings
The current form of strings are purely immutable and useless.
One may use template strings for some string functionality.

#### OOP (if added)
- Class string will replace primitive string type
- Class array will be added for arrays
- Basic data structure classes may be added

Objects will always be passed as reference and ref counted.
