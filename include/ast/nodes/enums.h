#ifndef AST_ENUMS_H
#define AST_ENUMS_H

enum AST_StatementType_t {
    STATEMENT_TYPE_EMPTY,
    STATEMENT_TYPE_RETURN,
    STATEMENT_TYPE_ASSIGNMENT,
    STATEMENT_TYPE_COMPOUND,
};

enum AST_AssignmentType_t {
    /** return value of RHS discarded */
    ASSIGNMENT_TYPE_TOVOID,
    /** create or shadow existing variable */
    ASSIGNMENT_TYPE_CREATE,
};

enum AST_CompoundStType_t {
    COMPOUNDST_TYPE_IF,
    COMPOUNDST_TYPE_WHILE,
    COMPOUNDST_TYPE_FOR,
    COMPOUNDST_TYPE_BLOCK,
};

enum AST_ForBlockType_t {
    FORBLOCK_TYPE_RANGE,
    FORBLOCK_TYPE_LIST,
};

enum AST_ExpressionType_t {
    EXPR_TYPE_EXPRESSION,
    EXPR_TYPE_LITERAL,
    EXPR_TYPE_IDENTIFIER,
    EXPR_TYPE_LIST,
    EXPR_TYPE_NULL,
};

/* based on the mapping of datatype IDs provided
   by the Scsh IR Spec
   https://github.com/AvirukBasak/scsh-runtime/docs/ScshIrSpec.md */
enum AST_DataType_t {
    DATA_TYPE_BUL = 0,        /* boolean        : 1 B */
    DATA_TYPE_CHR = 1,        /* char           : 1 B */
    DATA_TYPE_I64 = 2,        /* int64_t        : 8 B */
    DATA_TYPE_F64 = 3,        /* double         : 8 B */
    DATA_TYPE_STR = 4,        /* char*          : variable  */
    DATA_TYPE_INTERP_STR = 5, /* parsable char* : variable  */
    DATA_TYPE_LST = 6,        /* linked list    : variable  */
    DATA_TYPE_ANY = 7,        /* void*          : undefined */
};

#endif
