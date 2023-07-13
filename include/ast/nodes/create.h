#ifndef AST_NODES_CREATE_H
#define AST_NODES_CREATE_H

#include "lexer.h"
#include "ast.h"

typedef LexToken AST_Operator_t;

AST_Statements_t    *AST_Statements(AST_Statements_t *statements, AST_Statement_t *statement);

AST_Statement_t     *AST_Statement_empty(int line_no);
AST_Statement_t     *AST_Statement_Assignment(AST_Assignment_t *assignment, int line_no);
AST_Statement_t     *AST_Statement_CompoundSt(AST_CompoundSt_t *compund, int line_no);

AST_Assignment_t    *AST_Assignment_create(AST_Identifier_t *identifier, AST_Expression_t *expression);
AST_Assignment_t    *AST_Assignment_update(AST_Identifier_t *identifier, AST_Expression_t *expression);
AST_Assignment_t    *AST_Assignment_tovoid(AST_Expression_t *expression);

AST_CompoundSt_t    *AST_CompoundSt_IfBlock(AST_IfBlock_t *block);
AST_CompoundSt_t    *AST_CompoundSt_WhileBlock(AST_WhileBlock_t *block);
AST_CompoundSt_t    *AST_CompoundSt_ForBlock(AST_ForBlock_t *block);
AST_CompoundSt_t    *AST_CompoundSt_Block(AST_Block_t *block);

AST_IfBlock_t       *AST_IfBlock(AST_Condition_t *condition, AST_Statements_t *if_st, AST_ElseIfBlock_t *else_if_block, AST_Statements_t *else_st);
AST_ElseIfBlock_t   *AST_ElseIfBlock(AST_ElseIfBlock_t *else_if_block, AST_ElseIfSt_t *else_if_st);
AST_ElseIfSt_t      *AST_ElseIfSt(AST_Condition_t *condition, AST_Statements_t *statements);

AST_WhileBlock_t    *AST_WhileBlock(AST_Condition_t *condition, AST_Statements_t *while_st);
AST_ForBlock_t      *AST_ForBlock(AST_Identifier_t *iter, AST_Operand_t *start, AST_Operand_t *end, AST_Operand_t *by, AST_Statements_t *for_st);
AST_ForBlock_t      *AST_ForBlock_iterate(AST_Identifier_t *iter, AST_Operand_t *oprnd, AST_Statements_t *for_st);
AST_Block_t         *AST_Block(AST_Statements_t *statements);

AST_Expression_t    *AST_Expression(AST_Operator_t op, AST_Expression_t *lhs, AST_Expression_t *rhs, AST_Expression_t *condition);
AST_Expression_t    *AST_Expression_Operand(AST_Operand_t *operand);
AST_Expression_t    *AST_Expression_Identifier(AST_Identifier_t *identifier);
AST_Expression_t    *AST_Expression_CommaSepList(AST_CommaSepList_t *comma_list);

AST_CommaSepList_t  *AST_CommaSepList(AST_CommaSepList_t *comma_list, AST_Expression_t *expression);

AST_Operand_t       *AST_Operand_Literal(AST_Literal_t *literal);
AST_Operand_t       *AST_Operand_Identifier(AST_Identifier_t *identifier);

AST_Literal_t       *AST_Literal_bul(bool literal);
AST_Literal_t       *AST_Literal_chr(char literal);
AST_Literal_t       *AST_Literal_f64(double literal);
AST_Literal_t       *AST_Literal_i64(int64_t literal);
AST_Literal_t       *AST_Literal_str(char *literal);
AST_Literal_t       *AST_Literal_interp_str(char *literal);
AST_Literal_t       *AST_Literal_lst(AST_CommaSepList_t *literal);

AST_Identifier_t    *AST_Identifier(char *identifier_name);

#endif