#ifndef AST2JSON_H
#define AST2JSON_H

#include <stdbool.h>
#include "ast.h"

void AST2JSON_Statements(const AST_Statements_t* statements);
void AST2JSON_Statement(const AST_Statement_t* statement);
void AST2JSON_Assignment(const AST_Assignment_t* assignment);
void AST2JSON_CompoundSt(const AST_CompoundSt_t* compound_statement);
void AST2JSON_IfBlock(const AST_IfBlock_t* if_block);
void AST2JSON_ElseIfBlock(const AST_ElseIfBlock_t* else_if_block);
void AST2JSON_ElseIfSt(const AST_ElseIfSt_t* else_if_st);
void AST2JSON_WhileBlock(const AST_WhileBlock_t* while_block);
void AST2JSON_ForBlock(const AST_ForBlock_t* for_block);
void AST2JSON_Block(const AST_Block_t* block);
void AST2JSON_Expression(const AST_Expression_t* expression);
void AST2JSON_CommaSepList(const AST_CommaSepList_t* comma_list);
void AST2JSON_Literal(const AST_Literal_t* literal);
void AST2JSON_Identifier(const AST_Identifier_t* identifier);
void AST2JSON_ProcedureMap();
void AST2JSON_convert(const char *filepath, bool format);

#endif
