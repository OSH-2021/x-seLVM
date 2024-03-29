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


#include <assert.h>
#include <types.h>
#include <api/failures.h>
#include <api/invocation.h>
#include <api/syscall.h>
#include <machine/io.h>
#include <object/structures.h>
#include <object/interrupt.h>
#include <object/cnode.h>
#include <object/notification.h>
#include <kernel/cspace.h>
#include <kernel/thread.h>
#include <model/statedata.h>
#include <machine/timer.h>
#include <plat/machine/timer.h>
#include <smp/ipi.h>

//exception_t
//decodeIRQControlInvocation(word_t invLabel, word_t length,
//                           cte_t *srcSlot, extra_caps_t excaps,
//                           word_t *buffer)
//{
//    if (invLabel == IRQIssueIRQHandler) {
//        word_t index, depth, irq_w;
//        irq_t irq;
//        cte_t *destSlot;
//        cap_t cnodeCap;
//        lookupSlot_ret_t lu_ret;
//        exception_t status;
//
//        if (length < 3 || excaps.excaprefs[0] == NULL) {
//            current_syscall_error.type = seL4_TruncatedMessage;
//            return EXCEPTION_SYSCALL_ERROR;
//        }
//        irq_w = getSyscallArg(0, buffer);
//        irq = (irq_t) irq_w;
//        index = getSyscallArg(1, buffer);
//        depth = getSyscallArg(2, buffer);
//
//        cnodeCap = excaps.excaprefs[0]->cap;
//
//        status = Arch_checkIRQ(irq_w);
//        if (status != EXCEPTION_NONE) {
//            return status;
//        }
//
//        if (isIRQActive(irq)) {
//            current_syscall_error.type = seL4_RevokeFirst;
//            userError("Rejecting request for IRQ %u. Already active.", (int)irq);
//            return EXCEPTION_SYSCALL_ERROR;
//        }
//
//        lu_ret = lookupTargetSlot(cnodeCap, index, depth);
//        if (lu_ret.status != EXCEPTION_NONE) {
//            userError("Target slot for new IRQ Handler cap invalid: cap %lu, IRQ %u.",
//                      getExtraCPtr(buffer, 0), (int)irq);
//            return lu_ret.status;
//        }
//        destSlot = lu_ret.slot;
//
//        status = ensureEmptySlot(destSlot);
//        if (status != EXCEPTION_NONE) {
//            userError("Target slot for new IRQ Handler cap not empty: cap %lu, IRQ %u.",
//                      getExtraCPtr(buffer, 0), (int)irq);
//            return status;
//        }
//
//        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
//        return invokeIRQControl(irq, destSlot, srcSlot);
//    } else {
//        return Arch_decodeIRQControlInvocation(invLabel, length, srcSlot, excaps, buffer);
//    }
//}

//exception_t
//invokeIRQControl(irq_t irq, cte_t *handlerSlot, cte_t *controlSlot)
//{
//    setIRQState(IRQSignal, irq);
//    cteInsert(cap_irq_handler_cap_new(irq), controlSlot, handlerSlot);
//
//    return EXCEPTION_NONE;
//}

//exception_t
//decodeIRQHandlerInvocation(word_t invLabel, irq_t irq,
//                           extra_caps_t excaps)
//{
//    switch (invLabel) {
//    case IRQAckIRQ:
//        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
//        invokeIRQHandler_AckIRQ(irq);
//        return EXCEPTION_NONE;
//
//    case IRQSetIRQHandler: {
//        cap_t ntfnCap;
//        cte_t *slot;
//
//        if (excaps.excaprefs[0] == NULL) {
//            current_syscall_error.type = seL4_TruncatedMessage;
//            return EXCEPTION_SYSCALL_ERROR;
//        }
//        ntfnCap = excaps.excaprefs[0]->cap;
//        slot = excaps.excaprefs[0];
//
//        if (cap_get_capType(ntfnCap) != cap_notification_cap ||
//                !cap_notification_cap_get_capNtfnCanSend(ntfnCap)) {
//            if (cap_get_capType(ntfnCap) != cap_notification_cap) {
//                userError("IRQSetHandler: provided cap is not an notification capability.");
//            } else {
//                userError("IRQSetHandler: caller does not have send rights on the endpoint.");
//            }
//            current_syscall_error.type = seL4_InvalidCapability;
//            current_syscall_error.invalidCapNumber = 0;
//            return EXCEPTION_SYSCALL_ERROR;
//        }
//
//        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
//        invokeIRQHandler_SetIRQHandler(irq, ntfnCap, slot);
//        return EXCEPTION_NONE;
//    }
//
//    case IRQClearIRQHandler:
//        setThreadState(NODE_STATE(ksCurThread), ThreadState_Restart);
//        invokeIRQHandler_ClearIRQHandler(irq);
//        return EXCEPTION_NONE;
//
//    default:
//        userError("IRQHandler: Illegal operation.");
//        current_syscall_error.type = seL4_IllegalOperation;
//        return EXCEPTION_SYSCALL_ERROR;
//    }
//}

//void
//invokeIRQHandler_AckIRQ(irq_t irq)
//{
//    maskInterrupt(false, irq);
//}

//void
//invokeIRQHandler_SetIRQHandler(irq_t irq, cap_t cap, cte_t *slot)
//{
//    cte_t *irqSlot;
//
//    irqSlot = intStateIRQNode + irq;
//    /** GHOSTUPD: "(True, gs_set_assn cteDeleteOne_'proc (-1))" */
//    cteDeleteOne(irqSlot);
//    cteInsert(cap, slot, irqSlot);
//}

//void
//invokeIRQHandler_ClearIRQHandler(irq_t irq)
//{
//    cte_t *irqSlot;
//
//    irqSlot = intStateIRQNode + irq;
//    /** GHOSTUPD: "(True, gs_set_assn cteDeleteOne_'proc (-1))" */
//    cteDeleteOne(irqSlot);
//}

//void
//deletingIRQHandler(irq_t irq)
//{
//    cte_t *slot;
//
//    slot = intStateIRQNode + irq;
//    /** GHOSTUPD: "(True, gs_set_assn cteDeleteOne_'proc (ucast cap_notification_cap))" */
//    cteDeleteOne(slot);
//}

//void
//deletedIRQHandler(irq_t irq)
//{
//    setIRQState(IRQInactive, irq);
//}

static int 
l_handleInterrupt(lua_State *L)
{
    irq_t irq = lua_touserdata(L,1);
    if (unlikely(irq > maxIRQ)) {
        /* mask, ack and pretend it didn't happen. We assume that because
         * the interrupt controller for the platform returned this IRQ that
         * it is safe to use in mask and ack operations, even though it is
         * above the claimed maxIRQ. i.e. we're assuming maxIRQ is wrong */
        printf("Received IRQ %d, which is above the platforms maxIRQ of %d\n", (int)irq, (int)maxIRQ);
        maskInterrupt(true, irq);
        ackInterrupt(irq);
        return 0;
    }
    switch (intStateIRQTable[irq]) {
    case IRQSignal: {
        cap_t cap;

        cap = intStateIRQNode[irq].cap;

        if (cap_get_capType(cap) == cap_notification_cap &&
                cap_notification_cap_get_capNtfnCanSend(cap)) {
            sendSignal(NTFN_PTR(cap_notification_cap_get_capNtfnPtr(cap)),
                       cap_notification_cap_get_capNtfnBadge(cap));
        } else {
#ifdef CONFIG_IRQ_REPORTING
            printf("Undelivered IRQ: %d\n", (int)irq);
#endif
        }
        maskInterrupt(true, irq);
        break;
    }

    case IRQTimer:
        timerTick();
        resetTimer();
        break;

#ifdef ENABLE_SMP_SUPPORT
    case IRQIPI:
        handleIPI(irq, true);
        break;
#endif /* ENABLE_SMP_SUPPORT */

    case IRQReserved:
#ifdef CONFIG_IRQ_REPORTING
        printf("Received reserved IRQ: %d", (int)irq);
#endif
        handleReservedIRQ(irq);
        break;

    case IRQInactive:
        /*
         * This case shouldn't happen anyway unless the hardware or
         * platform code is broken. Hopefully masking it again should make
         * the interrupt go away.
         */
        maskInterrupt(true, irq);
#ifdef CONFIG_IRQ_REPORTING
        printf("Received disabled IRQ: %d\n", (int)irq);
#endif
        break;

    default:
        /* No corresponding haskell error */
        fail("Invalid IRQ state");
    }

    ackInterrupt(irq);
    return 0;
}

//bool_t
//isIRQActive(irq_t irq)
//{
//    return intStateIRQTable[irq] != IRQInactive;
//}

//void
//setIRQState(irq_state_t irqState, irq_t irq)
//{
//    intStateIRQTable[irq] = irqState;
//    maskInterrupt(irqState == IRQInactive, irq);
//}

static const luaL_Reg mylib[] = {
{"handleInterrupt",l_handleInterrupt},
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
