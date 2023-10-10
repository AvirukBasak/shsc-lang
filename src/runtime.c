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
#include "runtime/data/map.h"
#include "runtime/io.h"
#include "runtime/vartable.h"

#include "runtime/data.c.h"
#include "runtime/io.c.h"
#include "runtime/vartable.c.h"

typedef enum {
    RT_CTRL_PASS,
    RT_CTRL_RETURN,
    RT_CTRL_BREAK,
    RT_CTRL_CONTINUE,
} rt_ControlStatus_t;

const char *rt_currfile = NULL;
int rt_currline = 0;

const AST_Identifier_t *rt_current_module = NULL;
const AST_Identifier_t *rt_current_proc = NULL;

const AST_Identifier_t *rt_modulename_get(void);
const AST_Identifier_t *rt_procname_get(void);

rt_ControlStatus_t rt_Statements_eval(const AST_Statements_t *code);
rt_ControlStatus_t rt_Statements_newscope_eval(const AST_Statements_t *code);
rt_ControlStatus_t rt_Statement_eval(const AST_Statement_t *statement);
void rt_Assignment_eval(const AST_Assignment_t *assignment);
rt_ControlStatus_t rt_CompoundSt_eval(const AST_CompoundSt_t *compound_st);
rt_ControlStatus_t rt_IfBlock_eval(const AST_IfBlock_t *if_block);
rt_ControlStatus_t rt_ElseBlock_eval(const AST_ElseBlock_t *else_block);
rt_ControlStatus_t rt_WhileBlock_eval(const AST_WhileBlock_t *while_block);
rt_ControlStatus_t rt_ForBlock_eval(const AST_ForBlock_t *for_block);
void rt_Expression_eval(const AST_Expression_t *expr);
void rt_CommaSepList_eval(const AST_CommaSepList_t *comma_list);
void rt_AssociativeList_eval(const AST_AssociativeList_t *assoc_list);
void rt_Literal_eval(const AST_Literal_t *literal);
void rt_Identifier_eval(const AST_Identifier_t *identifier);

void rt_fncall_handler(const AST_Identifier_t *module, const AST_Identifier_t *proc);

void RT_exec(void)
{
    const AST_Identifier_t *module = AST_ProcedureMap_main();
    const AST_Identifier_t *proc = AST_ProcedureMap_main();
    const AST_Statements_t *code = AST_ProcedureMap_get_code(module, proc);
    rt_currfile = AST_ProcedureMap_get_filename(module, proc);
    RT_VarTable_push_proc(proc->identifier_name);
    rt_ControlStatus_t ctrl = rt_Statements_eval(code);
    if (ctrl == RT_CTRL_BREAK)
        rt_throw("unexpected `break` statement outside loop");
    if (ctrl == RT_CTRL_CONTINUE)
        rt_throw("unexpected `continue` statement outside loop");
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

rt_ControlStatus_t rt_Statements_eval(const AST_Statements_t *code)
{
    if (!code) return RT_CTRL_PASS;
    const AST_Statements_t *ptr = code;
    while (ptr) {
        rt_ControlStatus_t ctrl = rt_Statement_eval(ptr->statement);
        if (ctrl != RT_CTRL_PASS) return ctrl;
        ptr = ptr->statements;
    }
    return RT_CTRL_PASS;
}

rt_ControlStatus_t rt_Statements_newscope_eval(const AST_Statements_t *code)
{
    if (!code) return RT_CTRL_PASS;
    RT_VarTable_push_scope();
    rt_ControlStatus_t ctrl = rt_Statements_eval(code);
    RT_VarTable_pop_scope();
    return ctrl;
}

rt_ControlStatus_t rt_Statement_eval(const AST_Statement_t *statement)
{
    if (!statement) return RT_CTRL_PASS;
    rt_currline = statement->line_no;
    switch (statement->type) {
        case STATEMENT_TYPE_EMPTY:
            return RT_CTRL_PASS;
        case STATEMENT_TYPE_BREAK:
            return RT_CTRL_BREAK;
        case STATEMENT_TYPE_CONTINUE:
            return RT_CTRL_CONTINUE;
        case STATEMENT_TYPE_RETURN:
            rt_Expression_eval(statement->statement.expression);
            return RT_CTRL_RETURN;
        case STATEMENT_TYPE_ASSIGNMENT:
            rt_Assignment_eval(statement->statement.assignment);
            break;
        case STATEMENT_TYPE_COMPOUND:
            return rt_CompoundSt_eval(statement->statement.compound_statement);
    }
    return RT_CTRL_PASS;
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

rt_ControlStatus_t rt_CompoundSt_eval(const AST_CompoundSt_t *compound_st)
{
    if (!compound_st) return RT_CTRL_PASS;
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
    return RT_CTRL_PASS;
}

rt_ControlStatus_t rt_IfBlock_eval(const AST_IfBlock_t *if_block)
{
    if (!if_block) return RT_CTRL_PASS;
    rt_Expression_eval(if_block->condition);
    bool cond = RT_Data_tobool(*RT_ACC_DATA);
    if (cond) return rt_Statements_newscope_eval(if_block->if_st);
    else return rt_ElseBlock_eval(if_block->else_block);
}

rt_ControlStatus_t rt_ElseBlock_eval(const AST_ElseBlock_t *else_block)
{
    if (!else_block) return RT_CTRL_PASS;
    /* takes care of [ else nwp statements end ] */
    if (!else_block->condition && !else_block->else_block) {
        return rt_Statements_newscope_eval(else_block->else_if_st);
    }
    /* takes care of [ else if condition then nwp statements ] */
    rt_Expression_eval(else_block->condition);
    bool cond = RT_Data_tobool(*RT_ACC_DATA);
    if (cond) return rt_Statements_newscope_eval(else_block->else_if_st);
    else return rt_ElseBlock_eval(else_block->else_block);
}

rt_ControlStatus_t rt_WhileBlock_eval(const AST_WhileBlock_t *while_block)
{
    if (!while_block) return RT_CTRL_PASS;
    rt_Expression_eval(while_block->condition);
    bool cond = RT_Data_tobool(*RT_ACC_DATA);
    while (cond) {
        rt_ControlStatus_t ctrl = rt_Statements_newscope_eval(while_block->statements);
        if (ctrl == RT_CTRL_PASS)
            /* do nothing in pass */;
        if (ctrl == RT_CTRL_RETURN)   return ctrl;
        if (ctrl == RT_CTRL_BREAK)    break;
        if (ctrl == RT_CTRL_CONTINUE) continue;
    }
    return RT_CTRL_PASS;
}

rt_ControlStatus_t rt_ForBlock_eval(const AST_ForBlock_t *for_block)
{
    if (!for_block) return RT_CTRL_PASS;
    switch (for_block->type) {
        case FORBLOCK_TYPE_RANGE: {
            /* calculate start, end and by */
            rt_Expression_eval(for_block->it.range.start);
            RT_Data_t start = *RT_ACC_DATA;
            if (start.type != RT_DATA_TYPE_I64)
                rt_throw("for loop range start should be an i64, not '%s'", RT_Data_typename(start));
            rt_Expression_eval(for_block->it.range.end);
            RT_Data_t end = *RT_ACC_DATA;
            if (end.type != RT_DATA_TYPE_I64)
                rt_throw("for loop range end should be an i64, not '%s'", RT_Data_typename(start));
            RT_Data_t by = RT_Data_null();
            if (for_block->it.range.by) {
                rt_Expression_eval(for_block->it.range.by);
                by = *RT_ACC_DATA;
                if (by.type != RT_DATA_TYPE_I64)
                    rt_throw("for loop by value should be an i64, not '%s'", RT_Data_typename(start));
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
                RT_VarTable_create(for_block->val->identifier_name,
                    RT_Data_i64(i));
                rt_ControlStatus_t ctrl = rt_Statements_eval(for_block->statements);
                RT_VarTable_pop_scope();
                if (ctrl == RT_CTRL_PASS)
                    /* do nothing in pass */;
                if (ctrl == RT_CTRL_RETURN)   return ctrl;
                if (ctrl == RT_CTRL_BREAK)    break;
                if (ctrl == RT_CTRL_CONTINUE) continue;
            }
            break;
        }
        case FORBLOCK_TYPE_LIST: {
            /* convert expression to a data list */
            rt_Expression_eval(for_block->it.iterable);
            RT_Data_t iterable = *RT_ACC_DATA;
            RT_Data_copy(&iterable);
            int64_t length = 0;
            switch (iterable.type) {
                case RT_DATA_TYPE_LST:
                    length = RT_DataList_length(iterable.data.lst);
                    break;
                case RT_DATA_TYPE_STR:
                    length = RT_DataStr_length(iterable.data.str);
                    break;
                case RT_DATA_TYPE_MAP:
                    length = RT_DataMap_length(iterable.data.mp);
                    break;
                default:
                    rt_throw("not a for loop iterable type: '%s'", RT_Data_typename(iterable));
            }
            if (iterable.type == RT_DATA_TYPE_MAP) {
                for (RT_DataMap_iter_t entry_it = RT_DataMap_begin(iterable.data.mp);
                        entry_it != RT_DataMap_end(iterable.data.mp); ++entry_it) {
                    if (!RT_DataMap_exists(iterable.data.mp, entry_it)) continue;
                    RT_DataMapEntry_t entry = *RT_DataMap_get(iterable.data.mp, entry_it);
                    RT_VarTable_push_scope();
                    if (for_block->idx) RT_VarTable_create(for_block->idx->identifier_name,
                        RT_Data_str(RT_DataStr_init(entry.key)));
                    RT_VarTable_create(for_block->val->identifier_name, entry.value);
                    rt_ControlStatus_t ctrl = rt_Statements_eval(for_block->statements);
                    RT_VarTable_pop_scope();
                    if (ctrl == RT_CTRL_PASS)
                        /* do nothing in pass */;
                    if (ctrl == RT_CTRL_RETURN)   return ctrl;
                    if (ctrl == RT_CTRL_BREAK)    break;
                    if (ctrl == RT_CTRL_CONTINUE) continue;
                }
            } else for (int64_t i = 0; i < length; ++i) {
                RT_VarTable_push_scope();
                switch (iterable.type) {
                    case RT_DATA_TYPE_LST:
                        if (for_block->idx) RT_VarTable_create(for_block->idx->identifier_name,
                            RT_Data_i64(i));
                        RT_VarTable_create(for_block->val->identifier_name,
                            *RT_DataList_getref(iterable.data.lst, i));
                        break;
                    case RT_DATA_TYPE_STR:
                        if (for_block->idx) RT_VarTable_create(for_block->idx->identifier_name,
                            RT_Data_i64(i));
                        RT_VarTable_create(for_block->val->identifier_name,
                            RT_Data_chr(*RT_DataStr_getref(iterable.data.str, i)));
                        break;
                    default:
                        rt_throw("not a for loop iterable type: '%s'", RT_Data_typename(iterable));
                }
                rt_ControlStatus_t ctrl = rt_Statements_eval(for_block->statements);
                RT_VarTable_pop_scope();
                if (ctrl == RT_CTRL_PASS)
                    /* do nothing in pass */;
                if (ctrl == RT_CTRL_RETURN)   return ctrl;
                if (ctrl == RT_CTRL_BREAK)    break;
                if (ctrl == RT_CTRL_CONTINUE) continue;
            }
            /* destroy iterable object */
            RT_Data_destroy(&iterable);
            break;
        }
    }
    return RT_CTRL_PASS;
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
            /* create an array for args */
            RT_Data_t args[RT_TMPVAR_CNT];
            /* evaluate fn args and store in args array */
            for (int i = 0; i < RT_TMPVAR_CNT; ++i) {
                RT_Data_t data = RT_Data_null();
                if (ptr) {
                    rt_Expression_eval(ptr->expression);
                    data = *RT_ACC_DATA;
                    /* copy data as acc is overwritten on next iter */
                    RT_Data_copy(&data);
                }
                args[i] = data;
                if (ptr) ptr = ptr->comma_list;
            }
            /* copy fn args into temporary location */
            for (int i = 0; i < RT_TMPVAR_CNT; ++i) {
                RT_VarTable_modf(RT_VarTable_getref_tmpvar(i), args[i]);
                /* destroy data i.e. reduce its ref_count once as it was previously copied */
                RT_Data_destroy(&args[i]);
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
        case LEXTOK_ADD_ASSIGN:
        case LEXTOK_MINUS:
        case LEXTOK_DECREMENT:
        case LEXTOK_SUBSTRACT_ASSIGN:
            rt_throw("unimplemented operators");
            break;
        case LEXTOK_DOT:
            rt_throw("memebership operator '.' is not yet supported");
            break;
        case LEXTOK_FSLASH:
        case LEXTOK_FLOOR_DIVIDE:
        case LEXTOK_FLOOR_DIVIDE_ASSIGN:
        case LEXTOK_DIVIDE_ASSIGN:
        case LEXTOK_DCOLON:
        case LEXTOK_LBRACE_ANGULAR:
        case LEXTOK_BITWISE_LSHIFT:
        case LEXTOK_BITWISE_LSHIFT_ASSIGN:
        case LEXTOK_LOGICAL_LESSER_EQUAL:
            rt_throw("unimplemented operators");
            break;
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
        case TOKOP_FNCALL:
        case TOKOP_INDEXING:
        case TOKOP_TERNARY_COND:
            rt_throw("unimplemented operators");
            break;
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
    if (!literal) {
        RT_VarTable_acc_setval(RT_Data_null());
        return;
    }
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
        case DATA_TYPE_MAP:
            rt_AssociativeList_eval(literal->data.mp);
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
    if (!identifier) {
        RT_VarTable_acc_setval(RT_Data_null());
        return;
    }
    RT_VarTable_acc_setadr(
        RT_VarTable_getref(identifier->identifier_name));
}

void rt_CommaSepList_eval(const AST_CommaSepList_t *comma_list)
{
    if (!comma_list) {
        RT_VarTable_acc_setval(RT_Data_null());
        return;
    }
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

void rt_AssociativeList_eval(const AST_AssociativeList_t *assoc_list)
{
    if (!assoc_list) {
        RT_VarTable_acc_setval(RT_Data_null());
        return;
    }
    const AST_AssociativeList_t *ptr = assoc_list;
    RT_DataMap_t *new_map = RT_DataMap_init();
    while (ptr) {
        rt_Literal_eval(ptr->key);
        char *key_cstr = RT_Data_tostr(*RT_ACC_DATA);
        /* note that the RT_Data_t string returned above is not
           manually cleaned coz it's reference counted l, and is
           freed when accumulator value is changed below */
        rt_Expression_eval(ptr->value);
        RT_DataMap_insert(new_map, key_cstr, *RT_ACC_DATA);
        ptr = ptr->assoc_list;
        free(key_cstr);
    }
    RT_VarTable_acc_setval(
        RT_Data_map(new_map));
}

void rt_fncall_handler(const AST_Identifier_t *module, const AST_Identifier_t *proc)
{
    const AST_Statements_t *code = AST_ProcedureMap_get_code(module, proc);
    if (code) {
        const char *currfile_bkp = rt_currfile;
        const AST_Identifier_t *currmodule_bkp = rt_current_module;
        const AST_Identifier_t *currproc_bkp = rt_current_proc;

        rt_currfile = AST_ProcedureMap_get_filename(module, proc);
        rt_current_module = module;
        rt_current_proc = proc;

        RT_VarTable_push_proc(proc->identifier_name);
        rt_Statements_eval(code);
        RT_VarTable_pop_proc();

        rt_currfile = currfile_bkp;
        rt_current_module = currmodule_bkp;
        rt_current_proc = currproc_bkp;

        return;
    }
    /* attempt to call in built function */
    FN_FunctionDescriptor_t fn = FN_FunctionsList_getfn(proc->identifier_name);
    if (fn == FN_UNDEFINED)
        rt_throw("undefined procedure '%s::%s'", module->identifier_name, proc->identifier_name);
    RT_VarTable_acc_setval(FN_FunctionsList_call(fn));
}
