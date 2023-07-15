#ifndef AST_AST2JSON_C_H
#define AST_AST2JSON_C_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

#include "io.h"
#include "ast/nodes.h"
#include "ast/to_json.h"

FILE *AST2JSON_outfile = NULL;

/* helper function to escape special characters in a string */
char *AST2JSON_escape_string(const char *str)
{
    if (!str) return NULL;
    size_t len = strlen(str);
    char *escaped = (char*) malloc((4 * len +1) * sizeof(char));
    if (!escaped) parse_throw("memory allocation failed");
    char *ptr = escaped;
    while (*str != '\0') {
        switch (*str) {
            case '\a':
                *ptr++ = '\\';
                *ptr++ = 'a';
                break;
            case '\b':
                *ptr++ = '\\';
                *ptr++ = 'b';
                break;
            case '\f':
                *ptr++ = '\\';
                *ptr++ = 'f';
                break;
            case '\n':
                *ptr++ = '\\';
                *ptr++ = 'n';
                break;
            case '\r':
                *ptr++ = '\\';
                *ptr++ = 'r';
                break;
            case '\t':
                *ptr++ = '\\';
                *ptr++ = 't';
                break;
            case '\v':
                *ptr++ = '\\';
                *ptr++ = 'v';
                break;
            default:
                if (*str < 32 || *str > 126) {
                    /* unprintable character, escape using \xXX notation */
                    sprintf(
                        ptr, "\\x%02X",
                        (unsigned char) *str);
                    ptr += 4;
                } else
                    /* copy printable character as is */
                    *ptr++ = *str;
                break;
        }
        ++str;
    }
    *ptr = '\0';
    return escaped;
}

/* function to convert AST_Statements_t to JSON */
void AST2JSON_Statements(const AST_Statements_t *statements)
{
    if (!statements) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"node\": \"statements\"");
    fprintf(AST2JSON_outfile, ", \"statements\": [");
    const AST_Statements_t *st = statements;
    AST2JSON_Statement(st->statement);
    st = st->statements;
    while (st) {
        fprintf(AST2JSON_outfile, ", ");
        AST2JSON_Statement(st->statement);
        st = st->statements;
    }
    fprintf(AST2JSON_outfile, "]");
    fprintf(AST2JSON_outfile, "}");
}

/* function to convert AST_Statement_t to JSON */
void AST2JSON_Statement(const AST_Statement_t *statement)
{
    if (!statement) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"node\": \"statement\"");
    fprintf(AST2JSON_outfile, ", \"line_no\": %d", statement->line_no);

    switch (statement->type) {
        case STATEMENT_TYPE_ASSIGNMENT:
            fprintf(AST2JSON_outfile, ", \"type\": \"STATEMENT_TYPE_ASSIGNMENT\"");
            fprintf(AST2JSON_outfile, ", \"statement\": ");
            AST2JSON_Assignment(statement->statement.assignment);
            break;
        case STATEMENT_TYPE_COMPOUND:
            fprintf(AST2JSON_outfile, ", \"type\": \"STATEMENT_TYPE_COMPOUND\"");
            fprintf(AST2JSON_outfile, ", \"statement\": ");
            AST2JSON_CompoundSt(statement->statement.compound_statement);
            break;
        case STATEMENT_TYPE_EMPTY:
            fprintf(AST2JSON_outfile, ", \"type\": \"STATEMENT_TYPE_EMPTY\"");
            fprintf(AST2JSON_outfile, ", \"statement\": null");
            break;
    }
    fprintf(AST2JSON_outfile, "}");
}

/* function to convert AST_Assignment_t to JSON */
void AST2JSON_Assignment(const AST_Assignment_t *assignment)
{
    if (!assignment) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"node\": \"assignment\"");
    fprintf(AST2JSON_outfile, ", \"lhs\": ");
    AST2JSON_Identifier(assignment->lhs);
    fprintf(AST2JSON_outfile, ", \"rhs\": ");
    AST2JSON_Expression(assignment->rhs);
    fprintf(AST2JSON_outfile, "}");
}

/* function to convert AST_CompoundSt_t to JSON */
void AST2JSON_CompoundSt(const AST_CompoundSt_t *compound_statement)
{
    if (!compound_statement) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    switch (compound_statement->type) {
        case COMPOUNDST_TYPE_IF:
            AST2JSON_IfBlock(compound_statement->compound_statement.if_block);
            break;
        case COMPOUNDST_TYPE_WHILE:
            AST2JSON_WhileBlock(compound_statement->compound_statement.while_block);
            break;
        case COMPOUNDST_TYPE_FOR:
            AST2JSON_ForBlock(compound_statement->compound_statement.for_block);
            break;
        case COMPOUNDST_TYPE_BLOCK:
            AST2JSON_Block(compound_statement->compound_statement.block);
            break;
    }
}

/* function to convert AST_IfBlock_t to JSON */
void AST2JSON_IfBlock(const AST_IfBlock_t *if_block)
{
    if (!if_block) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"node\": \"if_block\"");
    fprintf(AST2JSON_outfile, ", \"condition\": ");
    AST2JSON_Expression(if_block->condition);
    fprintf(AST2JSON_outfile, ", \"if_st\": ");
    AST2JSON_Statements(if_block->if_st);
    fprintf(AST2JSON_outfile, ", \"else_if_block\": ");
    AST2JSON_ElseIfBlock(if_block->else_if_block);
    fprintf(AST2JSON_outfile, ", \"else_st\": ");
    AST2JSON_Statements(if_block->else_st);
    fprintf(AST2JSON_outfile, "}");
}

/* function to convert AST_ElseIfBlock_t to JSON */
void AST2JSON_ElseIfBlock(const AST_ElseIfBlock_t *else_if_block)
{
    if (!else_if_block) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"node\": \"else_if_block\"");
    fprintf(AST2JSON_outfile, ", \"else_if_block\": ");
    AST2JSON_ElseIfBlock(else_if_block->else_if_block);
    fprintf(AST2JSON_outfile, ", \"else_if_st\": ");
    AST2JSON_ElseIfSt(else_if_block->else_if_st);
    fprintf(AST2JSON_outfile, "}");
}

/* function to convert AST_ElseIfSt_t to JSON */
void AST2JSON_ElseIfSt(const AST_ElseIfSt_t *else_if_st)
{
    if (!else_if_st) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"node\": \"else_if_st\"");
    fprintf(AST2JSON_outfile, ", \"condition\": ");
    AST2JSON_Expression(else_if_st->condition);
    fprintf(AST2JSON_outfile, ", \"statements\": ");
    AST2JSON_Statements(else_if_st->statements);
    fprintf(AST2JSON_outfile, "}");
}

/* function to convert AST_WhileBlock_t to JSON */
void AST2JSON_WhileBlock(const AST_WhileBlock_t *while_block)
{
    if (!while_block) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"node\": \"while_block\"");
    fprintf(AST2JSON_outfile, ", \"condition\": ");
    AST2JSON_Expression(while_block->condition);
    fprintf(AST2JSON_outfile, ", \"statements\": ");
    AST2JSON_Statements(while_block->statements);
    fprintf(AST2JSON_outfile, "}");
}

/* Function to convert AST_ForBlock_t to JSON */
void AST2JSON_ForBlock(const AST_ForBlock_t *for_block)
{
    if (!for_block) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"node\": \"for_block\"");

    switch (for_block->type) {
        case FORBLOCK_TYPE_RANGE: {
            fprintf(AST2JSON_outfile, ", \"type\": \"FORBLOCK_TYPE_RANGE\"");
            fprintf(AST2JSON_outfile, ", \"iter\": ");
            AST2JSON_Identifier(for_block->iter);
            fprintf(AST2JSON_outfile, ", \"iterable\": {");
            fprintf(AST2JSON_outfile, "\"node\": \"iterable\"");
            fprintf(AST2JSON_outfile, ", \"start\": ");
            AST2JSON_Operand(for_block->iterable.range.start);
            fprintf(AST2JSON_outfile, ", \"end\": ");
            AST2JSON_Operand(for_block->iterable.range.end);
            fprintf(AST2JSON_outfile, ", \"by\": ");
            AST2JSON_Operand(for_block->iterable.range.by);
            fprintf(AST2JSON_outfile, "}");
            break;
        }
        case FORBLOCK_TYPE_LIST:
            fprintf(AST2JSON_outfile, ", \"type\": \"FORBLOCK_TYPE_LIST\"");
            fprintf(AST2JSON_outfile, ", \"iter\": ");
            AST2JSON_Identifier(for_block->iter);
            fprintf(AST2JSON_outfile, ", \"iterable\": ");
            AST2JSON_Operand(for_block->iterable.oprnd);
            break;
    }

    fprintf(AST2JSON_outfile, ", \"statements\": ");
    AST2JSON_Statements(for_block->statements);
    fprintf(AST2JSON_outfile, "}");
}

/* Function to convert AST_Block_t to JSON */
void AST2JSON_Block(const AST_Block_t *block)
{
    if (!block) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"node\": \"block\"");
    fprintf(AST2JSON_outfile, ", \"statements\": ");
    AST2JSON_Statements(block->statements);
    fprintf(AST2JSON_outfile, "}");
}

/* function to convert AST_Expression_t to JSON */
void AST2JSON_Expression(const AST_Expression_t *expression)
{
    if (!expression) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"node\": \"expression\"");
    fprintf(AST2JSON_outfile, ", \"op\": \"%s\"", lex_get_symbol(expression->op));

    switch (expression->lhs_type) {
        case EXPR_TYPE_EXPRESSION:
            fprintf(AST2JSON_outfile, ", \"lhs_type\": \"EXPR_TYPE_EXPRESSION\"");
            fprintf(AST2JSON_outfile, ", \"lhs\": ");
            AST2JSON_Expression(expression->lhs.expr);
            break;
        case EXPR_TYPE_OPERAND:
            fprintf(AST2JSON_outfile, ", \"lhs_type\": \"EXPR_TYPE_OPERAND\"");
            fprintf(AST2JSON_outfile, ", \"lhs\": ");
            AST2JSON_Operand(expression->lhs.oprnd);
            break;
        case EXPR_TYPE_LIST:
            fprintf(AST2JSON_outfile, ", \"lhs_type\": \"EXPR_TYPE_LIST\"");
            fprintf(AST2JSON_outfile, ", \"lhs\": ");
            AST2JSON_CommaSepList(expression->lhs.lst);
            break;
        case EXPR_TYPE_NULL:
            fprintf(AST2JSON_outfile, ", \"lhs_type\": \"EXPR_TYPE_NULL\"");
            fprintf(AST2JSON_outfile, ", \"lhs\": null");
            break;
    }

    switch (expression->rhs_type) {
        case EXPR_TYPE_EXPRESSION:
            fprintf(AST2JSON_outfile, ", \"rhs_type\": \"EXPR_TYPE_EXPRESSION\"");
            fprintf(AST2JSON_outfile, ", \"rhs\": ");
            AST2JSON_Expression(expression->rhs.expr);
            break;
        case EXPR_TYPE_OPERAND:
            fprintf(AST2JSON_outfile, ", \"rhs_type\": \"EXPR_TYPE_OPERAND\"");
            fprintf(AST2JSON_outfile, ", \"rhs\": ");
            AST2JSON_Operand(expression->rhs.oprnd);
            break;
        case EXPR_TYPE_LIST:
            fprintf(AST2JSON_outfile, ", \"rhs_type\": \"EXPR_TYPE_LIST\"");
            fprintf(AST2JSON_outfile, ", \"rhs\": ");
            AST2JSON_CommaSepList(expression->rhs.lst);
            break;
        case EXPR_TYPE_NULL:
            fprintf(AST2JSON_outfile, ", \"rhs_type\": \"EXPR_TYPE_NULL\"");
            fprintf(AST2JSON_outfile, ", \"rhs\": null");
            break;
    }

    switch (expression->condition_type) {
        case EXPR_TYPE_EXPRESSION:
            fprintf(AST2JSON_outfile, ", \"condition_type\": \"EXPR_TYPE_EXPRESSION\"");
            fprintf(AST2JSON_outfile, ", \"condition\": ");
            AST2JSON_Expression(expression->condition.expr);
            break;
        case EXPR_TYPE_OPERAND:
            fprintf(AST2JSON_outfile, ", \"condition_type\": \"EXPR_TYPE_OPERAND\"");
            fprintf(AST2JSON_outfile, ", \"condition\": ");
            AST2JSON_Operand(expression->condition.oprnd);
            break;
        case EXPR_TYPE_LIST:
            fprintf(AST2JSON_outfile, ", \"condition_type\": \"EXPR_TYPE_LIST\"");
            fprintf(AST2JSON_outfile, ", \"condition\": ");
            AST2JSON_CommaSepList(expression->condition.lst);
            break;
        case EXPR_TYPE_NULL:
            fprintf(AST2JSON_outfile, ", \"condition_type\": \"EXPR_TYPE_NULL\"");
            fprintf(AST2JSON_outfile, ", \"condition\": null");
            break;
    }

    fprintf(AST2JSON_outfile, "}");
}

/* function to convert AST_CommaSepList_t to JSON */
void AST2JSON_CommaSepList(const AST_CommaSepList_t *comma_list)
{
    if (!comma_list) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"node\": \"comma_list\"");

    const AST_CommaSepList_t *lst = comma_list;
    fprintf(AST2JSON_outfile, ", \"comma_list\": [");
    AST2JSON_Expression(lst->expression);
    lst = lst->comma_list;

    while (lst) {
        fprintf(AST2JSON_outfile, ", ");
        AST2JSON_Expression(lst->expression);
        lst = lst->comma_list;
    }

    fprintf(AST2JSON_outfile, "]");
    fprintf(AST2JSON_outfile, "}");
}

/* function to convert AST_Operand_t to JSON */
void AST2JSON_Operand(const AST_Operand_t *operand)
{
    if (!operand) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"node\": \"operand\"");

    switch (operand->type) {
        case OPERAND_TYPE_LITERAL:
            fprintf(AST2JSON_outfile, ", \"type\": \"OPERAND_TYPE_LITERAL\"");
            fprintf(AST2JSON_outfile, ", \"operand\": ");
            AST2JSON_Literal(operand->operand.literal);
            break;
        case OPERAND_TYPE_IDENTIFIER:
            fprintf(AST2JSON_outfile, ", \"type\": \"OPERAND_TYPE_IDENTIFIER\"");
            fprintf(AST2JSON_outfile, ", \"operand\": ");
            AST2JSON_Identifier(operand->operand.variable);
            break;
        default:
            fprintf(AST2JSON_outfile, ", \"operand\": null");
            break;
    }

    fprintf(AST2JSON_outfile, "}");
}

/* function to convert AST_Literal_t to JSON */
void AST2JSON_Literal(const AST_Literal_t *literal)
{
    if (!literal) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"node\": \"literal\"");

    switch (literal->type) {
        case DATA_TYPE_BUL:
            fprintf(AST2JSON_outfile, ", \"type\": \"DATA_TYPE_BUL\"");
            fprintf(AST2JSON_outfile, ", \"data\": ");
            fprintf(AST2JSON_outfile, "%s", literal->data.bul ? "true" : "false");
            break;
        case DATA_TYPE_CHR: {
            char chr[2] = { literal->data.chr, '\0' };
            char *escaped_chr = AST2JSON_escape_string(chr);
            fprintf(AST2JSON_outfile, ", \"type\": \"DATA_TYPE_CHR\"");
            fprintf(AST2JSON_outfile, ", \"data\": ");
            if (escaped_chr) {
                fprintf(AST2JSON_outfile, "\"%s\"", escaped_chr);
                free(escaped_chr);
            } else {
                fprintf(AST2JSON_outfile, "null");
            }
            break;
        }
        case DATA_TYPE_I64:
            fprintf(AST2JSON_outfile, ", \"type\": \"DATA_TYPE_I64\"");
            fprintf(AST2JSON_outfile, ", \"data\": ");
            fprintf(AST2JSON_outfile, "%" PRId64, literal->data.i64);
            break;
        case DATA_TYPE_F64:
            fprintf(AST2JSON_outfile, ", \"type\": \"DATA_TYPE_F64\"");
            fprintf(AST2JSON_outfile, ", \"data\": ");
            fprintf(AST2JSON_outfile, "%f", literal->data.f64);
            break;
        case DATA_TYPE_STR:
        case DATA_TYPE_INTERP_STR: {
            fprintf(AST2JSON_outfile, ", \"type\": \"DATA_TYPE_STR\"");
            fprintf(AST2JSON_outfile, ", \"data\": ");
            char *escaped_str = AST2JSON_escape_string(literal->data.str);
            if (escaped_str) {
                fprintf(AST2JSON_outfile, "\"%s\"", escaped_str);
                free(escaped_str);
            } else {
                fprintf(AST2JSON_outfile, "null");
            }
            break;
        }
        case DATA_TYPE_LST:
            fprintf(AST2JSON_outfile, ", \"type\": \"DATA_TYPE_LST\"");
            fprintf(AST2JSON_outfile, ", \"data\": ");
            AST2JSON_CommaSepList(literal->data.lst);
            break;
        case DATA_TYPE_ANY:
            fprintf(AST2JSON_outfile, ", \"type\": \"DATA_TYPE_ANY\"");
            fprintf(AST2JSON_outfile, ", \"data\": null");
            break;
    }

    fprintf(AST2JSON_outfile, "}");
}

/* function to convert AST_Identifier_t to JSON */
void AST2JSON_Identifier(const AST_Identifier_t *identifier)
{
    if (!identifier) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"node\": \"identifier\"");
    fprintf(AST2JSON_outfile, ", \"identifier_name\": \"%s\"", identifier->identifier_name);
    fprintf(AST2JSON_outfile, "}");
}

void AST2JSON_ProcedureMap()
{
    AST_ProcedureMapKeyList_t lst = AST_ProcedureMap_KeyList_get();
    /* open root */
    fprintf(AST2JSON_outfile, "{");
    /* node name */
    fprintf(AST2JSON_outfile, "\"node\": \"root\"");
    for (int i = 0; i < lst.module_cnt; ++i) {
        /* open map of the module name to procedures */
        fprintf(AST2JSON_outfile, ", \"%s\": {", lst.module[i].module_name->identifier_name);
        /* node name */
        fprintf(AST2JSON_outfile, "\"node\": \"module\"");
        for (int j = 0; j < lst.module[i].proc_cnt; ++j) {
            AST_Identifier_t *key = lst.module[i].lst[j];
            const AST_Statements_t *st = AST_ProcedureMap_get(lst.module[i].module_name, key);
            /* open a procedure node, map it with proc name */
            fprintf(AST2JSON_outfile, ", \"%s\": {", key->identifier_name);
            fprintf(AST2JSON_outfile, "\"node\": \"procedure\"");
            fprintf(AST2JSON_outfile, ", \"statements\": ");
            AST2JSON_Statements(st);
            /* close procedure */
            fprintf(AST2JSON_outfile, "}");
        }
        fprintf(AST2JSON_outfile, "}");
    }
    /* close root */
    fprintf(AST2JSON_outfile, "}");
    AST_ProcedureMap_KeyList_free(&lst);
}

void AST2JSON_convert(const char *filepath)
{
    if (!strcmp(filepath, "-")) AST2JSON_outfile = stdout;
    else AST2JSON_outfile = fopen(filepath, "wb");
    AST2JSON_ProcedureMap();
    if (AST2JSON_outfile != stdout)
        fclose(AST2JSON_outfile);
}

#else
    #warning re-inclusion of module 'ast/to_json.c.h'
#endif
