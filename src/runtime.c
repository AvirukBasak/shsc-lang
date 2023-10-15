#include <inttypes.h>
#include <stdbool.h>

#include "ast.h"
#include "ast/api.h"
#include "runtime.h"
#include "ast/nodes/enums.h"
#include "ast/util/ModuleAndProcTable.h"
#include "functions.h"
#include "lexer.h"
#include "parser.yy.h"
#include "runtime/data/Data.h"
#include "runtime/data/DataList.h"
#include "runtime/data/DataStr.h"
#include "runtime/data/DataMap.h"
#include "runtime/io.h"
#include "runtime/VarTable.h"

#include "runtime/data/Data.c.h"
#include "runtime/io.c.h"
#include "runtime/VarTable.c.h"

typedef enum {
    rt_CTRL_PASS,
    rt_CTRL_RETURN,
    rt_CTRL_BREAK,
    rt_CTRL_CONTINUE,
} rt_ControlStatus_t;

const char *rt_currfile = NULL;
int rt_currline = 0;

const ast_Identifier_t *rt_current_module = NULL;
const ast_Identifier_t *rt_current_proc = NULL;

rt_ControlStatus_t rt_Statements_eval(const ast_Statements_t *code);
rt_ControlStatus_t rt_Statements_newscope_eval(const ast_Statements_t *code);
rt_ControlStatus_t rt_Statement_eval(const ast_Statement_t *statement);
void rt_Assignment_eval(const ast_Assignment_t *assignment);
rt_ControlStatus_t rt_CompoundSt_eval(const ast_CompoundSt_t *compound_st);
rt_ControlStatus_t rt_IfBlock_eval(const ast_IfBlock_t *if_block);
rt_ControlStatus_t rt_ElseBlock_eval(const ast_ElseBlock_t *else_block);
rt_ControlStatus_t rt_WhileBlock_eval(const ast_WhileBlock_t *while_block);
rt_ControlStatus_t rt_ForBlock_eval(const ast_ForBlock_t *for_block);
void rt_Expression_eval(const ast_Expression_t *expr);
void rt_CommaSepList_eval(const ast_CommaSepList_t *comma_list);
void rt_AssociativeList_eval(const ast_AssociativeList_t *assoc_list);
void rt_Literal_eval(const ast_Literal_t *literal);
void rt_Identifier_eval(const ast_Identifier_t *identifier);

void rt_fncall_handler(const ast_Identifier_t *module, const ast_Identifier_t *proc);

void rt_exec(void)
{
    const ast_Identifier_t *module = ast_util_ModuleAndProcTable_idfmain();
    const ast_Identifier_t *proc = ast_util_ModuleAndProcTable_idfmain();
    const ast_Statements_t *code = ast_util_ModuleAndProcTable_get_code(module, proc);
    rt_currfile = ast_util_ModuleAndProcTable_get_filename(module, proc);
    rt_VarTable_push_proc(proc->identifier_name);
    rt_ControlStatus_t ctrl = rt_Statements_eval(code);
    if (ctrl == rt_CTRL_BREAK)
        rt_throw("unexpected `break` statement outside loop");
    if (ctrl == rt_CTRL_CONTINUE)
        rt_throw("unexpected `continue` statement outside loop");
    rt_VarTable_pop_proc();
}

const ast_Identifier_t *rt_modulename_get(void)
{
    if (!rt_current_module) rt_current_module = ast_util_ModuleAndProcTable_idfmain();
    return rt_current_module;
}

const ast_Identifier_t *rt_procname_get(void)
{
    if (!rt_current_module) rt_current_module = ast_util_ModuleAndProcTable_idfmain();
    return rt_current_module;
}

rt_ControlStatus_t rt_Statements_eval(const ast_Statements_t *code)
{
    if (!code) return rt_CTRL_PASS;
    const ast_Statements_t *ptr = code;
    while (ptr) {
        rt_ControlStatus_t ctrl = rt_Statement_eval(ptr->statement);
        if (ctrl != rt_CTRL_PASS) return ctrl;
        ptr = ptr->statements;
    }
    return rt_CTRL_PASS;
}

rt_ControlStatus_t rt_Statements_newscope_eval(const ast_Statements_t *code)
{
    if (!code) return rt_CTRL_PASS;
    rt_VarTable_push_scope();
    rt_ControlStatus_t ctrl = rt_Statements_eval(code);
    rt_VarTable_pop_scope();
    return ctrl;
}

rt_ControlStatus_t rt_Statement_eval(const ast_Statement_t *statement)
{
    if (!statement) return rt_CTRL_PASS;
    rt_currline = statement->line_no;
    switch (statement->type) {
        case STATEMENT_TYPE_EMPTY:
            return rt_CTRL_PASS;
        case STATEMENT_TYPE_BREAK:
            return rt_CTRL_BREAK;
        case STATEMENT_TYPE_CONTINUE:
            return rt_CTRL_CONTINUE;
        case STATEMENT_TYPE_RETURN:
            rt_Expression_eval(statement->statement.expression);
            return rt_CTRL_RETURN;
        case STATEMENT_TYPE_ASSIGNMENT:
            rt_Assignment_eval(statement->statement.assignment);
            break;
        case STATEMENT_TYPE_COMPOUND:
            return rt_CompoundSt_eval(statement->statement.compound_statement);
    }
    return rt_CTRL_PASS;
}

void rt_Assignment_eval(const ast_Assignment_t *assignment)
{
    if (!assignment) return;
    switch (assignment->type) {
        case ASSIGNMENT_TYPE_TOVOID:
            rt_Expression_eval(assignment->rhs);
            break;
        case ASSIGNMENT_TYPE_CREATE: {
            const char *idf = assignment->lhs->identifier_name;
            rt_Expression_eval(assignment->rhs);
            rt_VarTable_create(idf, *rt_ACC_DATA);
            break;
        }
    }
}

rt_ControlStatus_t rt_CompoundSt_eval(const ast_CompoundSt_t *compound_st)
{
    if (!compound_st) return rt_CTRL_PASS;
    switch (compound_st->type) {
        case COMPOUNDST_TYPE_IF:
            return rt_IfBlock_eval(compound_st->compound_statement.if_block);
        case COMPOUNDST_TYPE_WHILE:
            return rt_WhileBlock_eval(compound_st->compound_statement.while_block);
        case COMPOUNDST_TYPE_FOR:
            return rt_ForBlock_eval(compound_st->compound_statement.for_block);
        case COMPOUNDST_TYPE_BLOCK:
            return rt_Statements_newscope_eval(compound_st->compound_statement.block->statements);
    }
    return rt_CTRL_PASS;
}

rt_ControlStatus_t rt_IfBlock_eval(const ast_IfBlock_t *if_block)
{
    if (!if_block) return rt_CTRL_PASS;
    rt_Expression_eval(if_block->condition);
    bool cond = rt_Data_tobool(*rt_ACC_DATA);
    if (cond) return rt_Statements_newscope_eval(if_block->if_st);
    else return rt_ElseBlock_eval(if_block->else_block);
}

rt_ControlStatus_t rt_ElseBlock_eval(const ast_ElseBlock_t *else_block)
{
    if (!else_block) return rt_CTRL_PASS;
    /* takes care of [ else nwp statements end ] */
    if (!else_block->condition && !else_block->else_block) {
        return rt_Statements_newscope_eval(else_block->else_if_st);
    }
    /* takes care of [ else if condition then nwp statements ] */
    rt_Expression_eval(else_block->condition);
    bool cond = rt_Data_tobool(*rt_ACC_DATA);
    if (cond) return rt_Statements_newscope_eval(else_block->else_if_st);
    else return rt_ElseBlock_eval(else_block->else_block);
}

rt_ControlStatus_t rt_WhileBlock_eval(const ast_WhileBlock_t *while_block)
{
    if (!while_block) return rt_CTRL_PASS;
    rt_Expression_eval(while_block->condition);
    bool cond = rt_Data_tobool(*rt_ACC_DATA);
    while (cond) {
        rt_ControlStatus_t ctrl = rt_Statements_newscope_eval(while_block->statements);
        if (ctrl == rt_CTRL_PASS)
            /* do nothing in pass */;
        if (ctrl == rt_CTRL_RETURN)   return ctrl;
        if (ctrl == rt_CTRL_BREAK)    break;
        if (ctrl == rt_CTRL_CONTINUE) continue;
    }
    return rt_CTRL_PASS;
}

rt_ControlStatus_t rt_ForBlock_eval(const ast_ForBlock_t *for_block)
{
    if (!for_block) return rt_CTRL_PASS;
    switch (for_block->type) {
        case FORBLOCK_TYPE_RANGE: {
            /* calculate start, end and by */
            rt_Expression_eval(for_block->it.range.start);
            rt_Data_t start = *rt_ACC_DATA;
            if (start.type != rt_DATA_TYPE_I64)
                rt_throw("for loop range start should be an i64, not '%s'", rt_Data_typename(start));
            rt_Expression_eval(for_block->it.range.end);
            rt_Data_t end = *rt_ACC_DATA;
            if (end.type != rt_DATA_TYPE_I64)
                rt_throw("for loop range end should be an i64, not '%s'", rt_Data_typename(start));
            rt_Data_t by = rt_Data_null();
            if (for_block->it.range.by) {
                rt_Expression_eval(for_block->it.range.by);
                by = *rt_ACC_DATA;
                if (by.type != rt_DATA_TYPE_I64)
                    rt_throw("for loop by value should be an i64, not '%s'", rt_Data_typename(start));
            }
            const int64_t start_i = start.data.i64;
            const int64_t end_i = end.data.i64;
            const int64_t by_i = rt_Data_isnull(by) ?
                (start_i <= end_i ? +1 : -1) : by.data.i64;
            if (!by_i) rt_throw("for loop by value cannot be 0");
            if ( (start_i < end_i && by_i < 0) || (start_i > end_i && by_i > 0) )
                rt_throw("possible infinite for loop for by value '%" PRId64 "'", by_i);
            /* start for loop */
            for (int64_t i = start_i;
                    (start_i <= end_i && i < end_i) || i > end_i; i += by_i) {
                rt_VarTable_push_scope();
                rt_VarTable_create(for_block->val->identifier_name,
                    rt_Data_i64(i));
                rt_ControlStatus_t ctrl = rt_Statements_eval(for_block->statements);
                rt_VarTable_pop_scope();
                if (ctrl == rt_CTRL_PASS)
                    /* do nothing in pass */;
                if (ctrl == rt_CTRL_RETURN)   return ctrl;
                if (ctrl == rt_CTRL_BREAK)    break;
                if (ctrl == rt_CTRL_CONTINUE) continue;
            }
            break;
        }
        case FORBLOCK_TYPE_LIST: {
            /* convert expression to a data list */
            rt_Expression_eval(for_block->it.iterable);
            rt_Data_t iterable = *rt_ACC_DATA;
            rt_Data_copy(&iterable);
            int64_t length = 0;
            switch (iterable.type) {
                case rt_DATA_TYPE_LST:
                    length = rt_DataList_length(iterable.data.lst);
                    break;
                case rt_DATA_TYPE_STR:
                    length = rt_DataStr_length(iterable.data.str);
                    break;
                case rt_DATA_TYPE_MAP:
                    length = rt_DataMap_length(iterable.data.mp);
                    break;
                default:
                    rt_throw("not a for loop iterable type: '%s'", rt_Data_typename(iterable));
            }
            if (iterable.type == rt_DATA_TYPE_MAP) {
                for (rt_DataMap_iter_t entry_it = rt_DataMap_begin(iterable.data.mp);
                        entry_it != rt_DataMap_end(iterable.data.mp); ++entry_it) {
                    if (!rt_DataMap_exists(iterable.data.mp, entry_it)) continue;
                    rt_DataMapEntry_t entry = *rt_DataMap_get(iterable.data.mp, entry_it);
                    rt_VarTable_push_scope();
                    if (for_block->idx) rt_VarTable_create(for_block->idx->identifier_name,
                        rt_Data_str(rt_DataStr_init(entry.key)));
                    rt_VarTable_create(for_block->val->identifier_name, entry.value);
                    rt_ControlStatus_t ctrl = rt_Statements_eval(for_block->statements);
                    rt_VarTable_pop_scope();
                    if (ctrl == rt_CTRL_PASS)
                        /* do nothing in pass */;
                    if (ctrl == rt_CTRL_RETURN)   return ctrl;
                    if (ctrl == rt_CTRL_BREAK)    break;
                    if (ctrl == rt_CTRL_CONTINUE) continue;
                }
            } else for (int64_t i = 0; i < length; ++i) {
                rt_VarTable_push_scope();
                switch (iterable.type) {
                    case rt_DATA_TYPE_LST:
                        if (for_block->idx) rt_VarTable_create(for_block->idx->identifier_name,
                            rt_Data_i64(i));
                        rt_VarTable_create(for_block->val->identifier_name,
                            *rt_DataList_getref(iterable.data.lst, i));
                        break;
                    case rt_DATA_TYPE_STR:
                        if (for_block->idx) rt_VarTable_create(for_block->idx->identifier_name,
                            rt_Data_i64(i));
                        rt_VarTable_create(for_block->val->identifier_name,
                            rt_Data_chr(*rt_DataStr_getref(iterable.data.str, i)));
                        break;
                    default:
                        rt_throw("not a for loop iterable type: '%s'", rt_Data_typename(iterable));
                }
                rt_ControlStatus_t ctrl = rt_Statements_eval(for_block->statements);
                rt_VarTable_pop_scope();
                if (ctrl == rt_CTRL_PASS)
                    /* do nothing in pass */;
                if (ctrl == rt_CTRL_RETURN)   return ctrl;
                if (ctrl == rt_CTRL_BREAK)    break;
                if (ctrl == rt_CTRL_CONTINUE) continue;
            }
            /* destroy iterable object */
            rt_Data_destroy(&iterable);
            break;
        }
    }
    return rt_CTRL_PASS;
}

void rt_Expression_eval(const ast_Expression_t *expr)
{
    if (!expr) {
        rt_VarTable_acc_setval(rt_Data_null());
        return;
    }
    /* take care pf fn calls and membership operations */
    switch (expr->op) {
        case TOKEN_DOT:
            rt_throw("unimplemented operators");
            break;
        case TOKEN_DCOLON: {
            if (expr->lhs_type != EXPR_TYPE_IDENTIFIER
                || expr->rhs_type != EXPR_TYPE_IDENTIFIER)
                    rt_throw("invalid use of module membership operator");
            /* instead of evaluating the lhs and RHS, directly generate a
               procedure type literal and return it via accumulator */
            rt_VarTable_acc_setval((rt_Data_t) {
                .data.proc = {
                    .modulename = expr->lhs.variable,
                    .procname = expr->rhs.variable,
                },
                .type = rt_DATA_TYPE_PROC
            });
            return;
        }
        default: break;
    }

    /* handle lhs and evaluate it */
    rt_Data_t lhs_, *lhs = NULL;

    /* during function call, if lhs is a single identifier only
       then skip normal lhs evaluation to prevent conflict with
       rt_VarTable_getref during identifier value resolution */
    if (expr->op == TOKOP_FNCALL && expr->lhs_type == EXPR_TYPE_IDENTIFIER) {
        rt_VarTable_acc_setval((rt_Data_t) {
            .data.proc = {
                .modulename = rt_modulename_get(),
                .procname = expr->lhs.variable,
            },
            .type = rt_DATA_TYPE_PROC
        });
        /* copy accumulator value into temporary memory as accumulator gets
           modified when evaluating other operands */
        lhs_ = *rt_ACC_DATA;
        lhs = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &lhs_;
        goto rt_Expression_eval_skip_lhs_eval;
    }

    switch (expr->lhs_type) {
        case EXPR_TYPE_EXPRESSION:
            rt_Expression_eval(expr->lhs.expr);
            /* copy accumulator value into temporary memory as accumulator gets
               modified when evaluating other operands */
            lhs_ = *rt_ACC_DATA;
            lhs = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &lhs_;
            break;
        case EXPR_TYPE_LITERAL:
            rt_Literal_eval(expr->lhs.literal);
            lhs_ = *rt_ACC_DATA;
            lhs = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &lhs_;
            break;
        case EXPR_TYPE_IDENTIFIER:
            rt_Identifier_eval(expr->lhs.variable);
            lhs_ = *rt_ACC_DATA;
            lhs = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &lhs_;
            break;
        case EXPR_TYPE_NULL: break;
    }

    /* handle rhs and evaluate it */
    rt_Data_t rhs_, *rhs = NULL;
rt_Expression_eval_skip_lhs_eval:
    switch (expr->rhs_type) {
        case EXPR_TYPE_EXPRESSION:
            rt_Expression_eval(expr->rhs.expr);
            rhs_ = *rt_ACC_DATA;
            rhs = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &rhs_;
            break;
        case EXPR_TYPE_LITERAL:
            rt_Literal_eval(expr->rhs.literal);
            rhs_ = *rt_ACC_DATA;
            rhs = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &rhs_;
            break;
        case EXPR_TYPE_IDENTIFIER:
            rt_Identifier_eval(expr->rhs.variable);
            rhs_ = *rt_ACC_DATA;
            rhs = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &rhs_;
            break;
        case EXPR_TYPE_NULL: break;
    }

    /* handle condition and evaluate it */
    rt_Data_t condition_, *condition = NULL;
rt_Expression_eval_skip_lhs_and_rhs_eval:
    switch (expr->condition_type) {
        case EXPR_TYPE_EXPRESSION:
            rt_Expression_eval(expr->condition.expr);
            condition_ = *rt_ACC_DATA;
            condition = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &condition_;
            break;
        case EXPR_TYPE_LITERAL:
            rt_Literal_eval(expr->condition.literal);
            condition_ = *rt_ACC_DATA;
            condition = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &condition_;
            break;
        case EXPR_TYPE_IDENTIFIER:
            rt_Identifier_eval(expr->condition.variable);
            condition_ = *rt_ACC_DATA;
            condition = rt_VarTable_acc_get()->adr ? rt_VarTable_acc_get()->adr : &condition_;
            break;
        case EXPR_TYPE_NULL: break;
    }

rt_Expression_eval_skip_all_3_operands_eval:
    switch (expr->op) {
        case TOKEN_BANG:
        case TOKEN_LOGICAL_UNEQUAL:
        case TOKEN_PERCENT:
        case TOKEN_MODULO_ASSIGN:
        case TOKEN_AMPERSAND:
        case TOKEN_LOGICAL_AND:
        case TOKEN_LOGICAL_AND_ASSIGN:
        case TOKEN_BITWISE_AND_ASSIGN:
        case TOKEN_ASTERIX:
        case TOKEN_EXPONENT:
        case TOKEN_EXPONENT_ASSIGN:
        case TOKEN_MULTIPLY_ASSIGN:
        case TOKEN_PLUS:
        case TOKEN_INCREMENT:
        case TOKEN_ADD_ASSIGN:
        case TOKEN_MINUS:
        case TOKEN_DECREMENT:
        case TOKEN_SUBSTRACT_ASSIGN:
            rt_throw("unimplemented operators");
            break;
        case TOKEN_DOT:
            rt_throw("memebership operator '.' is not yet supported");
            break;
        case TOKEN_FSLASH:
        case TOKEN_FLOOR_DIVIDE:
        case TOKEN_FLOOR_DIVIDE_ASSIGN:
        case TOKEN_DIVIDE_ASSIGN:
        case TOKEN_DCOLON:
        case TOKEN_LBRACE_ANGULAR:
        case TOKEN_BITWISE_LSHIFT:
        case TOKEN_BITWISE_LSHIFT_ASSIGN:
        case TOKEN_LOGICAL_LESSER_EQUAL:
            rt_throw("unimplemented operators");
            break;
        case TOKEN_ASSIGN:
            rt_VarTable_acc_setval(*rt_VarTable_modf(lhs, *rhs));
            break;
        case TOKEN_LOGICAL_EQUAL:
        case TOKEN_RBRACE_ANGULAR:
        case TOKEN_LOGICAL_GREATER_EQUAL:
        case TOKEN_BITWISE_RSHIFT:
        case TOKEN_BITWISE_RSHIFT_ASSIGN:
        case TOKEN_ARITH_RSHIFT:
        case TOKEN_ARITH_RSHIFT_ASSIGN:
        case TOKEN_CARET:
        case TOKEN_BITWISE_XOR_ASSIGN:
        case TOKEN_PIPE:
        case TOKEN_BITWISE_OR_ASSIGN:
        case TOKEN_LOGICAL_OR:
        case TOKEN_LOGICAL_OR_ASSIGN:
        case TOKEN_TILDE:
            rt_throw("unimplemented operators");
            break;
        case TOKOP_FNCALL: {
            if (lhs->type != rt_DATA_TYPE_PROC)
                rt_throw("cannot make procedure call to type '%s'", rt_Data_typename(*lhs));
            if (!rhs) {
                rhs_ = rt_Data_list(rt_DataList_init());
                rhs = &rhs_;
            }
            if (rhs->type != rt_DATA_TYPE_LST)
                rt_throw("cannot pass type '%s' as procedure argument", rt_Data_typename(*rhs));
            /* copy fn args into temporary location */
            rt_VarTable_modf(rt_VarTable_getref("$"), *rhs);
            /* get fn code and push code to stack */
            rt_fncall_handler(lhs->data.proc.modulename, lhs->data.proc.procname);
            /* set no data to accumulator as data is already set by procedure called above
               return early to prevent accumulator being modified by some other code */
            return;
        }
        case TOKOP_INDEXING:
        case TOKOP_TERNARY_COND:
            rt_throw("unimplemented operators");
            break;
        case TOKOP_FNARGS_INDEXING: {
            if (!rhs || rhs->type != rt_DATA_TYPE_I64)
                rt_throw("argument index should evaluate to an `i64`");
            rt_Data_t args = *rt_VarTable_getref("$");
            if (args.type != rt_DATA_TYPE_LST)
                io_errndie("rt_Expression_eval: TOKOP_FNARGS_INDEXING: "
                           "received arguments list as type '%s'", rt_Data_typename(args));
            rt_VarTable_acc_setadr(
                rt_DataList_getref(args.data.lst, rhs->data.i64));
            break;
        }
        case TOKOP_NOP:
            rt_VarTable_acc_setval(*lhs);
            break;
        /* stuff that doesn't form an operation */
        default:
            io_errndie("rt_Expression_eval: invalid operation '%s'",
                lex_Token_getcode(expr->op));
    }
}

void rt_Literal_eval(const ast_Literal_t *literal)
{
    if (!literal) {
        rt_VarTable_acc_setval(rt_Data_null());
        return;
    }
    switch (literal->type) {
        case DATA_TYPE_BUL:
            rt_VarTable_acc_setval(
                rt_Data_bul(literal->data.bul));
            break;
        case DATA_TYPE_CHR:
            rt_VarTable_acc_setval(
                rt_Data_chr(literal->data.chr));
            break;
        case DATA_TYPE_I64:
            rt_VarTable_acc_setval(
                rt_Data_i64(literal->data.i64));
            break;
        case DATA_TYPE_F64:
            rt_VarTable_acc_setval(
                rt_Data_f64(literal->data.f64));
            break;
        case DATA_TYPE_STR:
            rt_VarTable_acc_setval(
                rt_Data_str(
                    rt_DataStr_init(literal->data.str)));
            break;
        case DATA_TYPE_INTERP_STR:
            rt_VarTable_acc_setval(
                rt_Data_interp_str(literal->data.str));
            break;
        case DATA_TYPE_LST:
            rt_CommaSepList_eval(literal->data.lst);
            break;
        case DATA_TYPE_MAP:
            rt_AssociativeList_eval(literal->data.mp);
            break;
        case DATA_TYPE_ANY:
            /* void* must be explicitly casted */
            rt_VarTable_acc_setval(
                rt_Data_any((void*) literal->data.any));
            break;
    }
}

void rt_Identifier_eval(const ast_Identifier_t *identifier)
{
    if (!identifier) {
        rt_VarTable_acc_setval(rt_Data_null());
        return;
    }
    rt_VarTable_acc_setadr(
        rt_VarTable_getref(identifier->identifier_name));
}

void rt_CommaSepList_eval(const ast_CommaSepList_t *comma_list)
{
    if (!comma_list) {
        rt_VarTable_acc_setval(rt_Data_null());
        return;
    }
    const ast_CommaSepList_t *ptr = comma_list;
    rt_DataList_t *new_list = rt_DataList_init();
    while (ptr) {
        rt_Expression_eval(ptr->expression);
        rt_DataList_append(new_list, *rt_ACC_DATA);
        ptr = ptr->comma_list;
    }
    rt_VarTable_acc_setval(
        rt_Data_list(new_list));
}

void rt_AssociativeList_eval(const ast_AssociativeList_t *assoc_list)
{
    if (!assoc_list) {
        rt_VarTable_acc_setval(rt_Data_null());
        return;
    }
    const ast_AssociativeList_t *ptr = assoc_list;
    rt_DataMap_t *new_map = rt_DataMap_init();
    while (ptr) {
        rt_Literal_eval(ptr->key);
        char *key_cstr = rt_Data_tostr(*rt_ACC_DATA);
        /* note that the rt_Data_t string returned above is not
           manually cleaned coz it's reference counted l, and is
           freed when accumulator value is changed below */
        rt_Expression_eval(ptr->value);
        rt_DataMap_insert(new_map, key_cstr, *rt_ACC_DATA);
        ptr = ptr->assoc_list;
        free(key_cstr);
    }
    rt_VarTable_acc_setval(
        rt_Data_map(new_map));
}

void rt_fncall_handler(const ast_Identifier_t *module, const ast_Identifier_t *proc)
{
    /* get code as AST from user defined function */
    const ast_Statements_t *code = ast_util_ModuleAndProcTable_get_code(module, proc);
    /* get a descriptor to in-built function */
    const fn_FunctionDescriptor_t fn = fn_FunctionsList_getfn(
        module->identifier_name, proc->identifier_name);
    /* backup metadata on current module and function */
    const char *currfile_bkp = rt_currfile;
    const ast_Identifier_t *currmodule_bkp = rt_current_module;
    const ast_Identifier_t *currproc_bkp = rt_current_proc;
    /* update metadata to new module and function */
    if (code) {
        rt_currfile = ast_util_ModuleAndProcTable_get_filename(module, proc);
        rt_current_module = module;
        rt_current_proc = proc;
    } else if (fn != fn_UNDEFINED) {
        rt_currfile = "<built-in>";
        rt_current_module = module;
        rt_current_proc = proc;
    }
    if (code) {
        /* call user defined function */
        rt_VarTable_push_proc(proc->identifier_name);
        rt_Statements_eval(code);
        rt_VarTable_pop_proc();
    } else {
        /* attempt to call in-built function */
        if (fn == fn_UNDEFINED)
            rt_throw("undefined procedure '%s:%s'",
                module->identifier_name, proc->identifier_name);
        rt_VarTable_acc_setval(fn_FunctionsList_call(fn));
    }
    /* restore metadata to previous module and function */
    rt_currfile = currfile_bkp;
    rt_current_module = currmodule_bkp;
    rt_current_proc = currproc_bkp;
}
