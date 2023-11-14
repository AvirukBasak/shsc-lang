#ifndef AST2JSON_H
#define AST2JSON_H

#include <stdbool.h>
#include "ast.h"

void ast2json_Statements(const ast_Statements_t* statements);
void ast2json_Statement(const ast_Statement_t* statement);
void ast2json_Assignment(const ast_Assignment_t* assignment);
void ast2json_CompoundSt(const ast_CompoundSt_t* compound_statement);
void ast2json_IfBlock(const ast_IfBlock_t* if_block);
void ast2json_ElseBlock(const ast_ElseBlock_t* else_block);
void ast2json_WhileBlock(const ast_WhileBlock_t* while_block);
void ast2json_ForBlock(const ast_ForBlock_t* for_block);
void ast2json_Block(const ast_Block_t* block);
void ast2json_FnArgsList(const ast_FnArgsList_t *fnargs_list);
void ast2json_Expression(const ast_Expression_t* expression);
void ast2json_CommaSepList(const ast_CommaSepList_t* comma_list);
void ast2json_AssociativeList(const ast_AssociativeList_t* assoc_list);
void ast2json_Literal(const ast_Literal_t* literal);
void ast2json_Identifier(const ast_Identifier_t* identifier);
void ast2json_ModuleAndProcTable();
void ast2json_convert(const char *filepath, bool format);

#endif
