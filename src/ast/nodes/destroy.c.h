#ifndef AST_NODES_DESTROY_C_H
#define AST_NODES_DESTROY_C_H

#include <stdlib.h>
#include "ast/nodes.h"

void AST_Statements_free(AST_Statements_t **ptr)
{
    if (!ptr) return;
    AST_Statements_t *statements = *ptr;
    if (!statements) return;
    AST_Statements_t *node = statements;
    while (node) {
        AST_Statement_free(&node->statement);
        AST_Statements_t *tmp = node;
        node = node->statements;
        free(tmp);
    }
    *ptr = NULL;
}

void AST_Statement_free(AST_Statement_t **ptr)
{
    if (!ptr) return;
    AST_Statement_t *statement = *ptr;
    if (!statement) return;
    switch (statement->type) {
        case STATEMENT_TYPE_EMPTY:
            break;
        case STATEMENT_TYPE_RETURN:
            AST_Expression_free(&statement->statement.expression);
            break;
        case STATEMENT_TYPE_ASSIGNMENT:
            AST_Assignment_free(&statement->statement.assignment);
            break;
        case STATEMENT_TYPE_COMPOUND:
            AST_CompoundSt_free(&statement->statement.compound_statement);
            break;
    }
    free(statement);
    *ptr = NULL;
}

void AST_Assignment_free(AST_Assignment_t **ptr)
{
    if (!ptr) return;
    AST_Assignment_t *assignment = *ptr;
    if (!assignment) return;
    AST_Identifier_free(&assignment->lhs);
    AST_Expression_free(&assignment->rhs);
    free(assignment);
    *ptr = NULL;
}

void AST_CompoundSt_free(AST_CompoundSt_t **ptr)
{
    if (!ptr) return;
    AST_CompoundSt_t *compound_statement = *ptr;
    if (!compound_statement) return;
    switch (compound_statement->type) {
        case COMPOUNDST_TYPE_IF:
            AST_IfBlock_free(&compound_statement->compound_statement.if_block);
            break;
        case COMPOUNDST_TYPE_WHILE:
            AST_WhileBlock_free(&compound_statement->compound_statement.while_block);
            break;
        case COMPOUNDST_TYPE_FOR:
            AST_ForBlock_free(&compound_statement->compound_statement.for_block);
            break;
        case COMPOUNDST_TYPE_BLOCK:
            AST_Block_free(&compound_statement->compound_statement.block);
            break;
    }
    free(compound_statement);
    *ptr = NULL;
}

void AST_IfBlock_free(AST_IfBlock_t **ptr)
{
    if (!ptr) return;
    AST_IfBlock_t *if_block = *ptr;
    if (!if_block) return;
    AST_Expression_free(&if_block->condition);
    AST_Statements_free(&if_block->if_st);
    AST_ElseIfBlock_free(&if_block->else_if_block);
    AST_Statements_free(&if_block->else_st);
    free(if_block);
    *ptr = NULL;
}

void AST_ElseIfBlock_free(AST_ElseIfBlock_t **ptr)
{
    if (!ptr) return;
    AST_ElseIfBlock_t *else_if_block = *ptr;
    if (!else_if_block) return;
    AST_ElseIfBlock_free(&else_if_block->else_if_block);
    AST_ElseIfSt_free(&else_if_block->else_if_st);
    free(else_if_block);
    *ptr = NULL;
}

void AST_ElseIfSt_free(AST_ElseIfSt_t **ptr)
{
    if (!ptr) return;
    AST_ElseIfSt_t *else_if_st = *ptr;
    if (!else_if_st) return;
    AST_Expression_free(&else_if_st->condition);
    AST_Statements_free(&else_if_st->statements);
    free(else_if_st);
    *ptr = NULL;
}

void AST_WhileBlock_free(AST_WhileBlock_t **ptr)
{
    if (!ptr) return;
    AST_WhileBlock_t *while_block = *ptr;
    if (!while_block) return;
    AST_Expression_free(&while_block->condition);
    AST_Statements_free(&while_block->statements);
    free(while_block);
    *ptr = NULL;
}

void AST_ForBlock_free(AST_ForBlock_t **ptr)
{
    if (!ptr) return;
    AST_ForBlock_t *for_block = *ptr;
    if (!for_block) return;
    AST_Identifier_free(&for_block->iter);
    switch (for_block->type) {
        case FORBLOCK_TYPE_RANGE:
            AST_Expression_free(&for_block->iterable.range.start);
            AST_Expression_free(&for_block->iterable.range.end);
            AST_Expression_free(&for_block->iterable.range.by);
            break;
        case FORBLOCK_TYPE_LIST:
            AST_Expression_free(&for_block->iterable.lst);
            break;
    }
    AST_Statements_free(&for_block->statements);
    free(for_block);
    *ptr = NULL;
}

void AST_Block_free(AST_Block_t **ptr)
{
    if (!ptr) return;
    AST_Block_t *block = *ptr;
    if (!block) return;
    AST_Statements_free(&block->statements);
    free(block);
    *ptr = NULL;
}

void AST_Expression_free(AST_Expression_t **ptr)
{
    if (!ptr) return;
    AST_Expression_t *expression = *ptr;
    if (!expression) return;
    switch (expression->lhs_type) {
        case EXPR_TYPE_EXPRESSION:
            AST_Expression_free(&expression->lhs.expr);
            break;
        case EXPR_TYPE_LITERAL:
            AST_Literal_free(&expression->lhs.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            AST_Identifier_free(&expression->lhs.variable);
            break;
        case EXPR_TYPE_LIST:
            AST_CommaSepList_free(&expression->lhs.lst);
            break;
        case EXPR_TYPE_NULL:
            break;
    }
    switch (expression->rhs_type) {
        case EXPR_TYPE_EXPRESSION:
            AST_Expression_free(&expression->rhs.expr);
            break;
        case EXPR_TYPE_LITERAL:
            AST_Literal_free(&expression->rhs.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            AST_Identifier_free(&expression->rhs.variable);
            break;
        case EXPR_TYPE_LIST:
            AST_CommaSepList_free(&expression->rhs.lst);
            break;
        case EXPR_TYPE_NULL:
            break;
    }
    switch (expression->condition_type) {
        case EXPR_TYPE_EXPRESSION:
            AST_Expression_free(&expression->condition.expr);
            break;
        case EXPR_TYPE_LITERAL:
            AST_Literal_free(&expression->condition.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            AST_Identifier_free(&expression->condition.variable);
            break;
        case EXPR_TYPE_LIST:
            AST_CommaSepList_free(&expression->condition.lst);
            break;
        case EXPR_TYPE_NULL:
            break;
    }
    free(expression);
    *ptr = NULL;
}

void AST_CommaSepList_free(AST_CommaSepList_t **ptr)
{
    if (!ptr) return;
    AST_CommaSepList_t *comma_list = *ptr;
    if (!comma_list) return;
    AST_CommaSepList_free(&comma_list->comma_list);
    AST_Expression_free(&comma_list->expression);
    free(comma_list);
    *ptr = NULL;
}

void AST_Literal_free(AST_Literal_t **ptr)
{
    if (!ptr) return;
    AST_Literal_t *literal = *ptr;
    if (!literal) return;
    switch (literal->type) {
        case DATA_TYPE_STR:
        case DATA_TYPE_INTERP_STR:
            free(literal->data.str);
            break;
        case DATA_TYPE_LST:
            AST_CommaSepList_free(&literal->data.lst);
            break;
        default: break;
    }
    free(literal);
    *ptr = NULL;
}

void AST_Identifier_free(AST_Identifier_t **ptr)
{
    if (!ptr) return;
    AST_Identifier_t *identifier = *ptr;
    if (!identifier) return;
    if (!identifier->identifier_name) return;
    free(identifier->identifier_name);
    identifier->identifier_name = NULL;
    free(identifier);
    *ptr = NULL;
}

#endif
