#ifndef AST_NODES_DESTRUCTORS_C_H
#define AST_NODES_DESTRUCTORS_C_H

#include <stdlib.h>
#include "ast/nodes.h"

void AST_Statements_destroy(AST_Statements_t **ptr)
{
    if (!ptr) return;
    AST_Statements_t *statements = *ptr;
    if (!statements) return;
    AST_Statements_t *node = statements;
    while (node) {
        AST_Statement_destroy(&node->statement);
        AST_Statements_t *tmp = node;
        node = node->statements;
        free(tmp);
    }
    *ptr = NULL;
}

void AST_Statement_destroy(AST_Statement_t **ptr)
{
    if (!ptr) return;
    AST_Statement_t *statement = *ptr;
    if (!statement) return;
    switch (statement->type) {
        case STATEMENT_TYPE_EMPTY:
        case STATEMENT_TYPE_BREAK:
        case STATEMENT_TYPE_CONTINUE:
            break;
        case STATEMENT_TYPE_RETURN:
            AST_Expression_destroy(&statement->statement.expression);
            break;
        case STATEMENT_TYPE_ASSIGNMENT:
            AST_Assignment_destroy(&statement->statement.assignment);
            break;
        case STATEMENT_TYPE_COMPOUND:
            AST_CompoundSt_destroy(&statement->statement.compound_statement);
            break;
    }
    free(statement);
    *ptr = NULL;
}

void AST_Assignment_destroy(AST_Assignment_t **ptr)
{
    if (!ptr) return;
    AST_Assignment_t *assignment = *ptr;
    if (!assignment) return;
    AST_Identifier_destroy(&assignment->lhs);
    AST_Expression_destroy(&assignment->rhs);
    free(assignment);
    *ptr = NULL;
}

void AST_CompoundSt_destroy(AST_CompoundSt_t **ptr)
{
    if (!ptr) return;
    AST_CompoundSt_t *compound_statement = *ptr;
    if (!compound_statement) return;
    switch (compound_statement->type) {
        case COMPOUNDST_TYPE_IF:
            AST_IfBlock_destroy(&compound_statement->compound_statement.if_block);
            break;
        case COMPOUNDST_TYPE_WHILE:
            AST_WhileBlock_destroy(&compound_statement->compound_statement.while_block);
            break;
        case COMPOUNDST_TYPE_FOR:
            AST_ForBlock_destroy(&compound_statement->compound_statement.for_block);
            break;
        case COMPOUNDST_TYPE_BLOCK:
            AST_Block_destroy(&compound_statement->compound_statement.block);
            break;
    }
    free(compound_statement);
    *ptr = NULL;
}

void AST_IfBlock_destroy(AST_IfBlock_t **ptr)
{
    if (!ptr) return;
    AST_IfBlock_t *if_block = *ptr;
    if (!if_block) return;
    AST_Expression_destroy(&if_block->condition);
    AST_Statements_destroy(&if_block->if_st);
    AST_ElseBlock_destroy(&if_block->else_block);
    free(if_block);
    *ptr = NULL;
}

void AST_ElseBlock_destroy(AST_ElseBlock_t **ptr)
{
    if (!ptr) return;
    AST_ElseBlock_t *else_block = *ptr;
    if (!else_block) return;
    AST_Expression_destroy(&else_block->condition);
    AST_Statements_destroy(&else_block->else_if_st);
    AST_ElseBlock_destroy(&else_block->else_block);
    free(else_block);
    *ptr = NULL;
}

void AST_WhileBlock_destroy(AST_WhileBlock_t **ptr)
{
    if (!ptr) return;
    AST_WhileBlock_t *while_block = *ptr;
    if (!while_block) return;
    AST_Expression_destroy(&while_block->condition);
    AST_Statements_destroy(&while_block->statements);
    free(while_block);
    *ptr = NULL;
}

void AST_ForBlock_destroy(AST_ForBlock_t **ptr)
{
    if (!ptr) return;
    AST_ForBlock_t *for_block = *ptr;
    if (!for_block) return;
    AST_Identifier_destroy(&for_block->idx);
    AST_Identifier_destroy(&for_block->val);
    switch (for_block->type) {
        case FORBLOCK_TYPE_RANGE:
            AST_Expression_destroy(&for_block->it.range.start);
            AST_Expression_destroy(&for_block->it.range.end);
            AST_Expression_destroy(&for_block->it.range.by);
            break;
        case FORBLOCK_TYPE_LIST:
            AST_Expression_destroy(&for_block->it.iterable);
            break;
    }
    AST_Statements_destroy(&for_block->statements);
    free(for_block);
    *ptr = NULL;
}

void AST_Block_destroy(AST_Block_t **ptr)
{
    if (!ptr) return;
    AST_Block_t *block = *ptr;
    if (!block) return;
    AST_Statements_destroy(&block->statements);
    free(block);
    *ptr = NULL;
}

void AST_Expression_destroy(AST_Expression_t **ptr)
{
    if (!ptr) return;
    AST_Expression_t *expression = *ptr;
    if (!expression) return;
    switch (expression->lhs_type) {
        case EXPR_TYPE_EXPRESSION:
            AST_Expression_destroy(&expression->lhs.expr);
            break;
        case EXPR_TYPE_LITERAL:
            AST_Literal_destroy(&expression->lhs.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            AST_Identifier_destroy(&expression->lhs.variable);
            break;
        case EXPR_TYPE_NULL:
            break;
    }
    switch (expression->rhs_type) {
        case EXPR_TYPE_EXPRESSION:
            AST_Expression_destroy(&expression->rhs.expr);
            break;
        case EXPR_TYPE_LITERAL:
            AST_Literal_destroy(&expression->rhs.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            AST_Identifier_destroy(&expression->rhs.variable);
            break;
        case EXPR_TYPE_NULL:
            break;
    }
    switch (expression->condition_type) {
        case EXPR_TYPE_EXPRESSION:
            AST_Expression_destroy(&expression->condition.expr);
            break;
        case EXPR_TYPE_LITERAL:
            AST_Literal_destroy(&expression->condition.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            AST_Identifier_destroy(&expression->condition.variable);
            break;
        case EXPR_TYPE_NULL:
            break;
    }
    free(expression);
    *ptr = NULL;
}

void AST_CommaSepList_destroy(AST_CommaSepList_t **ptr)
{
    if (!ptr) return;
    AST_CommaSepList_t *comma_list = *ptr;
    while (comma_list) {
        AST_Expression_destroy(&comma_list->expression);
        AST_CommaSepList_t *rm = comma_list;
        comma_list = comma_list->comma_list;
        free(rm);
    }
    *ptr = NULL;
}

void AST_AssociativeList_destroy(AST_AssociativeList_t **ptr)
{
    if (!ptr) return;
    AST_AssociativeList_t *assoc_list = *ptr;
    while (assoc_list) {
        AST_Literal_destroy(&assoc_list->key);
        AST_Expression_destroy(&assoc_list->value);
        AST_AssociativeList_t *rm = assoc_list;
        assoc_list = assoc_list->assoc_list;
        free(rm);
    }
    *ptr = NULL;
}

void AST_Literal_destroy(AST_Literal_t **ptr)
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
            AST_CommaSepList_destroy(&literal->data.lst);
            break;
        case DATA_TYPE_MAP:
            AST_AssociativeList_destroy(&literal->data.mp);
            break;
        default: break;
    }
    free(literal);
    *ptr = NULL;
}

void AST_Identifier_destroy(AST_Identifier_t **ptr)
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
