#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errcodes.h"
#include "io.h"
#include "ast/api.h"
#include "ast2json.h"
#include "lexer.h"

void AST2JSON_printf(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
void AST2JSON_open_obj(void);
void AST2JSON_close_obj(void);
void AST2JSON_open_list(void);
void AST2JSON_close_list(void);
void AST2JSON_put_comma(void);

FILE *AST2JSON_outfile = NULL;
int AST2JSON_indent_depth = 0;
bool AST2JSON_format = false;

#define AST2JSON_INDENT_INCR (2)

void AST2JSON_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(AST2JSON_outfile, fmt, args);
    va_end(args);
}

void AST2JSON_open_obj(void)
{
    if (!AST2JSON_format) {
        AST2JSON_printf("{");
        return;
    }
    AST2JSON_indent_depth += AST2JSON_INDENT_INCR;
    AST2JSON_printf("{\n%*s", AST2JSON_indent_depth, "");
}

void AST2JSON_close_obj(void)
{
    if (!AST2JSON_format) {
        AST2JSON_printf("}");
        return;
    }
    AST2JSON_indent_depth -= AST2JSON_INDENT_INCR;
    AST2JSON_printf("\n%*s}", AST2JSON_indent_depth, "");
}

void AST2JSON_open_list(void)
{
    if (!AST2JSON_format) {
        AST2JSON_printf("[");
        return;
    }
    AST2JSON_indent_depth += AST2JSON_INDENT_INCR;
    AST2JSON_printf("[\n%*s", AST2JSON_indent_depth, "");
}

void AST2JSON_close_list(void)
{
    if (!AST2JSON_format) {
        AST2JSON_printf("]");
        return;
    }
    AST2JSON_indent_depth -= AST2JSON_INDENT_INCR;
    AST2JSON_printf("\n%*s]", AST2JSON_indent_depth, "");
}

void AST2JSON_put_comma(void)
{
    if (!AST2JSON_format) {
        AST2JSON_printf(", ");
        return;
    }
    AST2JSON_printf(",\n%*s", AST2JSON_indent_depth, "");
}

/* function to convert AST_Statements_t to JSON */
void AST2JSON_Statements(const AST_Statements_t *statements)
{
    if (!statements) {
        AST2JSON_printf("null");
        return;
    }

    AST2JSON_open_obj();
    AST2JSON_printf("\"node\": \"statements\"");
    AST2JSON_put_comma();
    AST2JSON_printf("\"statements\": ");
    AST2JSON_open_list();
    const AST_Statements_t *st = statements;
    AST2JSON_Statement(st->statement);
    st = st->statements;
    while (st) {
        AST2JSON_put_comma();
        AST2JSON_Statement(st->statement);
        st = st->statements;
    }
    AST2JSON_close_list();
    AST2JSON_close_obj();
}

/* function to convert AST_Statement_t to JSON */
void AST2JSON_Statement(const AST_Statement_t *statement)
{
    if (!statement) {
        AST2JSON_printf("null");
        return;
    }

    AST2JSON_open_obj();
    AST2JSON_printf("\"node\": \"statement\"");
    AST2JSON_put_comma();
    AST2JSON_printf("\"line_no\": %d", statement->line_no);

    switch (statement->type) {
        case STATEMENT_TYPE_RETURN:
            AST2JSON_put_comma();
            AST2JSON_printf("\"type\": \"STATEMENT_TYPE_RETURN\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"statement\": ");
            AST2JSON_Expression(statement->statement.expression);
            break;
        case STATEMENT_TYPE_ASSIGNMENT:
            AST2JSON_put_comma();
            AST2JSON_printf("\"type\": \"STATEMENT_TYPE_ASSIGNMENT\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"statement\": ");
            AST2JSON_Assignment(statement->statement.assignment);
            break;
        case STATEMENT_TYPE_COMPOUND:
            AST2JSON_put_comma();
            AST2JSON_printf("\"type\": \"STATEMENT_TYPE_COMPOUND\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"statement\": ");
            AST2JSON_CompoundSt(statement->statement.compound_statement);
            break;
        case STATEMENT_TYPE_EMPTY:
            AST2JSON_put_comma();
            AST2JSON_printf("\"type\": \"STATEMENT_TYPE_EMPTY\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"statement\": null");
            break;
        case STATEMENT_TYPE_BREAK:
            AST2JSON_put_comma();
            AST2JSON_printf("\"type\": \"STATEMENT_TYPE_BREAK\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"statement\": null");
            break;
        case STATEMENT_TYPE_CONTINUE:
            AST2JSON_put_comma();
            AST2JSON_printf("\"type\": \"STATEMENT_TYPE_CONTINUE\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"statement\": null");
            break;
    }
    AST2JSON_close_obj();
}

/* function to convert AST_Assignment_t to JSON */
void AST2JSON_Assignment(const AST_Assignment_t *assignment)
{
    if (!assignment) {
        AST2JSON_printf("null");
        return;
    }

    AST2JSON_open_obj();
    AST2JSON_printf("\"node\": \"assignment\"");
    AST2JSON_put_comma();
    AST2JSON_printf("\"lhs\": ");
    AST2JSON_Identifier(assignment->lhs);
    AST2JSON_put_comma();
    AST2JSON_printf("\"rhs\": ");
    AST2JSON_Expression(assignment->rhs);
    AST2JSON_close_obj();
}

/* function to convert AST_CompoundSt_t to JSON */
void AST2JSON_CompoundSt(const AST_CompoundSt_t *compound_statement)
{
    if (!compound_statement) {
        AST2JSON_printf("null");
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
        AST2JSON_printf("null");
        return;
    }

    AST2JSON_open_obj();
    AST2JSON_printf("\"node\": \"if_block\"");
    AST2JSON_put_comma();
    AST2JSON_printf("\"condition\": ");
    AST2JSON_Expression(if_block->condition);
    AST2JSON_put_comma();
    AST2JSON_printf("\"if_st\": ");
    AST2JSON_Statements(if_block->if_st);
    AST2JSON_put_comma();
    AST2JSON_printf("\"else_block\": ");
    AST2JSON_ElseBlock(if_block->else_block);
    AST2JSON_close_obj();
}

/* function to convert AST_ElseIfBlock_t to JSON */
void AST2JSON_ElseBlock(const AST_ElseBlock_t *else_block)
{
    if (!else_block) {
        AST2JSON_printf("null");
        return;
    }

    AST2JSON_open_obj();
    AST2JSON_printf("\"node\": \"else_block\"");
    AST2JSON_put_comma();
    AST2JSON_printf("\"condition\": ");
    AST2JSON_Expression(else_block->condition);
    AST2JSON_put_comma();
    AST2JSON_printf("\"else_if_st\": ");
    AST2JSON_Statements(else_block->else_if_st);
    AST2JSON_put_comma();
    AST2JSON_printf("\"else_block\": ");
    AST2JSON_ElseBlock(else_block->else_block);
    AST2JSON_close_obj();
}

/* function to convert AST_WhileBlock_t to JSON */
void AST2JSON_WhileBlock(const AST_WhileBlock_t *while_block)
{
    if (!while_block) {
        AST2JSON_printf("null");
        return;
    }

    AST2JSON_open_obj();
    AST2JSON_printf("\"node\": \"while_block\"");
    AST2JSON_put_comma();
    AST2JSON_printf("\"condition\": ");
    AST2JSON_Expression(while_block->condition);
    AST2JSON_put_comma();
    AST2JSON_printf("\"statements\": ");
    AST2JSON_Statements(while_block->statements);
    AST2JSON_close_obj();
}

/* Function to convert AST_ForBlock_t to JSON */
void AST2JSON_ForBlock(const AST_ForBlock_t *for_block)
{
    if (!for_block) {
        AST2JSON_printf("null");
        return;
    }

    AST2JSON_open_obj();
    AST2JSON_printf("\"node\": \"for_block\"");

    switch (for_block->type) {
        case FORBLOCK_TYPE_RANGE: {
            AST2JSON_put_comma();
            AST2JSON_printf("\"type\": \"FORBLOCK_TYPE_RANGE\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"val\": ");
            AST2JSON_Identifier(for_block->val);
            AST2JSON_put_comma();
            AST2JSON_printf("\"it\": ");
            AST2JSON_open_obj();
            AST2JSON_printf("\"node\": \"range\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"start\": ");
            AST2JSON_Expression(for_block->it.range.start);
            AST2JSON_put_comma();
            AST2JSON_printf("\"end\": ");
            AST2JSON_Expression(for_block->it.range.end);
            AST2JSON_put_comma();
            AST2JSON_printf("\"by\": ");
            AST2JSON_Expression(for_block->it.range.by);
            AST2JSON_close_obj();
            break;
        }
        case FORBLOCK_TYPE_LIST:
            AST2JSON_put_comma();
            AST2JSON_printf("\"type\": \"FORBLOCK_TYPE_LIST\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"idx\": ");
            AST2JSON_Identifier(for_block->idx);
            AST2JSON_put_comma();
            AST2JSON_printf("\"val\": ");
            AST2JSON_Identifier(for_block->val);
            AST2JSON_put_comma();
            AST2JSON_printf("\"it\": ");
            AST2JSON_Expression(for_block->it.iterable);
            break;
    }

    AST2JSON_put_comma();
    AST2JSON_printf("\"statements\": ");
    AST2JSON_Statements(for_block->statements);
    AST2JSON_close_obj();
}

/* Function to convert AST_Block_t to JSON */
void AST2JSON_Block(const AST_Block_t *block)
{
    if (!block) {
        AST2JSON_printf("null");
        return;
    }

    AST2JSON_open_obj();
    AST2JSON_printf("\"node\": \"block\"");
    AST2JSON_put_comma();
    AST2JSON_printf("\"statements\": ");
    AST2JSON_Statements(block->statements);
    AST2JSON_close_obj();
}

/* function to convert AST_Expression_t to JSON */
void AST2JSON_Expression(const AST_Expression_t *expression)
{
    if (!expression) {
        AST2JSON_printf("null");
        return;
    }

    AST2JSON_open_obj();
    AST2JSON_printf("\"node\": \"expression\"");
    AST2JSON_put_comma();
    AST2JSON_printf("\"op\": \"%s\"", lex_get_symbol(expression->op));

    switch (expression->lhs_type) {
        case EXPR_TYPE_EXPRESSION:
            AST2JSON_put_comma();
            AST2JSON_printf("\"lhs_type\": \"EXPR_TYPE_EXPRESSION\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"lhs\": ");
            AST2JSON_Expression(expression->lhs.expr);
            break;
        case EXPR_TYPE_LITERAL:
            AST2JSON_put_comma();
            AST2JSON_printf("\"lhs_type\": \"EXPR_TYPE_LITERAL\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"lhs\": ");
            AST2JSON_Literal(expression->lhs.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            AST2JSON_put_comma();
            AST2JSON_printf("\"lhs_type\": \"EXPR_TYPE_IDENTIFIER\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"lhs\": ");
            AST2JSON_Identifier(expression->lhs.variable);
            break;
        case EXPR_TYPE_NULL:
            AST2JSON_put_comma();
            AST2JSON_printf("\"lhs_type\": \"EXPR_TYPE_NULL\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"lhs\": null");
            break;
    }

    switch (expression->rhs_type) {
        case EXPR_TYPE_EXPRESSION:
            AST2JSON_put_comma();
            AST2JSON_printf("\"rhs_type\": \"EXPR_TYPE_EXPRESSION\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"rhs\": ");
            AST2JSON_Expression(expression->rhs.expr);
            break;
        case EXPR_TYPE_LITERAL:
            AST2JSON_put_comma();
            AST2JSON_printf("\"rhs_type\": \"EXPR_TYPE_LITERAL\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"rhs\": ");
            AST2JSON_Literal(expression->rhs.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            AST2JSON_put_comma();
            AST2JSON_printf("\"rhs_type\": \"EXPR_TYPE_IDENTIFIER\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"rhs\": ");
            AST2JSON_Identifier(expression->rhs.variable);
            break;
        case EXPR_TYPE_NULL:
            AST2JSON_put_comma();
            AST2JSON_printf("\"rhs_type\": \"EXPR_TYPE_NULL\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"rhs\": null");
            break;
    }

    switch (expression->condition_type) {
        case EXPR_TYPE_EXPRESSION:
            AST2JSON_put_comma();
            AST2JSON_printf("\"condition_type\": \"EXPR_TYPE_EXPRESSION\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"condition\": ");
            AST2JSON_Expression(expression->condition.expr);
            break;
        case EXPR_TYPE_LITERAL:
            AST2JSON_put_comma();
            AST2JSON_printf("\"condition_type\": \"EXPR_TYPE_LITERAL\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"condition\": ");
            AST2JSON_Literal(expression->condition.literal);
            break;
        case EXPR_TYPE_IDENTIFIER:
            AST2JSON_put_comma();
            AST2JSON_printf("\"condition_type\": \"EXPR_TYPE_IDENTIFIER\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"condition\": ");
            AST2JSON_Identifier(expression->condition.variable);
            break;
        case EXPR_TYPE_NULL:
            AST2JSON_put_comma();
            AST2JSON_printf("\"condition_type\": \"EXPR_TYPE_NULL\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"condition\": null");
            break;
    }

    AST2JSON_close_obj();
}

/* function to convert AST_CommaSepList_t to JSON */
void AST2JSON_CommaSepList(const AST_CommaSepList_t *comma_list)
{
    if (!comma_list) {
        AST2JSON_printf("null");
        return;
    }

    AST2JSON_open_obj();
    AST2JSON_printf("\"node\": \"comma_list\"");

    const AST_CommaSepList_t *lst = comma_list;
    AST2JSON_put_comma();
    AST2JSON_printf("\"comma_list\": ");
    AST2JSON_open_list();
    AST2JSON_Expression(lst->expression);
    lst = lst->comma_list;

    while (lst) {
        AST2JSON_put_comma();
        AST2JSON_Expression(lst->expression);
        lst = lst->comma_list;
    }

    AST2JSON_close_list();
    AST2JSON_close_obj();
}

void AST2JSON_AssociativeList(const AST_AssociativeList_t* assoc_list)
{
    if (!assoc_list) {
        AST2JSON_printf("null");
        return;
    }

    AST2JSON_open_obj();
    AST2JSON_printf("\"node\": \"assoc_list\"");

    const AST_AssociativeList_t *mp = assoc_list;
    AST2JSON_put_comma();
    AST2JSON_printf("\"assoc_list\": ");
    AST2JSON_open_list();

    AST2JSON_open_obj();
    AST2JSON_printf("\"key\": ");
    AST2JSON_Literal(mp->key);
    AST2JSON_put_comma();
    AST2JSON_printf("\"value\": ");
    AST2JSON_Expression(mp->value);
    AST2JSON_close_obj();

    mp = mp->assoc_list;

    while (mp) {
        AST2JSON_put_comma();
        AST2JSON_open_obj();
        AST2JSON_printf("\"key\": ");
        AST2JSON_Literal(mp->key);
        AST2JSON_put_comma();
        AST2JSON_printf("\"value\": ");
        AST2JSON_Expression(mp->value);
        AST2JSON_close_obj();
        mp = mp->assoc_list;
    }

    AST2JSON_close_list();
    AST2JSON_close_obj();
}

/* function to convert AST_Literal_t to JSON */
void AST2JSON_Literal(const AST_Literal_t *literal)
{
    if (!literal) {
        AST2JSON_printf("null");
        return;
    }

    AST2JSON_open_obj();
    AST2JSON_printf("\"node\": \"literal\"");

    switch (literal->type) {
        case DATA_TYPE_BUL:
            AST2JSON_put_comma();
            AST2JSON_printf("\"type\": \"DATA_TYPE_BUL\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"data\": ");
            AST2JSON_printf("%s", literal->data.bul ? "true" : "false");
            break;
        case DATA_TYPE_CHR: {
            char chr[2] = { literal->data.chr, '\0' };
            char *escaped_chr = io_full_escape_string(chr);
            AST2JSON_put_comma();
            AST2JSON_printf("\"type\": \"DATA_TYPE_CHR\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"data\": ");
            if (escaped_chr) {
                AST2JSON_printf("\"%s\"", escaped_chr);
                free(escaped_chr);
            } else {
                AST2JSON_printf("null");
            }
            break;
        }
        case DATA_TYPE_I64:
            AST2JSON_put_comma();
            AST2JSON_printf("\"type\": \"DATA_TYPE_I64\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"data\": ");
            AST2JSON_printf("%" PRId64, literal->data.i64);
            break;
        case DATA_TYPE_F64:
            AST2JSON_put_comma();
            AST2JSON_printf("\"type\": \"DATA_TYPE_F64\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"data\": ");
            AST2JSON_printf("%lf", literal->data.f64);
            break;
        case DATA_TYPE_STR:
        case DATA_TYPE_INTERP_STR: {
            AST2JSON_put_comma();
            AST2JSON_printf("\"type\": \"DATA_TYPE_STR\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"data\": ");
            char *escaped_str = io_full_escape_string(literal->data.str);
            if (escaped_str) {
                AST2JSON_printf("\"%s\"", escaped_str);
                free(escaped_str);
            } else {
                AST2JSON_printf("null");
            }
            break;
        }
        case DATA_TYPE_LST:
            AST2JSON_put_comma();
            AST2JSON_printf("\"type\": \"DATA_TYPE_LST\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"data\": ");
            AST2JSON_CommaSepList(literal->data.lst);
            break;
        case DATA_TYPE_MAP:
            AST2JSON_put_comma();
            AST2JSON_printf("\"type\": \"DATA_TYPE_MAP\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"data\": ");
            AST2JSON_AssociativeList(literal->data.mp);
            break;
        case DATA_TYPE_ANY:
            AST2JSON_put_comma();
            AST2JSON_printf("\"type\": \"DATA_TYPE_ANY\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"data\": null");
            break;
    }

    AST2JSON_close_obj();
}

/* function to convert AST_Identifier_t to JSON */
void AST2JSON_Identifier(const AST_Identifier_t *identifier)
{
    if (!identifier) {
        AST2JSON_printf("null");
        return;
    }

    AST2JSON_open_obj();
    AST2JSON_printf("\"node\": \"identifier\"");
    AST2JSON_put_comma();
    AST2JSON_printf("\"identifier_name\": \"%s\"", identifier->identifier_name);
    AST2JSON_close_obj();
}

void AST2JSON_ModuleAndProcTable()
{
    /* open root */
    AST2JSON_open_obj();
    /* node name */
    AST2JSON_printf("\"node\": \"root\"");
    AST_util_ModuleAndProcTable_foreach_module(modulename, procmap, {
        /* open map of the module name to procedures */
        AST2JSON_put_comma();
        AST2JSON_printf("\"%s\": ", modulename);
        AST2JSON_open_obj();
        /* node name */
        AST2JSON_printf("\"node\": \"module\"");
        AST_util_ModuleAndProcTable_foreach_procedure(procmap, procname, filename, code, {
            /* open a procedure node, map it with proc name */
            AST2JSON_put_comma();
            AST2JSON_printf("\"%s\": ", procname);
            AST2JSON_open_obj();
            AST2JSON_printf("\"node\": \"procedure\"");
            AST2JSON_put_comma();
            AST2JSON_printf("\"file\": \"%s\"", filename);
            AST2JSON_put_comma();
            AST2JSON_printf("\"statements\": ");
            AST2JSON_Statements(code);
            /* close procedure */
            AST2JSON_close_obj();
        });
        AST2JSON_close_obj();
    });
    /* close root */
    AST2JSON_close_obj();
    AST2JSON_printf("\n");
}

void AST2JSON_convert(const char *filepath, bool format)
{
    AST2JSON_format = format;
    if (!strcmp(filepath, "-")) AST2JSON_outfile = stdout;
    else AST2JSON_outfile = fopen(filepath, "wb");
    AST2JSON_ModuleAndProcTable();
    if (AST2JSON_outfile != stdout)
        fclose(AST2JSON_outfile);
}
