%{
#include <stdio.h>
#include <stdlib.h>

extern int lex_line_no;
extern int lex_char_no;
enum LexTokens;

int yyerror(const char* s);
int yylex(void);

%}

Define tokens
%token <token_value> TOK_IDENTIFIER
%token <token_value> TOK_CONSTANT
Add more tokens here based on the LexTokens enum

Define types
%union {
  char* string_value;
  int int_value;
  // Add more types here based on the grammar
}

Define grammar
%start program

%%
program: /* Add rules here */ ;
%%

int main(int argc, char** argv)
{
  FILE* input_file;
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  input_file = fopen(argv[1], "r");
  if (input_file == NULL) {
    fprintf(stderr, "Unable to open input file: %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  yyin = input_file;
  yyparse();
  fclose(input_file);
  return 0;
}

int yylex(void)
{
  int token = get_next_token(yyin);
  switch (token) {
    case TOK_IDENTIFIER:
      yylval.string_value = strdup(get_token_string());
      break;
    case TOK_CONSTANT:
      yylval.int_value = atoi(get_token_string());
      break;
    // Add more cases here based on the tokens defined in the LexTokens enum
    default:
      return token;
  }
  return token;
}
