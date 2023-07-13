#ifndef AST_AST2JSON_C_H
#define AST_AST2JSON_C_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

#include "ast/nodes.h"
#include "ast/to_json.h"

FILE *AST2JSON_outfile = NULL;

/* Helper function to escape special characters in a string */
char* AST2JSON_escape_string(const char* input)
{
    if (!input) input = "null";
    size_t input_len = strlen(input);
    size_t output_len = 0;
    for (size_t i = 0; i < input_len; ++i) {
        if (input[i] == '"' || input[i] == '\\' || input[i] == '\n') {
            /* Add escape character */
            output_len += 2;
        } else {
            ++output_len;
        }
    }

    char* output = (char*) malloc(output_len + 1);
    size_t j = 0;
    for (size_t i = 0; i < input_len; ++i) {
        if (input[i] == '"' || input[i] == '\\' || input[i] == '\n') {
            output[j++] = '\\';  /* Add escape character */
        }
        output[j++] = input[i];
    }
    output[j] = '\0';
    return output;
}

/* Function to convert AST_Statements_t to JSON */
void AST2JSON_Statements(const AST_Statements_t *statements)
{
    if (!statements) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"statements\": [");
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

/* Function to convert AST_Statement_t to JSON */
void AST2JSON_Statement(const AST_Statement_t *statement)
{
    if (!statement) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"statement\": ");
    if (statement->type == STATEMENT_TYPE_ASSIGNMENT) {
        AST2JSON_Assignment(statement->statement.assignment);
    } else if (statement->type == STATEMENT_TYPE_COMPOUND) {
        AST2JSON_CompoundSt(statement->statement.compound_statement);
    } else {
        fprintf(AST2JSON_outfile, "null");
    }
    fprintf(AST2JSON_outfile, ", \"type\": %d", statement->type);
    fprintf(AST2JSON_outfile, ", \"line_no\": %d", statement->line_no);
    fprintf(AST2JSON_outfile, "}");
}

/* Function to convert AST_Assignment_t to JSON */
void AST2JSON_Assignment(const AST_Assignment_t *assignment)
{
    if (!assignment) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"lhs\": ");
    AST2JSON_Identifier(assignment->lhs);
    fprintf(AST2JSON_outfile, ", \"rhs\": ");
    AST2JSON_Expression(assignment->rhs);
    fprintf(AST2JSON_outfile, "}");
}

/* Function to convert AST_CompoundSt_t to JSON */
void AST2JSON_CompoundSt(const AST_CompoundSt_t *compound_statement)
{
    if (!compound_statement) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"compound_statement\": ");
    if (compound_statement->type == COMPOUNDST_TYPE_IF) {
        AST2JSON_IfBlock(compound_statement->compound_statement.if_block);
    } else if (compound_statement->type == COMPOUNDST_TYPE_WHILE) {
        AST2JSON_WhileBlock(compound_statement->compound_statement.while_block);
    } else if (compound_statement->type == COMPOUNDST_TYPE_FOR) {
        AST2JSON_ForBlock(compound_statement->compound_statement.for_block);
    } else if (compound_statement->type == COMPOUNDST_TYPE_BLOCK) {
        AST2JSON_Block(compound_statement->compound_statement.block);
    } else {
        fprintf(AST2JSON_outfile, "null");
    }
    fprintf(AST2JSON_outfile, ", \"type\": %d", compound_statement->type);
    fprintf(AST2JSON_outfile, "}");
}

/* Function to convert AST_IfBlock_t to JSON */
void AST2JSON_IfBlock(const AST_IfBlock_t *if_block)
{
    if (!if_block) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"condition\": ");
    AST2JSON_Expression(if_block->condition);
    fprintf(AST2JSON_outfile, ", \"if_st\": ");
    AST2JSON_Statements(if_block->if_st);
    fprintf(AST2JSON_outfile, ", \"else_if_block\": ");
    AST2JSON_ElseIfBlock(if_block->else_if_block);
    fprintf(AST2JSON_outfile, ", \"else_st\": ");
    AST2JSON_Statements(if_block->else_st);
    fprintf(AST2JSON_outfile, "}");
}

/* Function to convert AST_ElseIfBlock_t to JSON */
void AST2JSON_ElseIfBlock(const AST_ElseIfBlock_t *else_if_block)
{
    if (!else_if_block) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"else_if_block\": ");
    AST2JSON_ElseIfBlock(else_if_block->else_if_block);
    fprintf(AST2JSON_outfile, ", \"else_if_st\": ");
    AST2JSON_ElseIfSt(else_if_block->else_if_st);
    fprintf(AST2JSON_outfile, "}");
}

/* Function to convert AST_ElseIfSt_t to JSON */
void AST2JSON_ElseIfSt(const AST_ElseIfSt_t *else_if_st)
{
    if (!else_if_st) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"condition\": ");
    AST2JSON_Expression(else_if_st->condition);
    fprintf(AST2JSON_outfile, ", \"statements\": ");
    AST2JSON_Statements(else_if_st->statements);
    fprintf(AST2JSON_outfile, "}");
}

/* Function to convert AST_WhileBlock_t to JSON */
void AST2JSON_WhileBlock(const AST_WhileBlock_t *while_block)
{
    if (!while_block) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"condition\": ");
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
    fprintf(AST2JSON_outfile, "\"iter\": ");
    AST2JSON_Identifier(for_block->iter);
    fprintf(AST2JSON_outfile, ", \"iterable\": ");
    if (for_block->type == FORBLOCK_TYPE_RANGE) {
        fprintf(AST2JSON_outfile, "{");
        fprintf(AST2JSON_outfile, "\"start\": ");
        AST2JSON_Operand(for_block->iterable.range.start);
        fprintf(AST2JSON_outfile, ", \"end\": ");
        AST2JSON_Operand(for_block->iterable.range.end);
        fprintf(AST2JSON_outfile, ", \"by\": ");
        AST2JSON_Operand(for_block->iterable.range.by);
        fprintf(AST2JSON_outfile, "}");
        fprintf(AST2JSON_outfile, ", \"type\": \"range\"");
    } else if (for_block->type == FORBLOCK_TYPE_LIST) {
        AST2JSON_Operand(for_block->iterable.oprnd);
        fprintf(AST2JSON_outfile, ", \"type\": \"list\"");
    } else {
        fprintf(AST2JSON_outfile, "null");
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
    fprintf(AST2JSON_outfile, "\"statements\": ");
    AST2JSON_Statements(block->statements);
    fprintf(AST2JSON_outfile, "}");
}

/* Function to convert AST_Expression_t to JSON */
void AST2JSON_Expression(const AST_Expression_t *expression)
{
    if (!expression) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"op\": \"%s\"", lex_get_symbol(expression->op));
    fprintf(AST2JSON_outfile, ", \"lhs\": ");
    if (expression->lhs_type == EXPR_TYPE_EXPRESSION) {
        AST2JSON_Expression(expression->lhs.expr);
    } else if (expression->lhs_type == EXPR_TYPE_OPERAND) {
        AST2JSON_Operand(expression->lhs.oprnd);
    } else if (expression->lhs_type == EXPR_TYPE_LIST) {
        AST2JSON_CommaSepList(expression->lhs.lst);
    } else {
        fprintf(AST2JSON_outfile, "null");
    }
    fprintf(AST2JSON_outfile, ", \"lhs_type\": %d", expression->lhs_type);
    fprintf(AST2JSON_outfile, ", \"rhs\": ");
    if (expression->rhs_type == EXPR_TYPE_EXPRESSION) {
        AST2JSON_Expression(expression->rhs.expr);
    } else if (expression->rhs_type == EXPR_TYPE_OPERAND) {
        AST2JSON_Operand(expression->rhs.oprnd);
    } else if (expression->rhs_type == EXPR_TYPE_LIST) {
        AST2JSON_CommaSepList(expression->rhs.lst);
    } else {
        fprintf(AST2JSON_outfile, "null");
    }
    fprintf(AST2JSON_outfile, ", \"rhs_type\": %d", expression->rhs_type);
    fprintf(AST2JSON_outfile, ", \"condition\": ");
    if (expression->condition_type == EXPR_TYPE_EXPRESSION) {
        AST2JSON_Expression(expression->condition.expr);
    } else if (expression->condition_type == EXPR_TYPE_OPERAND) {
        AST2JSON_Operand(expression->condition.oprnd);
    } else if (expression->condition_type == EXPR_TYPE_LIST) {
        AST2JSON_CommaSepList(expression->condition.lst);
    } else {
        fprintf(AST2JSON_outfile, "null");
    }
    fprintf(AST2JSON_outfile, ", \"condition_type\": %d", expression->condition_type);
    fprintf(AST2JSON_outfile, "}");
}

/* Function to convert AST_CommaSepList_t to JSON */
void AST2JSON_CommaSepList(const AST_CommaSepList_t *comma_list)
{
    if (!comma_list) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"comma_list\": [");
    const AST_CommaSepList_t *lst = comma_list;
    AST2JSON_Expression(lst->expression);
    lst = lst->comma_list;
    while (lst) {
        fprintf(AST2JSON_outfile, ", ");
        AST2JSON_Expression(comma_list->expression);
        lst = lst->comma_list;
    }
    fprintf(AST2JSON_outfile, "]");
    fprintf(AST2JSON_outfile, "}");
}

/* Function to convert AST_Operand_t to JSON */
void AST2JSON_Operand(const AST_Operand_t *operand)
{
    if (!operand) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"operand\": ");
    if (operand->type == OPERAND_TYPE_LITERAL) {
        AST2JSON_Literal(operand->operand.literal);
        fprintf(AST2JSON_outfile, ", \"type\": \"literal\"");
    } else if (operand->type == OPERAND_TYPE_IDENTIFIER) {
        AST2JSON_Identifier(operand->operand.variable);
        fprintf(AST2JSON_outfile, ", \"type\": \"identifier\"");
    } else {
        fprintf(AST2JSON_outfile, "null");
    }
    fprintf(AST2JSON_outfile, "}");
}

/* Function to convert AST_Literal_t to JSON */
void AST2JSON_Literal(const AST_Literal_t *literal)
{
    if (!literal) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"data\": ");
    if (literal->type == DATA_TYPE_BUL) {
        fprintf(AST2JSON_outfile, "%s", literal->data.bul ? "true" : "false");
        fprintf(AST2JSON_outfile, ", \"type\": \"bool\"");
    } else if (literal->type == DATA_TYPE_CHR) {
        fprintf(AST2JSON_outfile, "\"%c\"", literal->data.chr);
        fprintf(AST2JSON_outfile, ", \"type\": \"char\"");
    } else if (literal->type == DATA_TYPE_I64) {
        fprintf(AST2JSON_outfile, "%" PRId64, literal->data.i64);
        fprintf(AST2JSON_outfile, ", \"type\": \"i64\"");
    } else if (literal->type == DATA_TYPE_F64) {
        fprintf(AST2JSON_outfile, "%f", literal->data.f64);
        fprintf(AST2JSON_outfile, ", \"type\": \"f64\"");
    } else if (literal->type == DATA_TYPE_STR || literal->type == DATA_TYPE_INTERP_STR) {
        char* escaped_str = AST2JSON_escape_string(literal->data.str);
        fprintf(AST2JSON_outfile, "\"%s\"", escaped_str);
        fprintf(AST2JSON_outfile, ", \"type\": \"str\"");
        free(escaped_str);
    } else if (literal->type == DATA_TYPE_LST) {
        AST2JSON_CommaSepList(literal->data.lst);
        fprintf(AST2JSON_outfile, ", \"type\": \"list\"");
    } else if (literal->type == DATA_TYPE_ANY) {
        fprintf(AST2JSON_outfile, "null");  /* You need to handle the conversion of "void* any" if needed */
        fprintf(AST2JSON_outfile, ", \"type\": \"any\"");
    } else {
        fprintf(AST2JSON_outfile, "null");
    }
    fprintf(AST2JSON_outfile, "}");
}

/* Function to convert AST_Identifier_t to JSON */
void AST2JSON_Identifier(const AST_Identifier_t *identifier)
{
    if (!identifier) {
        fprintf(AST2JSON_outfile, "null");
        return;
    }

    fprintf(AST2JSON_outfile, "{");
    fprintf(AST2JSON_outfile, "\"identifier_name\": \"%s\"", identifier->identifier_name);
    fprintf(AST2JSON_outfile, "}");
}

void AST2JSON_ProcedureMap()
{
    AST_ProcedureMapKeyList_t lst = AST_ProcedureMap_KeyList_get();
    for (int i = 0; i < lst.module_cnt; ++i) {
        fprintf(AST2JSON_outfile, "{");
        fprintf(AST2JSON_outfile, "\"module\": \"%s\"", lst.module[i].module_name->identifier_name);
        fprintf(AST2JSON_outfile, ", \"procedure\": ");
        for (int j = 0; j < lst.module[i].proc_cnt; ++j) {
            AST_Identifier_t *key = lst.module[i].lst[j];
            const AST_Statements_t *st = AST_ProcedureMap_get(lst.module[i].module_name, key);
            fprintf(AST2JSON_outfile, "{");
            fprintf(AST2JSON_outfile, "\"procedure_name\": \"%s\"", key->identifier_name);
            fprintf(AST2JSON_outfile, ", \"code\": ");
            AST2JSON_Statements(st);
            fprintf(AST2JSON_outfile, "}");
        }
        fprintf(AST2JSON_outfile, "}");
    }
    AST_ProcedureMap_KeyList_free(&lst);
}

void AST2JSON_convert(FILE *f)
{
    AST2JSON_outfile = f;
    AST2JSON_ProcedureMap();
}

#else
    #warning re-inclusion of module 'ast/to_json.c.h'
#endif
