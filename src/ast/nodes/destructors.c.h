#ifndef ast_NODES_DESTRUCTORS_C_H
#define ast_NODES_DESTRUCTORS_C_H

#include <stdlib.h>
#include "ast/nodes.h"

void ast_Statements_destroy(ast_Statements_t **ptr)
{
    if (!ptr) return;
    ast_Statements_t *statements = *ptr;
    if (!statements) return;
    ast_Statements_t *node = statements;
    while (node) {
        ast_Statement_destroy(&node->statement);
        ast_Statements_t *tmp = node;
        node = node->statements;
        free(tmp);
    }
    *ptr = NULL;
}

void ast_Statement_destroy(ast_Statement_t **ptr)
{
    if (!ptr) return;
    ast_Statement_t *statement = *ptr;
    if (!statement) return;
    switch (statement->type) {
        case STATEMENT_TYPE_EMPTY:
        case STATEMENT_TYPE_BREAK:
        case STATEMENT_TYPE_CONTINUE:
            break;
        case STATEMENT_TYPE_RETURN:
            ast_Expression_destroy(&statement->statement.expression);
            break;
        case STATEMENT_TYPE_ASSIGNMENT:
            ast_Assignment_destroy(&statement->statement.assignment);
            break;
        case STATEMENT_TYPE_COMPOUND:
            ast_CompoundSt_destroy(&statement->statement.compound_statement);
            break;
    }
    free(statement);
    *ptr = NULL;
}

void ast_Assignment_destroy(ast_Assignment_t **ptr)
{
    if (!ptr) return;
    ast_Assignment_t *assignment = *ptr;
    if (!assignment) return;
    ast_Identifier_destroy(&assignment->lhs);
    ast_Expression_destroy(&assignment->rhs);
    free(assignment);
    *ptr = NULL;
}

void ast_CompoundSt_destroy(ast_CompoundSt_t **ptr)
{
    if (!ptr) return;
    ast_CompoundSt_t *compound_statement = *ptr;
    if (!compound_statement) return;
    switch (compound_statement->type) {
        case COMPOUNDST_TYPE_IF:
            ast_IfBlock_destroy(&compound_statement->compound_statement.if_block);
            break;
        case COMPOUNDST_TYPE_WHILE:
            ast_WhileBlock_destroy(&compound_statement->compound_statement.while_block);
            break;
        case COMPOUNDST_TYPE_FOR:
            ast_ForBlock_destroy(&compound_statement->compound_statement.for_block);
            break;
        case COMPOUNDST_TYPE_BLOCK:
            ast_Block_destroy(&compound_statement->compound_statement.block);
            break;
    }
    free(compound_statement);
    *ptr = NULL;
}

void ast_IfBlock_destroy(ast_IfBlock_t **ptr)
{
    if (!ptr) return;
    ast_IfBlock_t *if_block = *ptr;
    if (!if_block) return;
    ast_Expression_destroy(&if_block->condition);
    ast_Statements_destroy(&if_block->if_st);
    ast_ElseBlock_destroy(&if_block->else_block);
    free(if_block);
    *ptr = NULL;
}

void ast_ElseBlock_destroy(ast_ElseBlock_t **ptr)
{
    if (!ptr) return;
    ast_ElseBlock_t *else_block = *ptr;
    if (!else_block) return;
    ast_Expression_destroy(&else_block->condition);
    ast_Statements_destroy(&else_block->else_if_st);
    ast_ElseBlock_destroy(&else_block->else_block);
    free(else_block);
    *ptr = NULL;
}

void ast_WhileBlock_destroy(ast_WhileBlock_t **ptr)
{
    if (!ptr) return;
    ast_WhileBlock_t *while_block = *ptr;
    if (!while_block) return;
    ast_Expression_destroy(&while_block->condition);
    ast_Statements_destroy(&while_block->statements);
    free(while_block);
    *ptr = NULL;
}

void ast_ForBlock_destroy(ast_ForBlock_t **ptr)
{
    if (!ptr) return;
    ast_ForBlock_t *for_block = *ptr;
    if (!for_block) return;
    ast_Identifier_destroy(&for_block->idx);
    ast_Identifier_destroy(&for_block->val);
    switch (for_block->type) {
        case FORBLOCK_TYPE_RANGE:
            ast_Expression_destroy(&for_block->it.range.start);
            ast_Expression_destroy(&for_block->it.range.end);
            ast_Expression_destroy(&for_block->it.range.by);
            break;
        case FORBLOCK_TYPE_LIST:
            ast_Expression_destroy(&for_block->it.iterable);
            break;
    }
    ast_Statements_destroy(&for_block->statements);
    free(for_block);
    *ptr = NULL;
}

void ast_Block_destroy(ast_Block_t **ptr)
{
    if (!ptr) return;
    ast_Block_t *block = *ptr;
    if (!block) return;
    ast_Statements_destroy(&block->statements);
    free(block);
    *ptr = NULL;
}

void ast_Expression_destroy(ast_Expression_t **ptr)
{
    if (!ptr) return;
    ast_Expression_t *expression = *ptr;
    if (!expression) return;
    switch (expression->lhs_type) {
        case EXPR_TYPE_EXPRESSION:
            ast_Expression_destroy(&expression->lhs.expr);
            break;
        case EXPR_TYPE_LITERAL:
            ast_Literal_destroy(&expression->lhs.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            ast_Identifier_destroy(&expression->lhs.variable);
            break;
        case EXPR_TYPE_NULL:
            break;
    }
    switch (expression->rhs_type) {
        case EXPR_TYPE_EXPRESSION:
            ast_Expression_destroy(&expression->rhs.expr);
            break;
        case EXPR_TYPE_LITERAL:
            ast_Literal_destroy(&expression->rhs.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            ast_Identifier_destroy(&expression->rhs.variable);
            break;
        case EXPR_TYPE_NULL:
            break;
    }
    switch (expression->condition_type) {
        case EXPR_TYPE_EXPRESSION:
            ast_Expression_destroy(&expression->condition.expr);
            break;
        case EXPR_TYPE_LITERAL:
            ast_Literal_destroy(&expression->condition.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            ast_Identifier_destroy(&expression->condition.variable);
            break;
        case EXPR_TYPE_NULL:
            break;
    }
    free(expression);
    *ptr = NULL;
}

void ast_CommaSepList_destroy(ast_CommaSepList_t **ptr)
{
    if (!ptr) return;
    ast_CommaSepList_t *comma_list = *ptr;
    while (comma_list) {
        ast_Expression_destroy(&comma_list->expression);
        ast_CommaSepList_t *rm = comma_list;
        comma_list = comma_list->comma_list;
        free(rm);
    }
    *ptr = NULL;
}

void ast_AssociativeList_destroy(ast_AssociativeList_t **ptr)
{
    if (!ptr) return;
    ast_AssociativeList_t *assoc_list = *ptr;
    while (assoc_list) {
        ast_Literal_destroy(&assoc_list->key);
        ast_Expression_destroy(&assoc_list->value);
        ast_AssociativeList_t *rm = assoc_list;
        assoc_list = assoc_list->assoc_list;
        free(rm);
    }
    *ptr = NULL;
}

void ast_Literal_destroy(ast_Literal_t **ptr)
{
    if (!ptr) return;
    ast_Literal_t *literal = *ptr;
    if (!literal) return;
    switch (literal->type) {
        case DATA_TYPE_STR:
        case DATA_TYPE_INTERP_STR:
            free(literal->data.str);
            break;
        case DATA_TYPE_LST:
            ast_CommaSepList_destroy(&literal->data.lst);
            break;
        case DATA_TYPE_MAP:
            ast_AssociativeList_destroy(&literal->data.mp);
            break;
        default: break;
    }
    free(literal);
    *ptr = NULL;
}

void ast_Identifier_destroy(ast_Identifier_t **ptr)
{
    if (!ptr) return;
    ast_Identifier_t *identifier = *ptr;
    if (!identifier) return;
    if (!identifier->identifier_name) return;
    free(identifier->identifier_name);
    identifier->identifier_name = NULL;
    free(identifier);
    *ptr = NULL;
}

#endif
