## Lexer Interface
The `lexer.h` file provides a bunch of functions to extract tokens from a source file.

The idea is to pass the `FILE*` to the `lex_get_nexttok` function and have it return a `LexToken` enum, which then can be `switch-case`d.

Every time `lex_get_nexttok` returns a `LexToken`, it buffers the actual string form of the token. This string can be extracted using `lex_get_buffstr`.

This function returns only a reference to the string in the buffer, so any further call to `lex_get_nexttok` will overwrite the buffer with the new token.

To get your own copy of the returned token, copy the string to a seperate memory location.

The memory of the buffer is managed automatically, so you don't need to worry.

Note that you cannot unget a token to the lexer.

## External Interface
- `LexToken lex_get_nexttok(FILE*)` Get next token
- `char *lex_get_tokcode(LexToken)` Get string code
- `char *lex_get_symbol(LexToken)` Get default symbol
- `char *lex_get_buffstr()` Get token string
- `int lex_line_no` Get file line number
- `int lex_char_no` Get line char number

## Ignored inputs
Any character that the lexer ignores is not put into the buffer.

Exclusive code is used for reading such characters if they are ever used as literals.

The lexer automatically ignores:
- Spaces, tabs, CRs and LFs
- Comments i.e. characters from `#` to `\n`
