## Intermediate Code

### Concept
- One byte mnemonics i.e. `256` possible combinations.
- In that 1 byte operaion and addressing mode will be specified.
- A max of 3 operands per instruction.
- Each operand has 4 bytes max.
- Can be immediate or address (ref to variable table).
- Will support immediate or direct (variable table).
- There are plans to add indirect addressing mode.
- An `src` can be immediate or address, but a `dest` is always address.
- Datatype is an attribute of the variable table and is inferred at runtime.

### Global Addresses
- A global 32 * 8 byte array is used for fn call args.
- The same can be reused as temporary variables.
- These addresses are accessed from 0 - 31, i.e. these addresses are not stored
  in the variable table but stores whatever the variable table can store.
- These addresses are however swept unconditionally for freeing data everytime a
  procedure returns.

### Basic Instructions
```
mov src, dest (1)
```

An operation here is arithmetic, bitwise, logical or relational.

```
<operation> src, dest            (dest op= src, 1 for each kind of assignment)
<operation> src1, src2, dest     (dest = src1 op src2, 1 for each operator)

call <execution_label>           (auto pushes new stack frame and auto manages variable scope)
ret src                          (auto pops stack frame and calls ref_counting garbage collector
                                     return 0 if void procedure)
brz src, <execution_label> ]
brp src, <execution_label> ]-----(branch if src is zero, positive or negative)
brn src, <execution_label> ]

br <execution_label>             (unconditional branch)
```

- An `execution_label` is basically a position of code file.
- Call to `ret` does the same thing, i.e. it retores the last execution label.

### Addressing Modes

```
src1 is const 0-------  src1 is addr 1-------
src2 is const -0------  src2 is addr -1------

xx------
```

### Notes
- Where the `xx` gives the addressing modes of `src1` and `src2`.
- For a mnemonic, if a `src` field doesn't exist, that bit is read but ignored.
- The remaining 6 bits provide only 64 combinations i.e 64 mnemonics.
- To fit things, only important operations will be given mnemonics, and other
  operations will need to be derived from those.
