/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */


#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"


#include <api/failures.h>
#include <kernel/cspace.h>
#include <kernel/faulthandler.h>
#include <kernel/thread.h>
#include <machine/io.h>
#include <arch/machine.h>
#include <arch/kernel/vspace.h>


static int l_handleFault(lua_State *L)
{
    exception_t status;
    seL4_Fault_t fault = current_fault;
    tcb_t *tptr = lua_topointer(L,1);

    status = sendFaultIPC(tptr);
    if (status != EXCEPTION_NONE) {
        handleDoubleFault(tptr, fault);
    }
    return 0;

}


static int l_sendFaultIPC(lua_State *L)
{
    cptr_t handlerCPtr;
    cap_t  handlerCap;
    lookupCap_ret_t lu_ret;
    lookup_fault_t original_lookup_fault;
    tcb_t *tptr = lua_topointer(L,1);
    original_lookup_fault = current_lookup_fault;

    handlerCPtr = tptr->tcbFaultHandler;
    lu_ret = lookupCap(tptr, handlerCPtr);
    if (lu_ret.status != EXCEPTION_NONE) {
        current_fault = seL4_Fault_CapFault_new(handlerCPtr, false);
        lua_pushnumber(L,EXCEPTION_FAULT);
        return 1;
    }
    handlerCap = lu_ret.cap;

    if (cap_get_capType(handlerCap) == cap_endpoint_cap &&
            cap_endpoint_cap_get_capCanSend(handlerCap) &&
            cap_endpoint_cap_get_capCanGrant(handlerCap)) {
        tptr->tcbFault = current_fault;
        if (seL4_Fault_get_seL4_FaultType(current_fault) == seL4_Fault_CapFault) {
            tptr->tcbLookupFailure = original_lookup_fault;
        }
        sendIPC(true, false,
                cap_endpoint_cap_get_capEPBadge(handlerCap),
                true, tptr,
                EP_PTR(cap_endpoint_cap_get_capEPPtr(handlerCap)));
            lua_pushnumber(L,EXCEPTION_FAULT);
            return 1;
    } else {
        current_fault = seL4_Fault_CapFault_new(handlerCPtr, false);
        current_lookup_fault = lookup_fault_missing_capability_new(0);
        
        lua_pushnumber(L,EXCEPTION_FAULT);
        return 1;
    }
}

#ifdef CONFIG_PRINTING
static int l_print_fault(lua_State *L)
{   
    seL4_Fault_t f = lua_touserdata(L,1);
    switch (seL4_Fault_get_seL4_FaultType(f)) {
    case seL4_Fault_NullFault:
        printf("null fault");
        break;
    case seL4_Fault_CapFault:
        printf("cap fault in %s phase at address %p",
               seL4_Fault_CapFault_get_inReceivePhase(f) ? "receive" : "send",
               (void *)seL4_Fault_CapFault_get_address(f));
        break;
    case seL4_Fault_VMFault:
        printf("vm fault on %s at address %p with status %p",
               seL4_Fault_VMFault_get_instructionFault(f) ? "code" : "data",
               (void *)seL4_Fault_VMFault_get_address(f),
               (void *)seL4_Fault_VMFault_get_FSR(f));
        break;
    case seL4_Fault_UnknownSyscall:
        printf("unknown syscall %p",
               (void *)seL4_Fault_UnknownSyscall_get_syscallNumber(f));
        break;
    case seL4_Fault_UserException:
        printf("user exception %p code %p",
               (void *)seL4_Fault_UserException_get_number(f),
               (void *)seL4_Fault_UserException_get_code(f));
        break;
    default:
        printf("unknown fault");
        break;
    }
    return 0;
}
#endif

/* The second fault, ex2, is stored in the global current_fault */
static int l_handleDoubleFault(lua_State *L)
{
    tcb_t *tptr = lua_topointer(L,2);
    seL4_Fault_t ex1 = lua_touserdata(L,1);
#ifdef CONFIG_PRINTING
    seL4_Fault_t ex2 = current_fault;
    printf("Caught ");
    print_fault(ex2);
    printf("\nwhile trying to handle:\n");
    print_fault(ex1);

#ifdef CONFIG_DEBUG_BUILD
    printf("\nin thread %p \"%s\" ", tptr, tptr->tcbName);
#endif /* CONFIG_DEBUG_BUILD */

    printf("at address %p\n", (void*)getRestartPC(tptr));
    printf("With stack:\n");
    Arch_userStackTrace(tptr);
#endif

    setThreadState(tptr, ThreadState_Inactive);
    return 0;
}

static const luaL_Reg mylib[] = {
{"handleFault",l_handleFault},
{"sendFaultIPC",l_sendFaultIPC},
{"print_fault",l_print_fault},
{"handleDoubleFault",l_handleDoubleFault},
{NULL, NULL}
};

extern int luaopen_seL4_lib(lua_State* L)
{
    /* void luaL_newlib (lua_State *L, const luaL_Reg l[]);
     * 创建一个新的"table"，并将"l"中所列出的函数注册为"table"的域。
     */ 
    luaL_newlib(L, mylib);

    return 1;
}