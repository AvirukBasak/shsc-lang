#ifndef AST2JSON_H
#define AST2JSON_H

#include <stdbool.h>
#include "ast.h"

void AST2JSON_Statements(const ast_Statements_t* statements);
void AST2JSON_Statement(const ast_Statement_t* statement);
void AST2JSON_Assignment(const ast_Assignment_t* assignment);
void AST2JSON_CompoundSt(const ast_CompoundSt_t* compound_statement);
void AST2JSON_IfBlock(const ast_IfBlock_t* if_block);
void AST2JSON_ElseBlock(const ast_ElseBlock_t* else_block);
void AST2JSON_WhileBlock(const ast_WhileBlock_t* while_block);
void AST2JSON_ForBlock(const ast_ForBlock_t* for_block);
void AST2JSON_Block(const ast_Block_t* block);
void AST2JSON_Expression(const ast_Expression_t* expression);
void AST2JSON_CommaSepList(const ast_CommaSepList_t* comma_list);
void AST2JSON_AssociativeList(const ast_AssociativeList_t* assoc_list);
void AST2JSON_Literal(const ast_Literal_t* literal);
void AST2JSON_Identifier(const ast_Identifier_t* identifier);
void AST2JSON_ModuleAndProcTable();
void AST2JSON_convert(const char *filepath, bool format);

#endif
