#ifndef RUNTIME_H
#define RUNTIME_H

#include "ast.h"
#include "runtime/data.h"

typedef struct RT_StackEntry_t RT_StackEntry_t;

enum RT_StackEntryType_t {
    STACKENTRY_ASTNODE_TYPE_STATEMENTS,
    STACKENTRY_ASTNODE_TYPE_STATEMENT,
    STACKENTRY_ASTNODE_TYPE_ASSIGNMENT,
    STACKENTRY_ASTNODE_TYPE_IF_BLOCK,
    STACKENTRY_ASTNODE_TYPE_ELSE_BLOCK,
    STACKENTRY_ASTNODE_TYPE_WHILE_BLOCK,
    STACKENTRY_ASTNODE_TYPE_FOR_BLOCK,
    STACKENTRY_ASTNODE_TYPE_EXPRESSION,
    STACKENTRY_ASTNODE_TYPE_COMMA_SEP_LIST,
    STACKENTRY_ASTNODE_TYPE_LITERAL,
    STACKENTRY_ASTNODE_TYPE_IDENTIFIER,

    STACKENTRY_STATES_TYPE_LOOP,
    STACKENTRY_STATES_TYPE_EXPR,

    STACKENTRY_TYPE_ASTNODE,
    STACKENTRY_TYPE_STATE,
    STACKENTRY_TYPE_SCOPE_POP,
    STACKENTRY_TYPE_PROC_POP,
};

union RT_StackEntry_AST_Node_t {
    const AST_Statements_t   *code;
    const AST_Statement_t    *statement;
    const AST_Assignment_t   *assignment;
    const AST_CompoundSt_t   *compound_st;
    const AST_IfBlock_t      *if_block;
    const AST_ElseBlock_t    *else_block;
    const AST_WhileBlock_t   *while_block;
    const AST_ForBlock_t     *for_block;
    const AST_Block_t        *block;
    const AST_Expression_t   *expression;
    const AST_CommaSepList_t *comma_list;
    const AST_Literal_t      *literal;
    const AST_Identifier_t   *identifier;
};

union RT_StackEntry_States_t {
    /** used by loops in runtime to maintain counter state */
    struct {
        const AST_ForBlock_t *for_block;
        union {
            struct {
                int64_t start;
                int64_t end;
                int64_t by;
            } range;
            struct {
                RT_DataList_t *lst;
                RT_DataStr_t *str;
                enum RT_DataType_t type;
            } iter;
        } it;
        int64_t i;
        bool is_running;
    } lp;
    /* used during expression evaluation to store temporary data */
    struct {
        /* eval the ast node and produce RT_Data_t */
        const AST_Expression_t *expr;
        RT_Data_t *lhs;
        RT_Data_t *rhs;
        RT_Data_t *extra;
    } xp;
};

/* specialised union of types to be pushed in runtime stack */
struct RT_StackEntry_t {
    union {
        union RT_StackEntry_AST_Node_t node;
        union RT_StackEntry_States_t state;
    } entry;
    enum RT_StackEntryType_t type;
};

extern const char *rt_currfile;
extern int rt_currline;

void rt_exec(void);

#endif
