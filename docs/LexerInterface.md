## Lexer Interface
The `lexer.h` file provides a bunch of functions to extract tokens from a source file.

The idea is to pass the `FILE*` to the `lex_Token_getnext` function and have it return a `lex_Token_t` enum, which then can be `switch-case`d.

Every time `lex_Token_getnext` returns a `lex_Token_t`, it buffers the actual string form of the token. This string can be extracted using `lex_Buffer_getstr`.

This function returns only a reference to the string in the buffer, so any further call to `lex_Token_getnext` will overwrite the buffer with the new token.

To get your own copy of the returned token, copy the string to a seperate memory location.

The memory of the buffer is managed automatically, so you don't need to worry.

Note that you cannot unget a token to the lexer.

## External Interface
- `lex_Token_t lex_Token_getnext(FILE*)` Get next token
- `char *lex_Token_getcode(lex_Token_t)` Get string code
- `char *lex_Token_getsymbol(lex_Token_t)` Get default symbol
- `char *lex_Buffer_getstr()` Get token string
- `int lex_line_no` Get file line number
- `int lex_char_no` Get line char number

## Ignored inputs
Any character that the lexer ignores is not put into the buffer.

Exclusive code is used for reading such characters if they are ever used as literals.

The lexer automatically ignores:
- Spaces, tabs, CRs and LFs
- Comments i.e. characters from `#` to `\n`
