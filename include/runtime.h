#ifndef RUNTIME_H
#define RUNTIME_H

typedef struct RT_StackEntry_t RT_StackEntry_t;

enum RT_StackEntryType_t {
    STACKENTRY_TYPE_STATEMENTS,
    STACKENTRY_TYPE_STATEMENT,
    STACKENTRY_TYPE_ASSIGNMENT,
    STACKENTRY_TYPE_IF_BLOCK,
    STACKENTRY_TYPE_ELSE_IF_BLOCK,
    STACKENTRY_TYPE_ELSE_IF_STATEMENT,
    STACKENTRY_TYPE_WHILE_BLOCK,
    STACKENTRY_TYPE_FOR_BLOCK,
    STACKENTRY_TYPE_EXPRESSION,
    STACKENTRY_TYPE_COMMA_SEP_LIST,
    STACKENTRY_TYPE_LITERAL,
    STACKENTRY_TYPE_IDENTIFIER,
    STACKENTRY_TYPE_SCOPE_POP,
    STACKENTRY_TYPE_PROC_POP,
};

/* specialised union of types to be pushed in runtime stack */
struct RT_StackEntry_t {
    union {
        const AST_Statements_t   *code;
        const AST_Statement_t    *statement;
        const AST_Assignment_t   *assignment;
        const AST_CompoundSt_t   *compound_st;
        const AST_IfBlock_t      *if_block;
        const AST_ElseIfBlock_t  *else_if_block;
        const AST_ElseIfSt_t     *else_if_st;
        const AST_WhileBlock_t   *while_block;
        const AST_ForBlock_t     *for_block;
        const AST_Block_t        *block;
        const AST_Expression_t   *expression;
        const AST_CommaSepList_t *comma_list;
        const AST_Literal_t      *literal;
        const AST_Identifier_t   *identifier;
    } node;
    enum RT_StackEntryType_t type;
};

extern const char *rt_currfile;
extern int rt_currline;

void rt_exec(void);

#endif
