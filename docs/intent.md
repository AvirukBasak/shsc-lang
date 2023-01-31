## Procedures
#### Un-parameterized function
```
start myFunction:
  $a = 45
  $b = 27
  return $a + $b
end

myFunction
```

#### Parameterized function
```
start myFunction:
  $a = $0    // 1st arg
  $b = $1    // 2nd arg
  return $a + $b
end

myFunction 23 67
```

#### Policies
- A function always returns 0 unless return provided
- Error occurrs if less arguments are provided
- Excess arguments are ignored
- `$0` to `$n` are variables to collect function args
- Theoretically, a function can take unlimited arguments
- Return data type is automatically handled

## Datatypes
#### Numbers
```
$a = 44      // integral decimal
$b = 17.28   // floating decimal
$c = -12e4   // scientific decimal
$d = 09      // integral octal
$e = 0x09    // integral hexadecimal
$d = 0b1011  // integral binary
$p = PI      // floating pi
$q = E       // floating Euler's constant
$z = '0'     // integral character
```

#### Strings
```
$a = "Hello, World!"
```

#### Interpolation in strings
```
$name = "Joe"
$age = 23
print `$name is $age years old`
```

#### Arrays
```
$a = [1, 5, 7, 'e', PI, "hello", 0x3a]
$a = [
  [1, 5, 7, 'e', PI, "hello", 0x3a],
  [1, 5, 7, 'e', PI, "hello", 0x3a],
  [1, 5, 7, 'e', PI, "hello", 0x3a],
]

// prints hello
print $a[0][5]
```

#### Maps
Maps use JSON syntax.
```
$person = {
  name: "Joe",
  age: 23,
  uid: 12345,
  address: [
    "address 1",
    "address 2"
  ]
}

print $person.name
print $person["age"]
```

## Constants
```
// global scoped
const MY_CONSTANT 45

start foo:
  // constant and scoped in foo
  const e_pow_2 E**2
  return e_pow_2
end
```

Note that a constant doesn't require the `$` symbol.

## If-else
```
if $condition:
  // code
end

if $condition:
  // code
elif $condition:
  // code
end
```

## Loops
```
loop:
  // forever
end

while $condition:
  // code
end
```

## Scopes
A variable has either global scope or local scope.
