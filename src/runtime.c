#include <inttypes.h>
#include <stdbool.h>

#include "ast.h"
#include "ast/api.h"
#include "runtime.h"
#include "runtime/eval.h"
#include "runtime/io.h"
#include "runtime/VarTable.h"


const char *rt_currfile = NULL;
int rt_currline = 0;

const ast_Identifier_t *rt_current_module = NULL;
const ast_Identifier_t *rt_current_proc = NULL;


void rt_exec(void)
{
    const ast_Identifier_t *module = ast_util_ModuleAndProcTable_idfmain();
    const ast_Identifier_t *proc = ast_util_ModuleAndProcTable_idfmain();
    const ast_Statements_t *code = ast_util_ModuleAndProcTable_get_code(module, proc);
    rt_currfile = ast_util_ModuleAndProcTable_get_filename(module, proc);
    rt_VarTable_push_proc(proc->identifier_name);
    rt_ControlStatus_t ctrl = rt_eval_Statements(code);
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


#include "runtime/data/Data.c.h"
#include "runtime/io.c.h"
#include "runtime/eval/assignment.c.h"
#include "runtime/eval/associativelist.c.h"
#include "runtime/eval/commaseplist.c.h"
#include "runtime/eval/expression.c.h"
#include "runtime/eval/fncall.c.h"
#include "runtime/eval/forblock.c.h"
#include "runtime/eval/identifier.c.h"
#include "runtime/eval/ifblock.c.h"
#include "runtime/eval/literal.c.h"
#include "runtime/eval/statement.c.h"
#include "runtime/eval/statements.c.h"
#include "runtime/eval/whileblock.c.h"
#include "runtime/VarTable.c.h"
