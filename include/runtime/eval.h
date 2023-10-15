#ifndef RT_EVAL_H
#define RT_EVAL_H

#include "ast.h"

typedef enum {
    rt_CTRL_PASS,
    rt_CTRL_RETURN,
    rt_CTRL_BREAK,
    rt_CTRL_CONTINUE,
} rt_ControlStatus_t;

extern const char *rt_currfile;
extern int rt_currline;

extern const ast_Identifier_t *rt_current_module;
extern const ast_Identifier_t *rt_current_proc;

rt_ControlStatus_t rt_eval_Statements(const ast_Statements_t *code);
rt_ControlStatus_t rt_eval_Statements_newscope(const ast_Statements_t *code);
rt_ControlStatus_t rt_eval_Statement(const ast_Statement_t *statement);
void rt_eval_Assignment(const ast_Assignment_t *assignment);
rt_ControlStatus_t rt_eval_CompoundSt(const ast_CompoundSt_t *compound_st);
rt_ControlStatus_t rt_eval_IfBlock(const ast_IfBlock_t *if_block);
rt_ControlStatus_t rt_eval_ElseBlock(const ast_ElseBlock_t *else_block);
rt_ControlStatus_t rt_eval_WhileBlock(const ast_WhileBlock_t *while_block);
rt_ControlStatus_t rt_eval_ForBlock(const ast_ForBlock_t *for_block);
void rt_eval_Expression(const ast_Expression_t *expr);
void rt_eval_CommaSepList(const ast_CommaSepList_t *comma_list);
void rt_eval_AssociativeList(const ast_AssociativeList_t *assoc_list);
void rt_eval_Literal(const ast_Literal_t *literal);
void rt_eval_Identifier(const ast_Identifier_t *identifier);

void rt_call_function(const ast_Identifier_t *module, const ast_Identifier_t *proc);

#endif
