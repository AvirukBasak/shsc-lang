#include <inttypes.h>
#include <stdbool.h>

#include "ast.h"
#include "ast/api.h"
#include "runtime.h"
#include "ast/nodes/enums.h"
#include "ast/util/procedure_map.h"
#include "functions.h"
#include "lexer.h"
#include "parser.yy.h"
#include "runtime/data.h"
#include "runtime/data/list.h"
#include "runtime/data/string.h"
#include "runtime/io.h"

#include "runtime/data.c.h"
#include "runtime/io.c.h"
#include "runtime/vartable.c.h"
#include "runtime/vartable.h"

#define RT_ACC_DATA (RT_VarTable_acc_get()->adr ? RT_VarTable_acc_get()->adr : &RT_VarTable_acc_get()->val)

const char *rt_currfile = NULL;
int rt_currline = 0;

const AST_Identifier_t *rt_current_module = NULL;
const AST_Identifier_t *rt_current_proc = NULL;

const AST_Identifier_t *rt_modulename_get(void);
const AST_Identifier_t *rt_procname_get(void);

bool rt_Statements_eval(const AST_Statements_t *code);
bool rt_Statements_newscope_eval(const AST_Statements_t *code);
bool rt_Statement_eval(const AST_Statement_t *statement);
void rt_Assignment_eval(const AST_Assignment_t *assignment);
void rt_CompoundSt_eval(const AST_CompoundSt_t *compound_st);
void rt_IfBlock_eval(const AST_IfBlock_t *if_block);
void rt_ElseBlock_eval(const AST_ElseBlock_t *else_block);
void rt_WhileBlock_eval(const AST_WhileBlock_t *while_block);
void rt_ForBlock_eval(const AST_ForBlock_t *for_block);
void rt_Expression_eval(const AST_Expression_t *expr);
void rt_CommaSepList_eval(const AST_CommaSepList_t *comma_list);
void rt_Literal_eval(const AST_Literal_t *literal);
void rt_Identifier_eval(const AST_Identifier_t *identifier);

void rt_fncall_handler(const AST_Identifier_t *module, const AST_Identifier_t *proc);

void RT_exec(void)
{
    const AST_Identifier_t *module = AST_ProcedureMap_main();
    const AST_Identifier_t *proc = AST_ProcedureMap_main();
    const AST_Statements_t *code = AST_ProcedureMap_get_code(module, proc);
    rt_currfile = AST_ProcedureMap_get_filename(module, proc);
    RT_VarTable_push_proc(proc->identifier_name, NULL);
    rt_Statements_eval(code);
    RT_VarTable_pop_proc();
}

const AST_Identifier_t *rt_modulename_get(void)
{
    if (!rt_current_module) rt_current_module = AST_ProcedureMap_main();
    return rt_current_module;
}

const AST_Identifier_t *rt_procname_get(void)
{
    if (!rt_current_module) rt_current_module = AST_ProcedureMap_main();
    return rt_current_module;
}

bool rt_Statements_eval(const AST_Statements_t *code)
{
    if (!code) return false;
    const AST_Statements_t *ptr = code;
    while (ptr) {
        bool return_ = rt_Statement_eval(ptr->statement);
        if (return_) return true;
        ptr = ptr->statements;
    }
    return false;
}

bool rt_Statements_newscope_eval(const AST_Statements_t *code)
{
    if (!code) return false;
    RT_VarTable_push_scope();
    bool return_ = rt_Statements_eval(code);
    RT_VarTable_pop_scope();
    return return_;
}

bool rt_Statement_eval(const AST_Statement_t *statement)
{
    if (!statement) return false;
    rt_currline = statement->line_no;
    switch (statement->type) {
        case STATEMENT_TYPE_EMPTY:
            break;
        case STATEMENT_TYPE_RETURN:
            rt_Expression_eval(statement->statement.expression);
            return true;
        case STATEMENT_TYPE_ASSIGNMENT:
            rt_Assignment_eval(statement->statement.assignment);
            break;
        case STATEMENT_TYPE_COMPOUND:
            rt_CompoundSt_eval(statement->statement.compound_statement);
            break;
    }
    return false;
}

void rt_Assignment_eval(const AST_Assignment_t *assignment)
{
    if (!assignment) return;
    switch (assignment->type) {
        case ASSIGNMENT_TYPE_TOVOID:
            rt_Expression_eval(assignment->rhs);
            break;
        case ASSIGNMENT_TYPE_CREATE: {
            const char *idf = assignment->lhs->identifier_name;
            rt_Expression_eval(assignment->rhs);
            RT_VarTable_create(idf, *RT_ACC_DATA);
            break;
        }
    }
}

void rt_CompoundSt_eval(const AST_CompoundSt_t *compound_st)
{
    if (!compound_st) return;
    switch (compound_st->type) {
        case COMPOUNDST_TYPE_IF:
            rt_IfBlock_eval(compound_st->compound_statement.if_block);
            break;
        case COMPOUNDST_TYPE_WHILE:
            rt_WhileBlock_eval(compound_st->compound_statement.while_block);
            break;
        case COMPOUNDST_TYPE_FOR:
            rt_ForBlock_eval(compound_st->compound_statement.for_block);
            break;
        case COMPOUNDST_TYPE_BLOCK:
            rt_Statements_newscope_eval(compound_st->compound_statement.block->statements);
            break;
    }
}

void rt_IfBlock_eval(const AST_IfBlock_t *if_block)
{
    if (!if_block) return;
    rt_Expression_eval(if_block->condition);
    bool cond = RT_Data_tobool(*RT_ACC_DATA);
    if (cond) rt_Statements_newscope_eval(if_block->if_st);
    else rt_ElseBlock_eval(if_block->else_block);
}

void rt_ElseBlock_eval(const AST_ElseBlock_t *else_block)
{
    if (!else_block) return;
    /* takes care of [ else nwp statements end ] */
    if (!else_block->condition && !else_block->else_block) {
        rt_Statements_newscope_eval(else_block->else_if_st);
        return;
    }
    /* takes care of [ else if condition then nwp statements ] */
    rt_Expression_eval(else_block->condition);
    bool cond = RT_Data_tobool(*RT_ACC_DATA);
    if (cond) rt_Statements_newscope_eval(else_block->else_if_st);
    else rt_ElseBlock_eval(else_block->else_block);
}

void rt_WhileBlock_eval(const AST_WhileBlock_t *while_block)
{
    if (!while_block) return;
    rt_Expression_eval(while_block->condition);
    bool cond = RT_Data_tobool(*RT_ACC_DATA);
    while (cond) {
        rt_Statements_newscope_eval(while_block->statements);
    }
}

void rt_ForBlock_eval(const AST_ForBlock_t *for_block)
{
    if (!for_block) return;
    switch (for_block->type) {
        case FORBLOCK_TYPE_RANGE: {
            /* calculate start, end and by */
            rt_Expression_eval(for_block->iterable.range.start);
            RT_Data_t start = *RT_ACC_DATA;
            if (start.type != RT_DATA_TYPE_I64)
                rt_throw("for loop range start should be an i64");
            rt_Expression_eval(for_block->iterable.range.end);
            RT_Data_t end = *RT_ACC_DATA;
            if (end.type != RT_DATA_TYPE_I64)
                rt_throw("for loop range end should be an i64");
            RT_Data_t by = RT_Data_null();
            if (for_block->iterable.range.by) {
                rt_Expression_eval(for_block->iterable.range.by);
                by = *RT_ACC_DATA;
                if (by.type != RT_DATA_TYPE_I64)
                    rt_throw("for loop by value should be an i64");
            }
            const int64_t start_i = start.data.i64;
            const int64_t end_i = end.data.i64;
            const int64_t by_i = RT_Data_isnull(by) ?
                (start_i <= end_i ? +1 : -1) : by.data.i64;
            if (!by_i) rt_throw("for loop by value cannot be 0");
            if ( (start_i < end_i && by_i < 0) || (start_i > end_i && by_i > 0) )
                rt_throw("possible infinite for loop for by value '%" PRId64 "'", by_i);
            /* start for loop */
            for (int64_t i = start_i; i < end_i; i += by_i) {
                RT_VarTable_push_scope();
                RT_VarTable_create(for_block->iter->identifier_name,
                    RT_Data_i64(i));
                bool return_ = rt_Statements_eval(for_block->statements);
                RT_VarTable_pop_scope();
                if (return_) break;
            }
            break;
        }
        case FORBLOCK_TYPE_LIST: {
            /* convert expression to a data list */
            rt_Expression_eval(for_block->iterable.lst);
            RT_Data_t iterable = *RT_ACC_DATA;
            int64_t length = 0;
            switch (iterable.type) {
                case RT_DATA_TYPE_LST:
                    length = RT_DataList_length(iterable.data.lst);
                    break;
                case RT_DATA_TYPE_STR:
                    length = RT_DataStr_length(iterable.data.str);
                    break;
                default:
                    rt_throw("unsupported for loop iterable type");
            }
            for (int64_t i = 0; i < length; ++i) {
                RT_VarTable_push_scope();
                switch (iterable.type) {
                    case RT_DATA_TYPE_LST:
                        RT_VarTable_create(for_block->iter->identifier_name,
                            *RT_DataList_getref(iterable.data.lst, i));
                        break;
                    case RT_DATA_TYPE_STR:
                        RT_VarTable_create(for_block->iter->identifier_name,
                            RT_Data_chr(*RT_DataStr_getref(iterable.data.str, i)));
                        break;
                    default:
                        rt_throw("unsupported for loop iterable type");
                }
                bool return_ = rt_Statements_eval(for_block->statements);
                RT_VarTable_pop_scope();
                if (return_) break;
            }
            /* destroy iterable object */
            RT_Data_destroy(&iterable);
        }
    }
}

void rt_Expression_eval(const AST_Expression_t *expr)
{
    if (!expr) {
        RT_VarTable_acc_setval(RT_Data_null());
        return;
    }
    /* take care pf fn calls and membership operations */
    switch (expr->op) {
        case LEXTOK_DOT:
            return;
        case LEXTOK_DCOLON:
            return;
        case TOKOP_FNCALL: {
            const AST_CommaSepList_t *ptr = expr->rhs_type != EXPR_TYPE_NULL ?
                expr->rhs.literal->data.lst : NULL;
            /* copy fn args into temporary location */
            for (int i = 0; i < RT_TMPVAR_CNT; ++i) {
                const char var[4] = { ((i % 100) / 10) + '0', (i % 10) + '0', '\0' };
                if (ptr) rt_Expression_eval(ptr->expression);
                RT_Data_t data = ptr ? *RT_ACC_DATA : RT_Data_null();
                RT_VarTable_modf(RT_VarTable_getref(var), data);
                ptr = ptr ? ptr->comma_list : ptr;
            }
            /* get fn code and push code to stack */
            rt_fncall_handler(rt_modulename_get(), expr->lhs.variable);
            return;
        }
        default: break;
    }

    /* handle lhs and evaluate it */
    RT_Data_t *lhs = NULL;
    switch (expr->lhs_type) {
        case EXPR_TYPE_EXPRESSION:
            rt_Expression_eval(expr->lhs.expr);
            lhs = RT_ACC_DATA;
            break;
        case EXPR_TYPE_LITERAL:
            rt_Literal_eval(expr->lhs.literal);
            lhs = RT_ACC_DATA;
            break;
        case EXPR_TYPE_IDENTIFIER:
            rt_Identifier_eval(expr->lhs.variable);
            lhs = RT_ACC_DATA;
            break;
        case EXPR_TYPE_NULL: break;
    }

    /* handle rhs and evaluate it */
    RT_Data_t *rhs = NULL;
    switch (expr->rhs_type) {
        case EXPR_TYPE_EXPRESSION:
            rt_Expression_eval(expr->rhs.expr);
            rhs = RT_ACC_DATA;
            break;
        case EXPR_TYPE_LITERAL:
            rt_Literal_eval(expr->rhs.literal);
            rhs = RT_ACC_DATA;
            break;
        case EXPR_TYPE_IDENTIFIER:
            rt_Identifier_eval(expr->rhs.variable);
            rhs = RT_ACC_DATA;
            break;
        case EXPR_TYPE_NULL: break;
    }

    /* handle condition and evaluate it */
    RT_Data_t *condition = NULL;
    switch (expr->condition_type) {
        case EXPR_TYPE_EXPRESSION:
            rt_Expression_eval(expr->condition.expr);
            condition = RT_ACC_DATA;
            break;
        case EXPR_TYPE_LITERAL:
            rt_Literal_eval(expr->condition.literal);
            condition = RT_ACC_DATA;
            break;
        case EXPR_TYPE_IDENTIFIER:
            rt_Identifier_eval(expr->condition.variable);
            condition = RT_ACC_DATA;
            break;
        case EXPR_TYPE_NULL: break;
    }

    switch (expr->op) {
        case LEXTOK_BANG:
        case LEXTOK_LOGICAL_UNEQUAL:
        case LEXTOK_PERCENT:
        case LEXTOK_MODULO_ASSIGN:
        case LEXTOK_AMPERSAND:
        case LEXTOK_LOGICAL_AND:
        case LEXTOK_LOGICAL_AND_ASSIGN:
        case LEXTOK_BITWISE_AND_ASSIGN:
        case LEXTOK_ASTERIX:
        case LEXTOK_EXPONENT:
        case LEXTOK_EXPONENT_ASSIGN:
        case LEXTOK_MULTIPLY_ASSIGN:
        case LEXTOK_PLUS:
        case LEXTOK_INCREMENT:
            rt_throw("unary increment operator is not yet supported");
            break;
        case LEXTOK_ADD_ASSIGN:
        case LEXTOK_MINUS:
        case LEXTOK_DECREMENT:
            rt_throw("unary decrement operator is not yet supported");
            break;
        case LEXTOK_SUBSTRACT_ASSIGN:
        case LEXTOK_DOT:
            rt_throw("memebership operator '.' is not yet supported");
            break;
        case LEXTOK_FSLASH:
        case LEXTOK_FLOOR_DIVIDE:
        case LEXTOK_FLOOR_DIVIDE_ASSIGN:
        case LEXTOK_DIVIDE_ASSIGN:
        case LEXTOK_DCOLON:
            rt_throw("memebership operator '::' is not yet supported");
            break;
        case LEXTOK_LBRACE_ANGULAR:
        case LEXTOK_BITWISE_LSHIFT:
        case LEXTOK_BITWISE_LSHIFT_ASSIGN:
        case LEXTOK_LOGICAL_LESSER_EQUAL:
        case LEXTOK_ASSIGN:
            RT_VarTable_acc_setval(*RT_VarTable_modf(lhs, *rhs));
            break;
        case LEXTOK_LOGICAL_EQUAL:
        case LEXTOK_RBRACE_ANGULAR:
        case LEXTOK_LOGICAL_GREATER_EQUAL:
        case LEXTOK_BITWISE_RSHIFT:
        case LEXTOK_BITWISE_RSHIFT_ASSIGN:
        case LEXTOK_ARITH_RSHIFT:
        case LEXTOK_ARITH_RSHIFT_ASSIGN:
        case LEXTOK_CARET:
        case LEXTOK_BITWISE_XOR_ASSIGN:
        case LEXTOK_PIPE:
        case LEXTOK_BITWISE_OR_ASSIGN:
        case LEXTOK_LOGICAL_OR:
        case LEXTOK_LOGICAL_OR_ASSIGN:
        case LEXTOK_TILDE:
        case TOKOP_FNCALL: break;
        case TOKOP_INDEXING:
        case TOKOP_TERNARY_COND:
        case TOKOP_FNARGS_INDEXING:
            if (!rhs || rhs->type != RT_DATA_TYPE_I64)
                rt_throw("argument index should evaluate to an `i64`");
            RT_VarTable_acc_setadr(
                RT_VarTable_getref_tmpvar(rhs->data.i64));
            break;
        case TOKOP_NOP:
            RT_VarTable_acc_setval(*lhs);
            break;
        /* stuff that doesn't form an operation */
        default:
            io_errndie("rt_Expression_eval: invalid operation '%s'", lex_get_tokcode(expr->op));
    }
}

void rt_Literal_eval(const AST_Literal_t *literal)
{
    if (!literal) return;
    switch (literal->type) {
        case DATA_TYPE_BUL:
            RT_VarTable_acc_setval(
                RT_Data_bul(literal->data.bul));
            break;
        case DATA_TYPE_CHR:
            RT_VarTable_acc_setval(
                RT_Data_chr(literal->data.chr));
            break;
        case DATA_TYPE_I64:
            RT_VarTable_acc_setval(
                RT_Data_i64(literal->data.i64));
            break;
        case DATA_TYPE_F64:
            RT_VarTable_acc_setval(
                RT_Data_f64(literal->data.f64));
            break;
        case DATA_TYPE_STR:
            RT_VarTable_acc_setval(
                RT_Data_str(
                    RT_DataStr_init(literal->data.str)));
            break;
        case DATA_TYPE_INTERP_STR:
            RT_VarTable_acc_setval(
                RT_Data_interp_str(literal->data.str));
            break;
        case DATA_TYPE_LST:
            rt_CommaSepList_eval(literal->data.lst);
            break;
        case DATA_TYPE_ANY:
            /* void* must be explicitly casted */
            RT_VarTable_acc_setval(
                RT_Data_any((void*) literal->data.any));
            break;
    }
}

void rt_Identifier_eval(const AST_Identifier_t *identifier)
{
    if (!identifier) return;
    RT_VarTable_acc_setadr(
        RT_VarTable_getref(identifier->identifier_name));
}

void rt_CommaSepList_eval(const AST_CommaSepList_t *comma_list)
{
    if (!comma_list) return;
    const AST_CommaSepList_t *ptr = comma_list;
    RT_DataList_t *new_list = RT_DataList_init();
    while (ptr) {
        rt_Expression_eval(ptr->expression);
        RT_DataList_append(new_list, *RT_ACC_DATA);
        ptr = ptr->comma_list;
    }
    RT_VarTable_acc_setval(
        RT_Data_list(new_list));
}

void rt_fncall_handler(const AST_Identifier_t *module, const AST_Identifier_t *proc)
{
    const AST_Statements_t *code = AST_ProcedureMap_get_code(module, proc);
    if (code) {
        RT_VarTable_push_proc(proc->identifier_name, NULL);
        rt_Statements_eval(code);
        RT_VarTable_pop_proc();
        return;
    }
    /* attempt to call in built function */
    FN_FunctionDescriptor_t fn = FN_FunctionsList_getfn(proc->identifier_name);
    if (fn == FN_UNDEFINED)
        rt_throw("undefined procedure '%s::%s'", module->identifier_name, proc->identifier_name);
    RT_VarTable_acc_setval(FN_FunctionsList_call(fn));
}
