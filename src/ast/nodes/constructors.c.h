#ifndef AST_NODES_CONSTRUCTORS_C_H
#define AST_NODES_CONSTRUCTORS_C_H

#include <stdlib.h>

#include "ast/nodes.h"
#include "errcodes.h"
#include "io.h"

AST_Statements_t *AST_Statements(AST_Statements_t *statements, AST_Statement_t *statement)
{
    AST_Statements_t *stmts = (AST_Statements_t*) malloc(sizeof(AST_Statements_t));
    if (!stmts) io_errndie("AST_Statements:" ERR_MSG_MALLOCFAIL);
    stmts->statements = statements;
    stmts->statement = statement;
    return stmts;
}

AST_Statement_t *AST_Statement_empty(int line_no) {
    AST_Statement_t *stmt = (AST_Statement_t*) malloc(sizeof(AST_Statement_t));
    if (!stmt) io_errndie("AST_Statement_empty:" ERR_MSG_MALLOCFAIL);
    stmt->type = STATEMENT_TYPE_EMPTY;
    stmt->statement.assignment = NULL;
    stmt->line_no = line_no;
    return stmt;
}

AST_Statement_t *AST_Statement_break(int line_no)
{
    AST_Statement_t *stmt = (AST_Statement_t*) malloc(sizeof(AST_Statement_t));
    if (!stmt) io_errndie("AST_Statement_break:" ERR_MSG_MALLOCFAIL);
    stmt->type = STATEMENT_TYPE_BREAK;
    stmt->statement.assignment = NULL;
    stmt->line_no = line_no;
    return stmt;
}

AST_Statement_t *AST_Statement_continue(int line_no)
{
    AST_Statement_t *stmt = (AST_Statement_t*) malloc(sizeof(AST_Statement_t));
    if (!stmt) io_errndie("AST_Statement_continue:" ERR_MSG_MALLOCFAIL);
    stmt->type = STATEMENT_TYPE_CONTINUE;
    stmt->statement.assignment = NULL;
    stmt->line_no = line_no;
    return stmt;
}

AST_Statement_t *AST_Statement_return(AST_Expression_t *expression, int line_no)
{
    AST_Statement_t *stmt = (AST_Statement_t*) malloc(sizeof(AST_Statement_t));
    if (!stmt) io_errndie("AST_Statement_return:" ERR_MSG_MALLOCFAIL);
    stmt->type = STATEMENT_TYPE_RETURN;
    stmt->statement.expression = expression;
    stmt->line_no = line_no;
    return stmt;
}

AST_Statement_t *AST_Statement_Assignment(AST_Assignment_t *assignment, int line_no)
{
    AST_Statement_t *stmt = (AST_Statement_t*) malloc(sizeof(AST_Statement_t));
    if (!stmt) io_errndie("AST_Statement_Assignment:" ERR_MSG_MALLOCFAIL);
    stmt->type = STATEMENT_TYPE_ASSIGNMENT;
    stmt->statement.assignment = assignment;
    stmt->line_no = line_no;
    return stmt;
}

AST_Statement_t *AST_Statement_CompoundSt(AST_CompoundSt_t *compound, int line_no)
{
    AST_Statement_t *stmt = (AST_Statement_t*) malloc(sizeof(AST_Statement_t));
    if (!stmt) io_errndie("AST_Statement_CompoundSt:" ERR_MSG_MALLOCFAIL);
    stmt->type = STATEMENT_TYPE_COMPOUND;
    stmt->statement.compound_statement = compound;
    stmt->line_no = line_no;
    return stmt;
}

AST_Assignment_t *AST_Assignment_create(AST_Identifier_t *identifier, AST_Expression_t *expression)
{
    AST_Assignment_t *assign = (AST_Assignment_t*) malloc(sizeof(AST_Assignment_t));
    if (!assign) io_errndie("AST_Assignment_create:" ERR_MSG_MALLOCFAIL);
    assign->lhs = identifier;
    assign->rhs = expression;
    assign->type = ASSIGNMENT_TYPE_CREATE;
    return assign;
}

AST_Assignment_t *AST_Assignment_tovoid(AST_Expression_t *expression)
{
    AST_Assignment_t *assign = (AST_Assignment_t*) malloc(sizeof(AST_Assignment_t));
    if (!assign) io_errndie("AST_Assignment_tovoid:" ERR_MSG_MALLOCFAIL);
    assign->lhs = NULL;
    assign->rhs = expression;
    assign->type = ASSIGNMENT_TYPE_TOVOID;
    return assign;
}

AST_CompoundSt_t *AST_CompoundSt_IfBlock(AST_IfBlock_t *block)
{
    AST_CompoundSt_t *compound = (AST_CompoundSt_t*) malloc(sizeof(AST_CompoundSt_t));
    if (!compound) io_errndie("AST_CompoundSt_IfBlock:" ERR_MSG_MALLOCFAIL);
    compound->type = COMPOUNDST_TYPE_IF;
    compound->compound_statement.if_block = block;
    return compound;
}

AST_CompoundSt_t *AST_CompoundSt_WhileBlock(AST_WhileBlock_t *block)
{
    AST_CompoundSt_t *compound = (AST_CompoundSt_t*) malloc(sizeof(AST_CompoundSt_t));
    if (!compound) io_errndie("AST_CompoundSt_WhileBlock:" ERR_MSG_MALLOCFAIL);
    compound->type = COMPOUNDST_TYPE_WHILE;
    compound->compound_statement.while_block = block;
    return compound;
}

AST_CompoundSt_t *AST_CompoundSt_ForBlock(AST_ForBlock_t *block)
{
    AST_CompoundSt_t *compound = (AST_CompoundSt_t*) malloc(sizeof(AST_CompoundSt_t));
    if (!compound) io_errndie("AST_CompoundSt_ForBlock:" ERR_MSG_MALLOCFAIL);
    compound->type = COMPOUNDST_TYPE_FOR;
    compound->compound_statement.for_block = block;
    return compound;
}

AST_CompoundSt_t *AST_CompoundSt_Block(AST_Block_t *block)
{
    AST_CompoundSt_t *compound = (AST_CompoundSt_t*) malloc(sizeof(AST_CompoundSt_t));
    if (!compound) io_errndie("AST_CompoundSt_Block:" ERR_MSG_MALLOCFAIL);
    compound->type = COMPOUNDST_TYPE_BLOCK;
    compound->compound_statement.block = block;
    return compound;
}

AST_IfBlock_t *AST_IfBlock(AST_Condition_t *condition, AST_Statements_t *if_st, AST_ElseBlock_t *else_block)
{
    AST_IfBlock_t *if_block = (AST_IfBlock_t*) malloc(sizeof(AST_IfBlock_t));
    if (!if_block) io_errndie("AST_IfBlock:" ERR_MSG_MALLOCFAIL);
    if_block->condition = condition;
    if_block->if_st = if_st;
    if_block->else_block = else_block;
    return if_block;
}

AST_ElseBlock_t *AST_ElseBlock(AST_Condition_t *condition, AST_Statements_t *else_if_st, AST_ElseBlock_t *else_block)
{
    AST_ElseBlock_t *block = (AST_ElseBlock_t*) malloc(sizeof(AST_ElseBlock_t));
    if (!block) io_errndie("AST_ElseBlock:" ERR_MSG_MALLOCFAIL);
    block->condition = condition;
    block->else_if_st = else_if_st;
    block->else_block = else_block;
    return block;
}

AST_WhileBlock_t *AST_WhileBlock(AST_Condition_t *condition, AST_Statements_t *while_st)
{
    AST_WhileBlock_t *while_block = (AST_WhileBlock_t*) malloc(sizeof(AST_WhileBlock_t));
    if (!while_block) io_errndie("AST_WhileBlock:" ERR_MSG_MALLOCFAIL);
    while_block->condition = condition;
    while_block->statements = while_st;
    return while_block;
}

AST_ForBlock_t *AST_ForBlock(AST_Identifier_t *val, AST_Expression_t *start, AST_Expression_t *end, AST_Expression_t *by, AST_Statements_t *for_st)
{
    AST_ForBlock_t *for_block = (AST_ForBlock_t*) malloc(sizeof(AST_ForBlock_t));
    if (!for_block) io_errndie("AST_ForBlock:" ERR_MSG_MALLOCFAIL);
    for_block->idx = NULL;
    for_block->val = val;
    for_block->it.range.start = start;
    for_block->it.range.end = end;
    for_block->it.range.by = by;
    for_block->statements = for_st;
    for_block->type = FORBLOCK_TYPE_RANGE;
    return for_block;
}

AST_ForBlock_t *AST_ForBlock_iterate(AST_Identifier_t *idx, AST_Identifier_t *val, AST_Expression_t *iterable, AST_Statements_t *for_st)
{
    AST_ForBlock_t *for_block = (AST_ForBlock_t*) malloc(sizeof(AST_ForBlock_t));
    if (!for_block) io_errndie("AST_ForBlock_iterate:" ERR_MSG_MALLOCFAIL);
    for_block->idx = idx;
    for_block->val = val;
    for_block->it.iterable = iterable;
    for_block->statements = for_st;
    for_block->type = FORBLOCK_TYPE_LIST;
    return for_block;
}

AST_Block_t *AST_Block(AST_Statements_t *statements)
{
    AST_Block_t *block = (AST_Block_t*) malloc(sizeof(AST_Block_t));
    if (!block) io_errndie("AST_Block:" ERR_MSG_MALLOCFAIL);
    block->statements = statements;
    return block;
}

#define AST_EXPRESSION_ISOPERAND(expr_) ({             \
    AST_Expression_t *expr = expr_;                    \
    expr && expr->op == TOKOP_NOP                      \
         && ( expr->lhs_type == EXPR_TYPE_LITERAL      \
           || expr->lhs_type == EXPR_TYPE_IDENTIFIER ) \
         && expr->rhs_type == EXPR_TYPE_NULL           \
         && expr->condition_type == EXPR_TYPE_NULL;    \
})

AST_Expression_t *AST_Expression(AST_Operator_t op, AST_Expression_t *lhs, AST_Expression_t *rhs, AST_Expression_t *condition)
{
    AST_Expression_t *expression = (AST_Expression_t*) malloc(sizeof(AST_Expression_t));
    if (!expression) io_errndie("AST_Expression:" ERR_MSG_MALLOCFAIL);
    expression->op = op;

    if (AST_EXPRESSION_ISOPERAND(lhs)) {
        expression->lhs_type = lhs->lhs_type;
        expression->lhs = lhs->lhs;
        lhs->lhs.expr = NULL;
        lhs->lhs_type = EXPR_TYPE_NULL;
        AST_Expression_destroy(&lhs);
    } else {
        expression->lhs_type = lhs ? EXPR_TYPE_EXPRESSION : EXPR_TYPE_NULL;
        expression->lhs.expr = lhs;
    }

    if (AST_EXPRESSION_ISOPERAND(rhs)) {
        expression->rhs_type = rhs->lhs_type;
        expression->rhs = rhs->lhs;
        rhs->lhs.expr = NULL;
        rhs->lhs_type = EXPR_TYPE_NULL;
        AST_Expression_destroy(&rhs);
    } else {
        expression->rhs_type = rhs ? EXPR_TYPE_EXPRESSION : EXPR_TYPE_NULL;
        expression->rhs.expr = rhs;
    }

    if (AST_EXPRESSION_ISOPERAND(condition)) {
        expression->condition_type = condition->lhs_type;
        expression->condition = condition->lhs;
        condition->lhs.expr = NULL;
        condition->lhs_type = EXPR_TYPE_NULL;
        AST_Expression_destroy(&condition);
    } else {
        expression->condition_type = condition ? EXPR_TYPE_EXPRESSION : EXPR_TYPE_NULL;
        expression->condition.expr = condition;
    }

    return expression;
}

AST_Expression_t *AST_Expression_Literal(AST_Literal_t *literal)
{
    AST_Expression_t *expression = (AST_Expression_t*) malloc(sizeof(AST_Expression_t));
    if (!expression) io_errndie("AST_Expression_Literal:" ERR_MSG_MALLOCFAIL);
    expression->op = TOKOP_NOP;
    expression->lhs_type = EXPR_TYPE_LITERAL;
    expression->lhs.literal = literal;
    expression->rhs_type = EXPR_TYPE_NULL;
    expression->rhs.expr = NULL;
    expression->condition_type = EXPR_TYPE_NULL;
    expression->condition.expr = NULL;
    return expression;
}

AST_Expression_t *AST_Expression_Identifier(AST_Identifier_t *identifier)
{
    AST_Expression_t *expression = (AST_Expression_t*) malloc(sizeof(AST_Expression_t));
    if (!expression) io_errndie("AST_Expression_Identifier:" ERR_MSG_MALLOCFAIL);
    expression->op = TOKOP_NOP;
    expression->lhs_type = EXPR_TYPE_IDENTIFIER;
    expression->lhs.variable = identifier;
    expression->rhs_type = EXPR_TYPE_NULL;
    expression->rhs.expr = NULL;
    expression->condition_type = EXPR_TYPE_NULL;
    expression->condition.expr = NULL;
    return expression;
}

AST_Expression_t *AST_Expression_CommaSepList(AST_CommaSepList_t *comma_list)
{
    AST_Expression_t *expression = (AST_Expression_t*) malloc(sizeof(AST_Expression_t));
    if (!expression) io_errndie("AST_Expression_CommaSepList:" ERR_MSG_MALLOCFAIL);
    expression->op = TOKOP_NOP;
    expression->lhs_type = EXPR_TYPE_LITERAL;
    expression->lhs.literal = AST_Literal_lst(comma_list);
    expression->rhs_type = EXPR_TYPE_NULL;
    expression->rhs.expr = NULL;
    expression->condition_type = EXPR_TYPE_NULL;
    expression->condition.expr = NULL;
    return expression;
}

AST_CommaSepList_t *AST_CommaSepList(AST_CommaSepList_t *comma_list, AST_Expression_t *expression)
{
    AST_CommaSepList_t *comma_sep_list = (AST_CommaSepList_t*) malloc(sizeof(AST_CommaSepList_t));
    if (!comma_sep_list) io_errndie("AST_CommaSepList:" ERR_MSG_MALLOCFAIL);
    comma_sep_list->comma_list = comma_list;
    comma_sep_list->expression = expression;
    return comma_sep_list;
}

AST_AssociativeList_t *AST_AssociativeList(AST_AssociativeList_t *assoc_list, AST_Literal_t *key, AST_Expression_t *value)
{
    AST_AssociativeList_t *associative_list = (AST_AssociativeList_t*) malloc(sizeof(AST_AssociativeList_t));
    if (!associative_list) io_errndie("AST_AssociativeList_t:" ERR_MSG_MALLOCFAIL);
    associative_list->assoc_list = assoc_list;
    associative_list->key = key;
    associative_list->value = value;
    return associative_list;
}

AST_Literal_t *AST_Literal_bul(bool literal)
{
    AST_Literal_t *AST_literal = (AST_Literal_t*) malloc(sizeof(AST_Literal_t));
    if (!AST_literal) io_errndie("AST_Literal_bul:" ERR_MSG_MALLOCFAIL);
    AST_literal->type = DATA_TYPE_BUL;
    AST_literal->data.bul = literal;
    return AST_literal;
}

AST_Literal_t *AST_Literal_chr(char literal)
{
    AST_Literal_t *AST_literal = (AST_Literal_t*) malloc(sizeof(AST_Literal_t));
    if (!AST_literal) io_errndie("AST_Literal_chr:" ERR_MSG_MALLOCFAIL);
    AST_literal->type = DATA_TYPE_CHR;
    AST_literal->data.chr = literal;
    return AST_literal;
}

AST_Literal_t *AST_Literal_f64(double literal)
{
    AST_Literal_t *AST_literal = (AST_Literal_t*) malloc(sizeof(AST_Literal_t));
    if (!AST_literal) io_errndie("AST_Literal_f64:" ERR_MSG_MALLOCFAIL);
    AST_literal->type = DATA_TYPE_F64;
    AST_literal->data.f64 = literal;
    return AST_literal;
}

AST_Literal_t *AST_Literal_i64(int64_t literal)
{
    AST_Literal_t *AST_literal = (AST_Literal_t*) malloc(sizeof(AST_Literal_t));
    if (!AST_literal) io_errndie("AST_Literal_i64:" ERR_MSG_MALLOCFAIL);
    AST_literal->type = DATA_TYPE_I64;
    AST_literal->data.i64 = literal;
    return AST_literal;
}

AST_Literal_t *AST_Literal_str(char *literal)
{
    AST_Literal_t *AST_literal = (AST_Literal_t*) malloc(sizeof(AST_Literal_t));
    if (!AST_literal) io_errndie("AST_Literal_str:" ERR_MSG_MALLOCFAIL);
    AST_literal->type = DATA_TYPE_STR;
    AST_literal->data.str = literal;
    return AST_literal;
}

AST_Literal_t *AST_Literal_interp_str(char *literal)
{
    AST_Literal_t *AST_literal = (AST_Literal_t*) malloc(sizeof(AST_Literal_t));
    if (!AST_literal) io_errndie("AST_Literal_interp_str:" ERR_MSG_MALLOCFAIL);
    AST_literal->type = DATA_TYPE_INTERP_STR;
    AST_literal->data.str = literal;
    return AST_literal;
}

AST_Literal_t *AST_Literal_lst(AST_CommaSepList_t *literal)
{
    AST_Literal_t *AST_literal = (AST_Literal_t*) malloc(sizeof(AST_Literal_t));
    if (!AST_literal) io_errndie("AST_Literal_lst:" ERR_MSG_MALLOCFAIL);
    AST_literal->type = DATA_TYPE_LST;
    AST_literal->data.lst = literal;
    return AST_literal;
}

AST_Literal_t *AST_Literal_map(AST_AssociativeList_t *literal)
{
    AST_Literal_t *AST_literal = (AST_Literal_t*) malloc(sizeof(AST_Literal_t));
    if (!AST_literal) io_errndie("AST_Literal_map:" ERR_MSG_MALLOCFAIL);
    AST_literal->type = DATA_TYPE_MAP;
    AST_literal->data.mp = literal;
    return AST_literal;
}

AST_Identifier_t *AST_Identifier(char *identifier_name)
{
    AST_Identifier_t *identifier = (AST_Identifier_t*) malloc(sizeof(AST_Identifier_t));
    if (!identifier) io_errndie("AST_Identifier:" ERR_MSG_MALLOCFAIL);
    identifier->identifier_name = identifier_name;
    return identifier;
}

#else
    #warning re-inclusion of module 'ast/nodes/constructors.c.h'
#endif