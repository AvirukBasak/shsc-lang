#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast/api.h"
#include "ast2json.h"
#include "errcodes.h"
#include "io.h"
#include "lexer.h"

void ast2json_printf(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void ast2json_open_obj(void);
void ast2json_close_obj(void);
void ast2json_open_list(void);
void ast2json_close_list(void);
void ast2json_put_comma(void);

FILE *ast2json_outfile = NULL;
int ast2json_indent_depth = 0;
bool ast2json_format = false;

#define ast2json_INDENT_INCR (2)

void ast2json_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(ast2json_outfile, fmt, args);
    va_end(args);
}

void ast2json_open_obj(void)
{
    if (!ast2json_format) {
        ast2json_printf("{");
        return;
    }
    ast2json_indent_depth += ast2json_INDENT_INCR;
    ast2json_printf("{\n%*s", ast2json_indent_depth, "");
}

void ast2json_close_obj(void)
{
    if (!ast2json_format) {
        ast2json_printf("}");
        return;
    }
    ast2json_indent_depth -= ast2json_INDENT_INCR;
    ast2json_printf("\n%*s}", ast2json_indent_depth, "");
}

void ast2json_open_list(void)
{
    if (!ast2json_format) {
        ast2json_printf("[");
        return;
    }
    ast2json_indent_depth += ast2json_INDENT_INCR;
    ast2json_printf("[\n%*s", ast2json_indent_depth, "");
}

void ast2json_close_list(void)
{
    if (!ast2json_format) {
        ast2json_printf("]");
        return;
    }
    ast2json_indent_depth -= ast2json_INDENT_INCR;
    ast2json_printf("\n%*s]", ast2json_indent_depth, "");
}

void ast2json_put_comma(void)
{
    if (!ast2json_format) {
        ast2json_printf(", ");
        return;
    }
    ast2json_printf(",\n%*s", ast2json_indent_depth, "");
}

/* function to convert ast_Statements_t to JSON */
void ast2json_Statements(const ast_Statements_t *statements)
{
    if (!statements) {
        ast2json_printf("null");
        return;
    }

    ast2json_open_obj();
    ast2json_printf("\"node\": \"statements\"");
    ast2json_put_comma();
    ast2json_printf("\"statements\": ");
    ast2json_open_list();
    const ast_Statements_t *st = statements;
    ast2json_Statement(st->statement);
    st = st->statements;
    while (st) {
        ast2json_put_comma();
        ast2json_Statement(st->statement);
        st = st->statements;
    }
    ast2json_close_list();
    ast2json_close_obj();
}

/* function to convert ast_Statement_t to JSON */
void ast2json_Statement(const ast_Statement_t *statement)
{
    if (!statement) {
        ast2json_printf("null");
        return;
    }

    ast2json_open_obj();
    ast2json_printf("\"node\": \"statement\"");
    ast2json_put_comma();
    ast2json_printf("\"line_no\": %d", statement->line_no);

    switch (statement->type) {
        case STATEMENT_TYPE_RETURN:
            ast2json_put_comma();
            ast2json_printf("\"type\": \"STATEMENT_TYPE_RETURN\"");
            ast2json_put_comma();
            ast2json_printf("\"statement\": ");
            ast2json_Expression(statement->statement.expression);
            break;
        case STATEMENT_TYPE_ASSIGNMENT:
            ast2json_put_comma();
            ast2json_printf("\"type\": \"STATEMENT_TYPE_ASSIGNMENT\"");
            ast2json_put_comma();
            ast2json_printf("\"statement\": ");
            ast2json_Assignment(statement->statement.assignment);
            break;
        case STATEMENT_TYPE_COMPOUND:
            ast2json_put_comma();
            ast2json_printf("\"type\": \"STATEMENT_TYPE_COMPOUND\"");
            ast2json_put_comma();
            ast2json_printf("\"statement\": ");
            ast2json_CompoundSt(statement->statement.compound_statement);
            break;
        case STATEMENT_TYPE_EMPTY:
            ast2json_put_comma();
            ast2json_printf("\"type\": \"STATEMENT_TYPE_EMPTY\"");
            ast2json_put_comma();
            ast2json_printf("\"statement\": null");
            break;
        case STATEMENT_TYPE_BREAK:
            ast2json_put_comma();
            ast2json_printf("\"type\": \"STATEMENT_TYPE_BREAK\"");
            ast2json_put_comma();
            ast2json_printf("\"statement\": null");
            break;
        case STATEMENT_TYPE_CONTINUE:
            ast2json_put_comma();
            ast2json_printf("\"type\": \"STATEMENT_TYPE_CONTINUE\"");
            ast2json_put_comma();
            ast2json_printf("\"statement\": null");
            break;
    }
    ast2json_close_obj();
}

/* function to convert ast_Assignment_t to JSON */
void ast2json_Assignment(const ast_Assignment_t *assignment)
{
    if (!assignment) {
        ast2json_printf("null");
        return;
    }

    ast2json_open_obj();
    ast2json_printf("\"node\": \"assignment\"");
    ast2json_put_comma();
    ast2json_printf("\"lhs\": ");
    ast2json_Identifier(assignment->lhs);
    ast2json_put_comma();
    ast2json_printf("\"rhs\": ");
    ast2json_Expression(assignment->rhs);
    ast2json_close_obj();
}

/* function to convert ast_CompoundSt_t to JSON */
void ast2json_CompoundSt(const ast_CompoundSt_t *compound_statement)
{
    if (!compound_statement) {
        ast2json_printf("null");
        return;
    }

    switch (compound_statement->type) {
        case COMPOUNDST_TYPE_IF:
            ast2json_IfBlock(compound_statement->compound_statement.if_block);
            break;
        case COMPOUNDST_TYPE_WHILE:
            ast2json_WhileBlock(compound_statement->compound_statement.while_block);
            break;
        case COMPOUNDST_TYPE_FOR:
            ast2json_ForBlock(compound_statement->compound_statement.for_block);
            break;
        case COMPOUNDST_TYPE_BLOCK:
            ast2json_Block(compound_statement->compound_statement.block);
            break;
    }
}

/* function to convert ast_IfBlock_t to JSON */
void ast2json_IfBlock(const ast_IfBlock_t *if_block)
{
    if (!if_block) {
        ast2json_printf("null");
        return;
    }

    ast2json_open_obj();
    ast2json_printf("\"node\": \"if_block\"");
    ast2json_put_comma();
    ast2json_printf("\"condition\": ");
    ast2json_Expression(if_block->condition);
    ast2json_put_comma();
    ast2json_printf("\"if_st\": ");
    ast2json_Statements(if_block->if_st);
    ast2json_put_comma();
    ast2json_printf("\"else_block\": ");
    ast2json_ElseBlock(if_block->else_block);
    ast2json_close_obj();
}

/* function to convert ast_ElseIfBlock_t to JSON */
void ast2json_ElseBlock(const ast_ElseBlock_t *else_block)
{
    if (!else_block) {
        ast2json_printf("null");
        return;
    }

    ast2json_open_obj();
    ast2json_printf("\"node\": \"else_block\"");
    ast2json_put_comma();
    ast2json_printf("\"condition\": ");
    ast2json_Expression(else_block->condition);
    ast2json_put_comma();
    ast2json_printf("\"else_if_st\": ");
    ast2json_Statements(else_block->else_if_st);
    ast2json_put_comma();
    ast2json_printf("\"else_block\": ");
    ast2json_ElseBlock(else_block->else_block);
    ast2json_close_obj();
}

/* function to convert ast_WhileBlock_t to JSON */
void ast2json_WhileBlock(const ast_WhileBlock_t *while_block)
{
    if (!while_block) {
        ast2json_printf("null");
        return;
    }

    ast2json_open_obj();
    ast2json_printf("\"node\": \"while_block\"");
    ast2json_put_comma();
    ast2json_printf("\"condition\": ");
    ast2json_Expression(while_block->condition);
    ast2json_put_comma();
    ast2json_printf("\"statements\": ");
    ast2json_Statements(while_block->statements);
    ast2json_close_obj();
}

/* Function to convert ast_ForBlock_t to JSON */
void ast2json_ForBlock(const ast_ForBlock_t *for_block)
{
    if (!for_block) {
        ast2json_printf("null");
        return;
    }

    ast2json_open_obj();
    ast2json_printf("\"node\": \"for_block\"");

    switch (for_block->type) {
        case FORBLOCK_TYPE_RANGE: {
            ast2json_put_comma();
            ast2json_printf("\"type\": \"FORBLOCK_TYPE_RANGE\"");
            ast2json_put_comma();
            ast2json_printf("\"val\": ");
            ast2json_Identifier(for_block->val);
            ast2json_put_comma();
            ast2json_printf("\"it\": ");
            ast2json_open_obj();
            ast2json_printf("\"node\": \"range\"");
            ast2json_put_comma();
            ast2json_printf("\"start\": ");
            ast2json_Expression(for_block->it.range.start);
            ast2json_put_comma();
            ast2json_printf("\"end\": ");
            ast2json_Expression(for_block->it.range.end);
            ast2json_put_comma();
            ast2json_printf("\"by\": ");
            ast2json_Expression(for_block->it.range.by);
            ast2json_close_obj();
            break;
        }
        case FORBLOCK_TYPE_LIST:
            ast2json_put_comma();
            ast2json_printf("\"type\": \"FORBLOCK_TYPE_LIST\"");
            ast2json_put_comma();
            ast2json_printf("\"idx\": ");
            ast2json_Identifier(for_block->idx);
            ast2json_put_comma();
            ast2json_printf("\"val\": ");
            ast2json_Identifier(for_block->val);
            ast2json_put_comma();
            ast2json_printf("\"it\": ");
            ast2json_Expression(for_block->it.iterable);
            break;
    }

    ast2json_put_comma();
    ast2json_printf("\"statements\": ");
    ast2json_Statements(for_block->statements);
    ast2json_close_obj();
}

/* Function to convert ast_Block_t to JSON */
void ast2json_Block(const ast_Block_t *block)
{
    if (!block) {
        ast2json_printf("null");
        return;
    }

    ast2json_open_obj();
    ast2json_printf("\"node\": \"block\"");
    ast2json_put_comma();
    ast2json_printf("\"statements\": ");
    ast2json_Statements(block->statements);
    ast2json_close_obj();
}

/* function to convert ast_Expression_t to JSON */
void ast2json_Expression(const ast_Expression_t *expression)
{
    if (!expression) {
        ast2json_printf("null");
        return;
    }

    ast2json_open_obj();
    ast2json_printf("\"node\": \"expression\"");
    ast2json_put_comma();
    ast2json_printf("\"op\": \"%s\"", lex_Token_getsymbol(expression->op));

    switch (expression->lhs_type) {
        case EXPR_TYPE_EXPRESSION:
            ast2json_put_comma();
            ast2json_printf("\"lhs_type\": \"EXPR_TYPE_EXPRESSION\"");
            ast2json_put_comma();
            ast2json_printf("\"lhs\": ");
            ast2json_Expression(expression->lhs.expr);
            break;
        case EXPR_TYPE_LITERAL:
            ast2json_put_comma();
            ast2json_printf("\"lhs_type\": \"EXPR_TYPE_LITERAL\"");
            ast2json_put_comma();
            ast2json_printf("\"lhs\": ");
            ast2json_Literal(expression->lhs.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            ast2json_put_comma();
            ast2json_printf("\"lhs_type\": \"EXPR_TYPE_IDENTIFIER\"");
            ast2json_put_comma();
            ast2json_printf("\"lhs\": ");
            ast2json_Identifier(expression->lhs.variable);
            break;
        case EXPR_TYPE_NULL:
            ast2json_put_comma();
            ast2json_printf("\"lhs_type\": \"EXPR_TYPE_NULL\"");
            ast2json_put_comma();
            ast2json_printf("\"lhs\": null");
            break;
    }

    switch (expression->rhs_type) {
        case EXPR_TYPE_EXPRESSION:
            ast2json_put_comma();
            ast2json_printf("\"rhs_type\": \"EXPR_TYPE_EXPRESSION\"");
            ast2json_put_comma();
            ast2json_printf("\"rhs\": ");
            ast2json_Expression(expression->rhs.expr);
            break;
        case EXPR_TYPE_LITERAL:
            ast2json_put_comma();
            ast2json_printf("\"rhs_type\": \"EXPR_TYPE_LITERAL\"");
            ast2json_put_comma();
            ast2json_printf("\"rhs\": ");
            ast2json_Literal(expression->rhs.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            ast2json_put_comma();
            ast2json_printf("\"rhs_type\": \"EXPR_TYPE_IDENTIFIER\"");
            ast2json_put_comma();
            ast2json_printf("\"rhs\": ");
            ast2json_Identifier(expression->rhs.variable);
            break;
        case EXPR_TYPE_NULL:
            ast2json_put_comma();
            ast2json_printf("\"rhs_type\": \"EXPR_TYPE_NULL\"");
            ast2json_put_comma();
            ast2json_printf("\"rhs\": null");
            break;
    }

    switch (expression->condition_type) {
        case EXPR_TYPE_EXPRESSION:
            ast2json_put_comma();
            ast2json_printf("\"condition_type\": \"EXPR_TYPE_EXPRESSION\"");
            ast2json_put_comma();
            ast2json_printf("\"condition\": ");
            ast2json_Expression(expression->condition.expr);
            break;
        case EXPR_TYPE_LITERAL:
            ast2json_put_comma();
            ast2json_printf("\"condition_type\": \"EXPR_TYPE_LITERAL\"");
            ast2json_put_comma();
            ast2json_printf("\"condition\": ");
            ast2json_Literal(expression->condition.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            ast2json_put_comma();
            ast2json_printf("\"condition_type\": \"EXPR_TYPE_IDENTIFIER\"");
            ast2json_put_comma();
            ast2json_printf("\"condition\": ");
            ast2json_Identifier(expression->condition.variable);
            break;
        case EXPR_TYPE_NULL:
            ast2json_put_comma();
            ast2json_printf("\"condition_type\": \"EXPR_TYPE_NULL\"");
            ast2json_put_comma();
            ast2json_printf("\"condition\": null");
            break;
    }

    ast2json_close_obj();
}

void ast2json_FnArgsList(const ast_FnArgsList_t *fnargs_list)
{
    if (!fnargs_list) {
        ast2json_printf("null");
        return;
    }

    ast2json_open_obj();
    ast2json_printf("\"node\": \"fnargs_list\"");

    const ast_FnArgsList_t *lst = fnargs_list;
    ast2json_put_comma();
    ast2json_printf("\"fnargs_list\": ");
    ast2json_open_list();
    ast2json_Identifier(lst->identifier);
    lst = lst->args_list;

    while (lst) {
        ast2json_put_comma();
        ast2json_Identifier(lst->identifier);
        lst = lst->args_list;
    }

    ast2json_close_list();
    ast2json_close_obj();
}

/* function to convert ast_CommaSepList_t to JSON */
void ast2json_CommaSepList(const ast_CommaSepList_t *comma_list)
{
    if (!comma_list) {
        ast2json_printf("null");
        return;
    }

    ast2json_open_obj();
    ast2json_printf("\"node\": \"comma_list\"");

    const ast_CommaSepList_t *lst = comma_list;
    ast2json_put_comma();
    ast2json_printf("\"comma_list\": ");
    ast2json_open_list();
    ast2json_Expression(lst->expression);
    lst = lst->comma_list;

    while (lst) {
        ast2json_put_comma();
        ast2json_Expression(lst->expression);
        lst = lst->comma_list;
    }

    ast2json_close_list();
    ast2json_close_obj();
}

void ast2json_AssociativeList(const ast_AssociativeList_t* assoc_list)
{
    if (!assoc_list) {
        ast2json_printf("null");
        return;
    }

    ast2json_open_obj();
    ast2json_printf("\"node\": \"assoc_list\"");

    const ast_AssociativeList_t *mp = assoc_list;
    ast2json_put_comma();
    ast2json_printf("\"assoc_list\": ");
    ast2json_open_list();

    ast2json_open_obj();
    ast2json_printf("\"key\": ");
    ast2json_Literal(mp->key);
    ast2json_put_comma();
    ast2json_printf("\"value\": ");
    ast2json_Expression(mp->value);
    ast2json_close_obj();

    mp = mp->assoc_list;

    while (mp) {
        ast2json_put_comma();
        ast2json_open_obj();
        ast2json_printf("\"key\": ");
        ast2json_Literal(mp->key);
        ast2json_put_comma();
        ast2json_printf("\"value\": ");
        ast2json_Expression(mp->value);
        ast2json_close_obj();
        mp = mp->assoc_list;
    }

    ast2json_close_list();
    ast2json_close_obj();
}

/* function to convert ast_Literal_t to JSON */
void ast2json_Literal(const ast_Literal_t *literal)
{
    if (!literal) {
        ast2json_printf("null");
        return;
    }

    ast2json_open_obj();
    ast2json_printf("\"node\": \"literal\"");

    switch (literal->type) {
        case DATA_TYPE_BUL:
            ast2json_put_comma();
            ast2json_printf("\"type\": \"DATA_TYPE_BUL\"");
            ast2json_put_comma();
            ast2json_printf("\"data\": ");
            ast2json_printf("%s", literal->data.bul ? "true" : "false");
            break;
        case DATA_TYPE_CHR: {
            char chr[2] = { literal->data.chr, '\0' };
            char *escaped_chr = io_full_escape_string(chr);
            ast2json_put_comma();
            ast2json_printf("\"type\": \"DATA_TYPE_CHR\"");
            ast2json_put_comma();
            ast2json_printf("\"data\": ");
            if (escaped_chr) {
                ast2json_printf("\"%s\"", escaped_chr);
                free(escaped_chr);
            } else {
                ast2json_printf("null");
            }
            break;
        }
        case DATA_TYPE_I64:
            ast2json_put_comma();
            ast2json_printf("\"type\": \"DATA_TYPE_I64\"");
            ast2json_put_comma();
            ast2json_printf("\"data\": ");
            ast2json_printf("%" PRId64, literal->data.i64);
            break;
        case DATA_TYPE_F64:
            ast2json_put_comma();
            ast2json_printf("\"type\": \"DATA_TYPE_F64\"");
            ast2json_put_comma();
            ast2json_printf("\"data\": ");
            ast2json_printf("%lf", literal->data.f64);
            break;
        case DATA_TYPE_STR:
        case DATA_TYPE_INTERP_STR: {
            ast2json_put_comma();
            ast2json_printf("\"type\": \"DATA_TYPE_STR\"");
            ast2json_put_comma();
            ast2json_printf("\"data\": ");
            char *escaped_str = io_full_escape_string(literal->data.str);
            if (escaped_str) {
                ast2json_printf("\"%s\"", escaped_str);
                free(escaped_str);
            } else {
                ast2json_printf("null");
            }
            break;
        }
        case DATA_TYPE_LST:
            ast2json_put_comma();
            ast2json_printf("\"type\": \"DATA_TYPE_LST\"");
            ast2json_put_comma();
            ast2json_printf("\"data\": ");
            ast2json_CommaSepList(literal->data.lst);
            break;
        case DATA_TYPE_MAP:
            ast2json_put_comma();
            ast2json_printf("\"type\": \"DATA_TYPE_MAP\"");
            ast2json_put_comma();
            ast2json_printf("\"data\": ");
            ast2json_AssociativeList(literal->data.mp);
            break;
        case DATA_TYPE_ANY:
            ast2json_put_comma();
            ast2json_printf("\"type\": \"DATA_TYPE_ANY\"");
            ast2json_put_comma();
            ast2json_printf("\"data\": null");
            break;
    }

    ast2json_close_obj();
}

/* function to convert ast_Identifier_t to JSON */
void ast2json_Identifier(const ast_Identifier_t *identifier)
{
    if (!identifier) {
        ast2json_printf("null");
        return;
    }

    ast2json_open_obj();
    ast2json_printf("\"node\": \"identifier\"");
    ast2json_put_comma();
    ast2json_printf("\"identifier_name\": \"%s\"", identifier);
    ast2json_close_obj();
}

void ast2json_ModuleAndProcTable()
{
    /* open root */
    ast2json_open_obj();
    /* node name */
    ast2json_printf("\"node\": \"root\"");
    ast_util_ModuleAndProcTable_foreach_module(module_name, procmap, {
        /* open map of the module name to procedures */
        ast2json_put_comma();
        ast2json_printf("\"%s\": ", module_name);
        ast2json_open_obj();
        /* node name */
        ast2json_printf("\"node\": \"module\"");
        ast_util_ModuleAndProcTable_foreach_procedure(procmap, proc_name, filename, fnargs_list, code, {
            /* open a procedure node, map it with proc name */
            ast2json_put_comma();
            ast2json_printf("\"%s\": ", proc_name);
            ast2json_open_obj();
            ast2json_printf("\"node\": \"procedure\"");
            ast2json_put_comma();
            ast2json_printf("\"file\": \"%s\"", filename);
            ast2json_put_comma();
            ast2json_printf("\"fnargs_list\": ");
            ast2json_FnArgsList(fnargs_list);
            ast2json_put_comma();
            ast2json_printf("\"statements\": ");
            ast2json_Statements(code);
            /* close procedure */
            ast2json_close_obj();
        });
        ast2json_close_obj();
    });
    /* close root */
    ast2json_close_obj();
    ast2json_printf("\n");
}

void ast2json_convert(const char *filepath, bool format)
{
    ast2json_format = format;
    if (!strcmp(filepath, "-")) ast2json_outfile = stdout;
    else ast2json_outfile = fopen(filepath, "wb");
    ast2json_ModuleAndProcTable();
    if (ast2json_outfile != stdout)
        fclose(ast2json_outfile);
}
