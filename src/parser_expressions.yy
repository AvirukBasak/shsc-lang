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
    operand
    | "(" expression ")"
    ;

argument_expression_list:
    expression
    | argument_expression_list "," expression
    ;
