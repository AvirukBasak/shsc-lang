// this is a place to start

expression:
    logical_or_expression
    ;

logical_or_expression:
    logical_and_expression
    | logical_or_expression "||" logical_and_expression %left
    ;

logical_and_expression:
    equality_expression
    | logical_and_expression "&&" equality_expression %left
    ;

equality_expression:
    relational_expression
    | equality_expression "==" relational_expression %left
    | equality_expression "!=" relational_expression %left
    ;

relational_expression:
    additive_expression
    | relational_expression "<" additive_expression %left
    | relational_expression ">" additive_expression %left
    | relational_expression "<=" additive_expression %left
    | relational_expression ">=" additive_expression %left
    ;

additive_expression:
    multiplicative_expression
    | additive_expression "+" multiplicative_expression %left
    | additive_expression "-" multiplicative_expression %left
    ;

multiplicative_expression:
    unary_expression
    | multiplicative_expression "*" unary_expression %left
    | multiplicative_expression "/" unary_expression %left
    | multiplicative_expression "%" unary_expression %left
    ;

unary_expression:
    postfix_expression
    | "-" unary_expression %right
    | "!" unary_expression %right
    ;

postfix_expression:
    primary_expression
    | postfix_expression "(" argument_expression_list ")" %left
    | postfix_expression "[" expression "]" %left
    ;

primary_expression:
    identifier
    | constant
    | "(" expression ")"
    ;

constant:
    integer_constant
    | floating_constant
    | character_constant
    | string_literal
    ;

integer_constant:
    LEXTOK_DECINT_LITERAL
    | LEXTOK_HEXINT_LITERAL
    | LEXTOK_OCTINT_LITERAL
    | LEXTOK_BININT_LITERAL
    ;

floating_constant:
    LEXTOK_BINFLOAT_LITERAL
    | LEXTOK_OCTFLOAT_LITERAL
    | LEXTOK_DECFLOAT_LITERAL
    | LEXTOK_HEXFLOAT_LITERAL
    ;

character_constant:
    LEXTOK_CHAR_LITERAL
    ;

string_literal:
    LEXTOK_STR_LITERAL
    ;

identifier:
    LEXTOK_IDENTIFIER
    ;

argument_expression_list:
    expression
    | argument_expression_list "," expression
    ;
