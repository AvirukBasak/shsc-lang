## Syntax

Syntax is inspired partly by Python, JS and Go.
However, unlike them, this language has a very few datatypes.

Composite data types will be implemented as classes when OOP is introduced.

#### Policies
- Dynamically typed (type inferred at runtime).
- Weakly typed (sensible type coercion).
- Error if type coercion is impossible.
- Objects are objects, everything is not.
- Support for libc functions.
- Apart from primitive datatypes, everything else is an object.
- Syntax should be sensible.
- Should not become JS.

#### Coercion rules
- Any primitive can be coerced to str.
- An str to primitive coercion may fail and cause error.
- Any other conversion must be explicitly done using functions.
- If magic functions are introduced, one may specify their own coercion rules.

#### Expressions
```
r * (cos(a) + sin(b)) - pow(E, sin(ab))
```

#### Assignment
```
x = r * (cos(a) + sin(b)) - pow(E, sin(ab));
```

#### Functions
```
fn cos(x) {
    return sin(PI/2 + x);
}
```

#### Conditional statements
```
if x == 5 {
    x = x + 7;
} else {
    x = x + 8; 
}
```

#### Loops
```
while x < 10 {
    x = x + 1;
}

# for loop will be added when iterables are introduced
```

#### Data memory model
- Primitives: pseudo stack, auto managed
- Objects: heap, reference counted

A pseudo stack is a contiguous (array type) stack maintained in the heap.

#### Datatypes
The following are the 3 of the primitive types:
- char  (char)
- int   (int64_t)
- float (float64_t)

#### Unsafe types (might be added)
The following are the rest primitive types:
- pointers
  - charp
  - intp
  - floatp

#### Currently primitive
**`str (i.e. const char*)`**: will be replaced by the str class when that is introduced.
When that happens, it should no longer be considered a primitive type.

#### OOP to be added
- Class str will replace str
- Class array will be added for arrays
- Basic data structure classes will be added

Objects will always be passed as reference and ref counted.

#### Agenda
1. WAP that supports some basic functions and evaluates an expression
2. Implement assignment to variables
3. Develop a syntax to create functions
4. Develop syntax for loops and conditions
5. Develop an interface with libc
6. Develop modules system
7. Introduce magic functions
8. Add whatever the f*ck you want
