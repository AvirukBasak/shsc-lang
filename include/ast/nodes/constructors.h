#ifndef AST_NODES_CONSTRUCTORS_H
#define AST_NODES_CONSTRUCTORS_H

#include <stdbool.h>
#include <stdint.h>

#include "ast.h"
#include "lexer.h"

typedef lex_Token_t ast_Operator_t;

ast_Statements_t    *ast_Statements(ast_Statements_t *statements, ast_Statement_t *statement);

ast_Statement_t     *ast_Statement_empty(int line_no);
ast_Statement_t     *ast_Statement_break(int line_no);
ast_Statement_t     *ast_Statement_continue(int line_no);
ast_Statement_t     *ast_Statement_return(ast_Expression_t *expression, int line_no);
ast_Statement_t     *ast_Statement_Assignment(ast_Assignment_t *assignment, int line_no);
ast_Statement_t     *ast_Statement_CompoundSt(ast_CompoundSt_t *compund, int line_no);

ast_Assignment_t    *ast_Assignment_create(ast_Identifier_t *identifier, ast_Expression_t *expression, bool is_const, bool is_weak);
ast_Assignment_t    *ast_Assignment_tovoid(ast_Expression_t *expression);

ast_CompoundSt_t    *ast_CompoundSt_IfBlock(ast_IfBlock_t *block);
ast_CompoundSt_t    *ast_CompoundSt_WhileBlock(ast_WhileBlock_t *block);
ast_CompoundSt_t    *ast_CompoundSt_ForBlock(ast_ForBlock_t *block);
ast_CompoundSt_t    *ast_CompoundSt_Block(ast_Block_t *block);

ast_IfBlock_t       *ast_IfBlock(ast_Condition_t *condition, ast_Statements_t *if_st, ast_ElseBlock_t *else_block);
ast_ElseBlock_t     *ast_ElseBlock(ast_Condition_t *condition, ast_Statements_t *else_if_st, ast_ElseBlock_t *else_block);

ast_WhileBlock_t    *ast_WhileBlock(ast_Condition_t *condition, ast_Statements_t *while_st);
ast_ForBlock_t      *ast_ForBlock(ast_Identifier_t *val, ast_Expression_t *start, ast_Expression_t *end, ast_Expression_t *by, ast_Statements_t *for_st);
ast_ForBlock_t      *ast_ForBlock_iterate(ast_Identifier_t *idx, ast_Identifier_t *val, ast_Expression_t *iterable, ast_Statements_t *for_st);
ast_Block_t         *ast_Block(ast_Statements_t *statements);

ast_Expression_t    *ast_Expression(ast_Operator_t op, ast_Expression_t *lhs, ast_Expression_t *rhs, ast_Expression_t *condition);
ast_Expression_t    *ast_Expression_Literal(ast_Literal_t *literal);
ast_Expression_t    *ast_Expression_Identifier(ast_Identifier_t *identifier);
ast_Expression_t    *ast_Expression_CommaSepList(ast_CommaSepList_t *comma_list);

ast_CommaSepList_t  *ast_CommaSepList(ast_CommaSepList_t *comma_list, ast_Expression_t *expression);
ast_AssociativeList_t  *ast_AssociativeList(ast_AssociativeList_t *assoc_list, ast_Literal_t *key, ast_Expression_t *value);

ast_Literal_t       *ast_Literal_bul(bool literal);
ast_Literal_t       *ast_Literal_chr(char literal);
ast_Literal_t       *ast_Literal_f64(double literal);
ast_Literal_t       *ast_Literal_i64(int64_t literal);
ast_Literal_t       *ast_Literal_str(char *literal);
ast_Literal_t       *ast_Literal_interp_str(char *literal);
ast_Literal_t       *ast_Literal_lst(ast_CommaSepList_t *literal);
ast_Literal_t       *ast_Literal_map(ast_AssociativeList_t *literal);

ast_Identifier_t    *ast_Identifier(char *identifier_name);

#endif
