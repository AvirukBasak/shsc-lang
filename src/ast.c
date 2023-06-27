#include <stdlib.h>  // for malloc

#include "ast.h"

void AST_module_stack_push(AST_Identifier *module_name)
{
    // TODO: add implementation
}

AST_Identifier *AST_module_stack_top(void)
{
    // TODO: add implementation
}

AST_Identifier *AST_module_stack_pop(void)
{
    // TODO: add implementation
}

void AST_module_stack_clear(void)
{
    // TODO: add implementation
}

void AST_procedure_add(AST_Identifier *module_name, AST_Identifier *procedure_name, AST_Statements *statements)
{
    // TODO: add implementation
}

AST_Statements *AST_statements(AST_Statements *statements, AST_Statement *statement)
{
    AST_Statements *stmts = (AST_Statements*) malloc(sizeof(AST_Statements));
    stmts->statements = statements;
    stmts->statement = statement;
    return stmts;
}

AST_Statement *AST_statement_empty(void) {
    AST_Statement *stmt = (AST_Statement*) malloc(sizeof(AST_Statement));
    stmt->type = STATEMENT_TYPE_EMPTY;
    stmt->statement.assignment = NULL;
    return stmt;
}

AST_Statement *AST_statement_assignment(AST_Assignment *assignment)
{
    AST_Statement *stmt = (AST_Statement*) malloc(sizeof(AST_Statement));
    stmt->type = STATEMENT_TYPE_ASSIGNMENT;
    stmt->statement.assignment = assignment;
    return stmt;
}

AST_Statement *AST_statement_compound(AST_CompoundStatement *compound)
{
    AST_Statement *stmt = (AST_Statement*) malloc(sizeof(AST_Statement));
    stmt->type = STATEMENT_TYPE_COMPOUND;
    stmt->statement.compound_statement = compound;
    return stmt;
}

AST_Assignment *AST_assignment_create(AST_Identifier *identifier, AST_Expression *expression)
{
    AST_Assignment *assign = (AST_Assignment*) malloc(sizeof(AST_Assignment));
    assign->lhs = identifier;
    assign->rhs = expression;
    assign->type = ASSIGNMENT_TYPE_CREATE;
    return assign;
}

AST_Assignment *AST_assignment_update(AST_Identifier *identifier, AST_Expression *expression)
{
    AST_Assignment *assign = (AST_Assignment*) malloc(sizeof(AST_Assignment));
    assign->lhs = identifier;
    assign->rhs = expression;
    assign->type = ASSIGNMENT_TYPE_UPDATE;
    return assign;
}

AST_Assignment *AST_assignment_tovoid(AST_Expression *expression)
{
    AST_Assignment *assign = (AST_Assignment*) malloc(sizeof(AST_Assignment));
    assign->lhs = NULL;
    assign->rhs = expression;
    assign->type = ASSIGNMENT_TYPE_TOVOID;
    return assign;
}

AST_CompoundStatement *AST_compoundst_if_block(AST_IfBlock *block)
{
    AST_CompoundStatement *compound = (AST_CompoundStatement*) malloc(sizeof(AST_CompoundStatement));
    compound->type = COMPOUNDST_TYPE_IF;
    compound->compound_statement.if_block = block;
    return compound;
}

AST_CompoundStatement *AST_compoundst_if_else_block(AST_IfElseBlock *block)
{
    AST_CompoundStatement *compound = (AST_CompoundStatement*) malloc(sizeof(AST_CompoundStatement));
    compound->type = COMPOUNDST_TYPE_IF_ELSE;
    compound->compound_statement.if_else_block = block;
    return compound;
}

AST_CompoundStatement *AST_compoundst_if_else_if_block(AST_IfElseIfBlock *block)
{
    AST_CompoundStatement *compound = (AST_CompoundStatement*) malloc(sizeof(AST_CompoundStatement));
    compound->type = COMPOUNDST_TYPE_IF_ELSE_IF;
    compound->compound_statement.if_else_if_block = block;
    return compound;
}

AST_CompoundStatement *AST_compoundst_while_block(AST_WhileBlock *block)
{
    AST_CompoundStatement *compound = (AST_CompoundStatement*) malloc(sizeof(AST_CompoundStatement));
    compound->type = COMPOUNDST_TYPE_WHILE;
    compound->compound_statement.while_block = block;
    return compound;
}

AST_CompoundStatement *AST_compoundst_for_block(AST_ForBlock *block)
{
    AST_CompoundStatement *compound = (AST_CompoundStatement*) malloc(sizeof(AST_CompoundStatement));
    compound->type = COMPOUNDST_TYPE_FOR;
    compound->compound_statement.for_block = block;
    return compound;
}

AST_CompoundStatement *AST_compoundst_block(AST_Block *block)
{
    AST_CompoundStatement *compound = (AST_CompoundStatement*) malloc(sizeof(AST_CompoundStatement));
    compound->type = COMPOUNDST_TYPE_BLOCK;
    compound->compound_statement.block = block;
    return compound;
}

AST_IfBlock *AST_if_block(AST_Condition *condition, AST_Statements *if_st)
{
    AST_IfBlock *if_block = (AST_IfBlock*) malloc(sizeof(AST_IfBlock));
    if_block->condition = condition;
    if_block->statements = if_st;
    return if_block;
}

AST_IfElseBlock *AST_if_else_block(AST_Condition *condition, AST_Statements *if_st, AST_Statements *else_st)
{
    AST_IfElseBlock *if_else_block = (AST_IfElseBlock*) malloc(sizeof(AST_IfElseBlock));
    if_else_block->condition = condition;
    if_else_block->if_statements = if_st;
    if_else_block->else_statements = else_st;
    return if_else_block;
}

AST_IfElseIfBlock *AST_if_else_if_block(AST_Condition *condition, AST_Statements *if_st, AST_ElseIfBlock *block)
{
    AST_IfElseIfBlock *if_else_if_block = (AST_IfElseIfBlock*) malloc(sizeof(AST_IfElseIfBlock));
    if_else_if_block->condition = condition;
    if_else_if_block->if_statements = if_st;
    if_else_if_block->else_if_block = block;
    return if_else_if_block;
}

AST_ElseIfBlock *AST_else_if_block(AST_IfElseIfBlock *block)
{
    AST_ElseIfBlock *else_if_block = (AST_ElseIfBlock*) malloc(sizeof(AST_ElseIfBlock));
    else_if_block->if_else_if_block = block;
    return else_if_block;
}

AST_WhileBlock *AST_while_block(AST_Condition *condition, AST_Statements *while_st)
{
    AST_WhileBlock *while_block = (AST_WhileBlock*) malloc(sizeof(AST_WhileBlock));
    while_block->condition = condition;
    while_block->statements = while_st;
    return while_block;
}

AST_ForBlock *AST_for_block(AST_Identifier *iter, AST_Operand *start, AST_Operand *end, AST_Operand *by, AST_Statements *for_st)
{
    AST_ForBlock *for_block = (AST_ForBlock*) malloc(sizeof(AST_ForBlock));
    for_block->iter = iter;
    for_block->start = start;
    for_block->end = end;
    for_block->by = by;
    for_block->statements = for_st;
    return for_block;
}

AST_Block *AST_block(AST_Statements *statements)
{
    AST_Block *block = (AST_Block*) malloc(sizeof(AST_Block));
    block->statements = statements;
    return block;
}

AST_Condition *AST_condition(AST_Expression *expression)
{
    // TODO: add implementation
}

AST_Operand *AST_operand_literal(AST_Literal *literal)
{
    AST_Operand *operand = (AST_Operand*) malloc(sizeof(AST_Operand));
    operand->type = OPERAND_TYPE_LITERAL;
    operand->operand.literal = literal;
    return operand;
}

AST_Operand *AST_operand_identifier(AST_Identifier *identifier)
{
    AST_Operand *operand = (AST_Operand*) malloc(sizeof(AST_Operand));
    operand->type = OPERAND_TYPE_IDENTIFIER;
    operand->operand.variable = identifier;
    return operand;
}

AST_Literal *AST_literal_bul(bool literal)
{
    AST_Literal *ast_literal = (AST_Literal*) malloc(sizeof(AST_Literal));
    ast_literal->type = DATA_TYPE_BUL;
    ast_literal->data.bul = literal;
    return ast_literal;
}

AST_Literal *AST_literal_chr(char literal)
{
    AST_Literal *ast_literal = (AST_Literal*) malloc(sizeof(AST_Literal));
    ast_literal->type = DATA_TYPE_CHR;
    ast_literal->data.chr = literal;
    return ast_literal;
}

AST_Literal *AST_literal_f64(double literal)
{
    AST_Literal *ast_literal = (AST_Literal*) malloc(sizeof(AST_Literal));
    ast_literal->type = DATA_TYPE_F64;
    ast_literal->data.f64 = literal;
    return ast_literal;
}

AST_Literal *AST_literal_i64(int64_t literal)
{
    AST_Literal *ast_literal = (AST_Literal*) malloc(sizeof(AST_Literal));
    ast_literal->type = DATA_TYPE_I64;
    ast_literal->data.i64 = literal;
    return ast_literal;
}

AST_Literal *AST_literal_str(char *literal)
{
    AST_Literal *ast_literal = (AST_Literal*) malloc(sizeof(AST_Literal));
    ast_literal->type = DATA_TYPE_STR;
    ast_literal->data.str = literal;
    return ast_literal;
}

AST_Literal *AST_literal_interp_str(char *literal)
{
    AST_Literal *ast_literal = (AST_Literal*) malloc(sizeof(AST_Literal));
    ast_literal->type = DATA_TYPE_INTERP_STR;
    ast_literal->data.str = literal;
    return ast_literal;
}

AST_Identifier *AST_identifier(char *identifier_name)
{
    AST_Identifier *identifier = (AST_Identifier*) malloc(sizeof(AST_Identifier));
    identifier->identifier_name = identifier_name;
    return identifier;
}
