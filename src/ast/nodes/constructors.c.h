#ifndef AST_NODES_CONSTRUCTORS_C_H
#define AST_NODES_CONSTRUCTORS_C_H

#include <stdlib.h>

#include "ast.h"
#include "ast/nodes.h"
#include "ast/nodes/enums.h"
#include "errcodes.h"
#include "io.h"

ast_Statements_t *ast_Statements(ast_Statements_t *statements, ast_Statement_t *statement)
{
    ast_Statements_t *stmts = (ast_Statements_t*) malloc(sizeof(ast_Statements_t));
    if (!stmts) io_errndie("ast_Statements:" ERR_MSG_MALLOCFAIL);
    stmts->statements = statements;
    stmts->statement = statement;
    return stmts;
}

ast_Statement_t *ast_Statement_empty(int line_no) {
    ast_Statement_t *stmt = (ast_Statement_t*) malloc(sizeof(ast_Statement_t));
    if (!stmt) io_errndie("ast_Statement_empty:" ERR_MSG_MALLOCFAIL);
    stmt->type = STATEMENT_TYPE_EMPTY;
    stmt->statement.assignment = NULL;
    stmt->line_no = line_no;
    return stmt;
}

ast_Statement_t *ast_Statement_break(int line_no)
{
    ast_Statement_t *stmt = (ast_Statement_t*) malloc(sizeof(ast_Statement_t));
    if (!stmt) io_errndie("ast_Statement_break:" ERR_MSG_MALLOCFAIL);
    stmt->type = STATEMENT_TYPE_BREAK;
    stmt->statement.assignment = NULL;
    stmt->line_no = line_no;
    return stmt;
}

ast_Statement_t *ast_Statement_continue(int line_no)
{
    ast_Statement_t *stmt = (ast_Statement_t*) malloc(sizeof(ast_Statement_t));
    if (!stmt) io_errndie("ast_Statement_continue:" ERR_MSG_MALLOCFAIL);
    stmt->type = STATEMENT_TYPE_CONTINUE;
    stmt->statement.assignment = NULL;
    stmt->line_no = line_no;
    return stmt;
}

ast_Statement_t *ast_Statement_return(ast_Expression_t *expression, int line_no)
{
    ast_Statement_t *stmt = (ast_Statement_t*) malloc(sizeof(ast_Statement_t));
    if (!stmt) io_errndie("ast_Statement_return:" ERR_MSG_MALLOCFAIL);
    stmt->type = STATEMENT_TYPE_RETURN;
    stmt->statement.expression = expression;
    stmt->line_no = line_no;
    return stmt;
}

ast_Statement_t *ast_Statement_Assignment(ast_Assignment_t *assignment, int line_no)
{
    ast_Statement_t *stmt = (ast_Statement_t*) malloc(sizeof(ast_Statement_t));
    if (!stmt) io_errndie("ast_Statement_Assignment:" ERR_MSG_MALLOCFAIL);
    stmt->type = STATEMENT_TYPE_ASSIGNMENT;
    stmt->statement.assignment = assignment;
    stmt->line_no = line_no;
    return stmt;
}

ast_Statement_t *ast_Statement_CompoundSt(ast_CompoundSt_t *compound, int line_no)
{
    ast_Statement_t *stmt = (ast_Statement_t*) malloc(sizeof(ast_Statement_t));
    if (!stmt) io_errndie("ast_Statement_CompoundSt:" ERR_MSG_MALLOCFAIL);
    stmt->type = STATEMENT_TYPE_COMPOUND;
    stmt->statement.compound_statement = compound;
    stmt->line_no = line_no;
    return stmt;
}

ast_Assignment_t *ast_Assignment_create(ast_Identifier_t *identifier, ast_Expression_t *expression, bool is_const, bool is_weak)
{
    ast_Assignment_t *assign = (ast_Assignment_t*) malloc(sizeof(ast_Assignment_t));
    if (!assign) io_errndie("ast_Assignment_create:" ERR_MSG_MALLOCFAIL);
    assign->lhs = identifier;
    assign->rhs = expression;
    assign->type = ASSIGNMENT_TYPE_CREATE;
    assign->is_const = is_const;
    assign->is_weak = is_weak;
    return assign;
}

ast_Assignment_t *ast_Assignment_tovoid(ast_Expression_t *expression)
{
    ast_Assignment_t *assign = (ast_Assignment_t*) malloc(sizeof(ast_Assignment_t));
    if (!assign) io_errndie("ast_Assignment_tovoid:" ERR_MSG_MALLOCFAIL);
    assign->lhs = NULL;
    assign->rhs = expression;
    assign->type = ASSIGNMENT_TYPE_TOVOID;
    return assign;
}

ast_CompoundSt_t *ast_CompoundSt_IfBlock(ast_IfBlock_t *block)
{
    ast_CompoundSt_t *compound = (ast_CompoundSt_t*) malloc(sizeof(ast_CompoundSt_t));
    if (!compound) io_errndie("ast_CompoundSt_IfBlock:" ERR_MSG_MALLOCFAIL);
    compound->type = COMPOUNDST_TYPE_IF;
    compound->compound_statement.if_block = block;
    return compound;
}

ast_CompoundSt_t *ast_CompoundSt_WhileBlock(ast_WhileBlock_t *block)
{
    ast_CompoundSt_t *compound = (ast_CompoundSt_t*) malloc(sizeof(ast_CompoundSt_t));
    if (!compound) io_errndie("ast_CompoundSt_WhileBlock:" ERR_MSG_MALLOCFAIL);
    compound->type = COMPOUNDST_TYPE_WHILE;
    compound->compound_statement.while_block = block;
    return compound;
}

ast_CompoundSt_t *ast_CompoundSt_ForBlock(ast_ForBlock_t *block)
{
    ast_CompoundSt_t *compound = (ast_CompoundSt_t*) malloc(sizeof(ast_CompoundSt_t));
    if (!compound) io_errndie("ast_CompoundSt_ForBlock:" ERR_MSG_MALLOCFAIL);
    compound->type = COMPOUNDST_TYPE_FOR;
    compound->compound_statement.for_block = block;
    return compound;
}

ast_CompoundSt_t *ast_CompoundSt_Block(ast_Block_t *block)
{
    ast_CompoundSt_t *compound = (ast_CompoundSt_t*) malloc(sizeof(ast_CompoundSt_t));
    if (!compound) io_errndie("ast_CompoundSt_Block:" ERR_MSG_MALLOCFAIL);
    compound->type = COMPOUNDST_TYPE_BLOCK;
    compound->compound_statement.block = block;
    return compound;
}

ast_IfBlock_t *ast_IfBlock(ast_Condition_t *condition, ast_Statements_t *if_st, ast_ElseBlock_t *else_block)
{
    ast_IfBlock_t *if_block = (ast_IfBlock_t*) malloc(sizeof(ast_IfBlock_t));
    if (!if_block) io_errndie("ast_IfBlock:" ERR_MSG_MALLOCFAIL);
    if_block->condition = condition;
    if_block->if_st = if_st;
    if_block->else_block = else_block;
    return if_block;
}

ast_ElseBlock_t *ast_ElseBlock(ast_Condition_t *condition, ast_Statements_t *else_if_st, ast_ElseBlock_t *else_block)
{
    ast_ElseBlock_t *block = (ast_ElseBlock_t*) malloc(sizeof(ast_ElseBlock_t));
    if (!block) io_errndie("ast_ElseBlock:" ERR_MSG_MALLOCFAIL);
    block->condition = condition;
    block->else_if_st = else_if_st;
    block->else_block = else_block;
    return block;
}

ast_WhileBlock_t *ast_WhileBlock(ast_Condition_t *condition, ast_Statements_t *while_st)
{
    ast_WhileBlock_t *while_block = (ast_WhileBlock_t*) malloc(sizeof(ast_WhileBlock_t));
    if (!while_block) io_errndie("ast_WhileBlock:" ERR_MSG_MALLOCFAIL);
    while_block->condition = condition;
    while_block->statements = while_st;
    return while_block;
}

ast_ForBlock_t *ast_ForBlock(ast_Identifier_t *val, ast_Expression_t *start, ast_Expression_t *end, ast_Expression_t *by, ast_Statements_t *for_st)
{
    ast_ForBlock_t *for_block = (ast_ForBlock_t*) malloc(sizeof(ast_ForBlock_t));
    if (!for_block) io_errndie("ast_ForBlock:" ERR_MSG_MALLOCFAIL);
    for_block->idx = NULL;
    for_block->val = val;
    for_block->it.range.start = start;
    for_block->it.range.end = end;
    for_block->it.range.by = by;
    for_block->statements = for_st;
    for_block->type = FORBLOCK_TYPE_RANGE;
    return for_block;
}

ast_ForBlock_t *ast_ForBlock_iterate(ast_Identifier_t *idx, ast_Identifier_t *val, ast_Expression_t *iterable, ast_Statements_t *for_st)
{
    ast_ForBlock_t *for_block = (ast_ForBlock_t*) malloc(sizeof(ast_ForBlock_t));
    if (!for_block) io_errndie("ast_ForBlock_iterate:" ERR_MSG_MALLOCFAIL);
    for_block->idx = idx;
    for_block->val = val;
    for_block->it.iterable = iterable;
    for_block->statements = for_st;
    for_block->type = FORBLOCK_TYPE_LIST;
    return for_block;
}

ast_Block_t *ast_Block(ast_Statements_t *statements)
{
    ast_Block_t *block = (ast_Block_t*) malloc(sizeof(ast_Block_t));
    if (!block) io_errndie("ast_Block:" ERR_MSG_MALLOCFAIL);
    block->statements = statements;
    return block;
}

#define AST_EXPRESSION_ISOPERAND(expr_) ({             \
    ast_Expression_t *expr = expr_;                    \
    expr && expr->op == TOKOP_NOP                      \
         && ( expr->lhs_type == EXPR_TYPE_LITERAL      \
           || expr->lhs_type == EXPR_TYPE_IDENTIFIER ) \
         && expr->rhs_type == EXPR_TYPE_NULL           \
         && expr->condition_type == EXPR_TYPE_NULL;    \
})

ast_Expression_t *ast_Expression(ast_Operator_t op, ast_Expression_t *lhs, ast_Expression_t *rhs, ast_Expression_t *condition)
{
    ast_Expression_t *expression = (ast_Expression_t*) malloc(sizeof(ast_Expression_t));
    if (!expression) io_errndie("ast_Expression:" ERR_MSG_MALLOCFAIL);
    expression->op = op;

    if (AST_EXPRESSION_ISOPERAND(lhs)) {
        expression->lhs_type = lhs->lhs_type;
        expression->lhs = lhs->lhs;
        lhs->lhs.expr = NULL;
        lhs->lhs_type = EXPR_TYPE_NULL;
        ast_Expression_destroy(&lhs);
    } else {
        expression->lhs_type = lhs ? EXPR_TYPE_EXPRESSION : EXPR_TYPE_NULL;
        expression->lhs.expr = lhs;
    }

    if (AST_EXPRESSION_ISOPERAND(rhs)) {
        expression->rhs_type = rhs->lhs_type;
        expression->rhs = rhs->lhs;
        rhs->lhs.expr = NULL;
        rhs->lhs_type = EXPR_TYPE_NULL;
        ast_Expression_destroy(&rhs);
    } else {
        expression->rhs_type = rhs ? EXPR_TYPE_EXPRESSION : EXPR_TYPE_NULL;
        expression->rhs.expr = rhs;
    }

    if (AST_EXPRESSION_ISOPERAND(condition)) {
        expression->condition_type = condition->lhs_type;
        expression->condition = condition->lhs;
        condition->lhs.expr = NULL;
        condition->lhs_type = EXPR_TYPE_NULL;
        ast_Expression_destroy(&condition);
    } else {
        expression->condition_type = condition ? EXPR_TYPE_EXPRESSION : EXPR_TYPE_NULL;
        expression->condition.expr = condition;
    }

    return expression;
}

ast_Expression_t *ast_Expression_Literal(ast_Literal_t *literal)
{
    ast_Expression_t *expression = (ast_Expression_t*) malloc(sizeof(ast_Expression_t));
    if (!expression) io_errndie("ast_Expression_Literal:" ERR_MSG_MALLOCFAIL);
    expression->op = TOKOP_NOP;
    expression->lhs_type = EXPR_TYPE_LITERAL;
    expression->lhs.literal = literal;
    expression->rhs_type = EXPR_TYPE_NULL;
    expression->rhs.expr = NULL;
    expression->condition_type = EXPR_TYPE_NULL;
    expression->condition.expr = NULL;
    return expression;
}

ast_Expression_t *ast_Expression_Identifier(ast_Identifier_t *identifier)
{
    ast_Expression_t *expression = (ast_Expression_t*) malloc(sizeof(ast_Expression_t));
    if (!expression) io_errndie("ast_Expression_Identifier:" ERR_MSG_MALLOCFAIL);
    expression->op = TOKOP_NOP;
    expression->lhs_type = EXPR_TYPE_IDENTIFIER;
    expression->lhs.variable = identifier;
    expression->rhs_type = EXPR_TYPE_NULL;
    expression->rhs.expr = NULL;
    expression->condition_type = EXPR_TYPE_NULL;
    expression->condition.expr = NULL;
    return expression;
}

ast_Expression_t *ast_Expression_CommaSepList(ast_CommaSepList_t *comma_list)
{
    ast_Expression_t *expression = (ast_Expression_t*) malloc(sizeof(ast_Expression_t));
    if (!expression) io_errndie("ast_Expression_CommaSepList:" ERR_MSG_MALLOCFAIL);
    expression->op = TOKOP_NOP;
    expression->lhs_type = EXPR_TYPE_LITERAL;
    expression->lhs.literal = ast_Literal_lst(comma_list);
    expression->rhs_type = EXPR_TYPE_NULL;
    expression->rhs.expr = NULL;
    expression->condition_type = EXPR_TYPE_NULL;
    expression->condition.expr = NULL;
    return expression;
}

ast_FnArgsList_t *ast_FnArgsList(ast_FnArgsList_t *args_list, ast_Identifier_t *identifier)
{
    ast_FnArgsList_t *fn_args_list = (ast_FnArgsList_t*) malloc(sizeof(ast_FnArgsList_t));
    if (!fn_args_list) io_errndie("ast_FnArgsList:" ERR_MSG_MALLOCFAIL);
    fn_args_list->args_list = args_list;
    fn_args_list->identifier = identifier;
    return fn_args_list;
}

ast_CommaSepList_t *ast_CommaSepList(ast_CommaSepList_t *comma_list, ast_Expression_t *expression)
{
    ast_CommaSepList_t *comma_sep_list = (ast_CommaSepList_t*) malloc(sizeof(ast_CommaSepList_t));
    if (!comma_sep_list) io_errndie("ast_CommaSepList:" ERR_MSG_MALLOCFAIL);
    comma_sep_list->comma_list = comma_list;
    comma_sep_list->expression = expression;
    return comma_sep_list;
}

ast_AssociativeList_t *ast_AssociativeList(ast_AssociativeList_t *assoc_list, ast_Literal_t *key, ast_Expression_t *value)
{
    ast_AssociativeList_t *associative_list = (ast_AssociativeList_t*) malloc(sizeof(ast_AssociativeList_t));
    if (!associative_list) io_errndie("ast_AssociativeList:" ERR_MSG_MALLOCFAIL);
    associative_list->assoc_list = assoc_list;
    associative_list->key = key;
    associative_list->value = value;
    return associative_list;
}

ast_Literal_t *ast_Literal_bul(bool literal)
{
    ast_Literal_t *ast_literal = (ast_Literal_t*) malloc(sizeof(ast_Literal_t));
    if (!ast_literal) io_errndie("ast_Literal_bul:" ERR_MSG_MALLOCFAIL);
    ast_literal->type = DATA_TYPE_BUL;
    ast_literal->data.bul = literal;
    return ast_literal;
}

ast_Literal_t *ast_Literal_chr(char literal)
{
    ast_Literal_t *ast_literal = (ast_Literal_t*) malloc(sizeof(ast_Literal_t));
    if (!ast_literal) io_errndie("ast_Literal_chr:" ERR_MSG_MALLOCFAIL);
    ast_literal->type = DATA_TYPE_CHR;
    ast_literal->data.chr = literal;
    return ast_literal;
}

ast_Literal_t *ast_Literal_f64(double literal)
{
    ast_Literal_t *ast_literal = (ast_Literal_t*) malloc(sizeof(ast_Literal_t));
    if (!ast_literal) io_errndie("ast_Literal_f64:" ERR_MSG_MALLOCFAIL);
    ast_literal->type = DATA_TYPE_F64;
    ast_literal->data.f64 = literal;
    return ast_literal;
}

ast_Literal_t *ast_Literal_i64(int64_t literal)
{
    ast_Literal_t *ast_literal = (ast_Literal_t*) malloc(sizeof(ast_Literal_t));
    if (!ast_literal) io_errndie("ast_Literal_i64:" ERR_MSG_MALLOCFAIL);
    ast_literal->type = DATA_TYPE_I64;
    ast_literal->data.i64 = literal;
    return ast_literal;
}

ast_Literal_t *ast_Literal_str(char *literal)
{
    ast_Literal_t *ast_literal = (ast_Literal_t*) malloc(sizeof(ast_Literal_t));
    if (!ast_literal) io_errndie("ast_Literal_str:" ERR_MSG_MALLOCFAIL);
    ast_literal->type = DATA_TYPE_STR;
    ast_literal->data.str = literal;
    return ast_literal;
}

ast_Literal_t *ast_Literal_interp_str(char *literal)
{
    ast_Literal_t *ast_literal = (ast_Literal_t*) malloc(sizeof(ast_Literal_t));
    if (!ast_literal) io_errndie("ast_Literal_interp_str:" ERR_MSG_MALLOCFAIL);
    ast_literal->type = DATA_TYPE_INTERP_STR;
    ast_literal->data.str = literal;
    return ast_literal;
}

ast_Literal_t *ast_Literal_lst(ast_CommaSepList_t *literal)
{
    ast_Literal_t *ast_literal = (ast_Literal_t*) malloc(sizeof(ast_Literal_t));
    if (!ast_literal) io_errndie("ast_Literal_lst:" ERR_MSG_MALLOCFAIL);
    ast_literal->type = DATA_TYPE_LST;
    ast_literal->data.lst = literal;
    return ast_literal;
}

ast_Literal_t *ast_Literal_map(ast_AssociativeList_t *literal)
{
    ast_Literal_t *ast_literal = (ast_Literal_t*) malloc(sizeof(ast_Literal_t));
    if (!ast_literal) io_errndie("ast_Literal_map:" ERR_MSG_MALLOCFAIL);
    ast_literal->type = DATA_TYPE_MAP;
    ast_literal->data.mp = literal;
    return ast_literal;
}

ast_Identifier_t *ast_Identifier(char *identifier_name)
{
    return (ast_Identifier_t*) identifier_name;
}

#else
    #warning re-inclusion of module 'ast/nodes/constructors.c.h'
#endif
