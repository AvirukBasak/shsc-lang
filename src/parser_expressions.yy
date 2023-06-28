expression:
    assignment_expression
    ;

assignment_expression:
    conditional_expression
    | postfix_expression "=" assignment_expression %right
    | postfix_expression "||=" assignment_expression %right
    | postfix_expression "&&=" assignment_expression %right
    | postfix_expression "|=" assignment_expression %right
    | postfix_expression "^=" assignment_expression %right
    | postfix_expression "&=" assignment_expression %right
    | postfix_expression ">>>=" assignment_expression %right
    | postfix_expression "<<=" assignment_expression %right
    | postfix_expression ">>=" assignment_expression %right
    | postfix_expression "+=" assignment_expression %right
    | postfix_expression "-=" assignment_expression %right
    | postfix_expression "*=" assignment_expression %right
    | postfix_expression "/=" assignment_expression %right
    | postfix_expression "%=" assignment_expression %right
    | postfix_expression "**=" assignment_expression %right
    | postfix_expression "//=" assignment_expression %right
    ;

conditional_expression:
    logical_or_expression
    | expression "if" logical_or_expression "else" conditional_expression %left
    ;

logical_or_expression:
    logical_and_expression
    | logical_or_expression "||" logical_and_expression %left
    ;

logical_and_expression:
    bitwise_or_expression
    | logical_and_expression "&&" bitwise_or_expression %left
    ;

bitwise_or_expression:
    bitwise_xor_expression
    | bitwise_or_expression "|" bitwise_xor_expression %left
    ;

bitwise_xor_expression:
    bitwise_and_expression
    | bitwise_xor_expression "^" bitwise_and_expression %left
    ;

bitwise_and_expression:
    equality_expression
    | bitwise_and_expression "&" equality_expression %left
    ;

equality_expression:
    relational_expression
    | equality_expression "==" relational_expression %left
    | equality_expression "!=" relational_expression %left
    ;

relational_expression:
    shift_expression
    | relational_expression "<" shift_expression %left
    | relational_expression ">" shift_expression %left
    | relational_expression "<=" shift_expression %left
    | relational_expression ">=" shift_expression %left
    ;

shift_expression:
    additive_expression
    | shift_expression ">>>" additive_expression %left
    | shift_expression "<<" additive_expression %left
    | shift_expression ">>" additive_expression %left
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
    | multiplicative_expression "**" unary_expression %right
    | multiplicative_expression "//" unary_expression %left
    ;

unary_expression:
    postfix_expression
    | "-" unary_expression %right
    | "!" unary_expression %right
    | "~" unary_expression %right
    | "++" unary_expression %right
    | "--" unary_expression %right
    ;

postfix_expression:
    primary_expression
    | postfix_expression "(" arguments_list ")" %left
    | postfix_expression "[" expression "]" %left
    | postfix_expression "++"
    | postfix_expression "--"
    | postfix_expression "." identifier %left
    | postfix_expression "::" identifier %left
    ;

primary_expression:
    operand
    | "(" expression ")"
    ;

arguments_list:
    expression
    | arguments_list "," expression %left
    ;
