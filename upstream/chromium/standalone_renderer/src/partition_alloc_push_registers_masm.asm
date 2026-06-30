;; Copyright 2026 The Chromium Authors
;; Use of this source code is governed by a BSD-style license that can be
;; found in the LICENSE file.

;; MASM version of PartitionAlloc's x64 stack scanning trampoline for native
;; MSVC, which does not accept the GNU-style top-level asm used upstream.

public PAPushAllRegistersAndIterateStack

.code
PAPushAllRegistersAndIterateStack proc frame
    ;; Push all callee-saved registers to get them on the stack for
    ;; conservative stack scanning. The Windows x64 ABI also treats xmm6-xmm15
    ;; as callee-saved, so keep them visible to the scanner too.
    ;;
    ;; There is an 8-byte return address on the stack. This function pushes
    ;; rbp, seven general-purpose registers, one alignment slot, and reserves
    ;; 160 bytes for xmm6-xmm15, preserving 16-byte stack alignment at the call.
    push rbp
    .pushreg rbp
    mov rbp, rsp
    .setframe rbp, 0
    push 0CDCDCDh
    .allocstack 8
    push rsi
    .pushreg rsi
    push rdi
    .pushreg rdi
    push rbx
    .pushreg rbx
    push r12
    .pushreg r12
    push r13
    .pushreg r13
    push r14
    .pushreg r14
    push r15
    .pushreg r15
    sub rsp, 160
    .allocstack 160
    .endprolog

    movdqa xmmword ptr [rsp + 144], xmm6
    movdqa xmmword ptr [rsp + 128], xmm7
    movdqa xmmword ptr [rsp + 112], xmm8
    movdqa xmmword ptr [rsp + 96], xmm9
    movdqa xmmword ptr [rsp + 80], xmm10
    movdqa xmmword ptr [rsp + 64], xmm11
    movdqa xmmword ptr [rsp + 48], xmm12
    movdqa xmmword ptr [rsp + 32], xmm13
    movdqa xmmword ptr [rsp + 16], xmm14
    movdqa xmmword ptr [rsp], xmm15

    ;; Pass 1st parameter (rcx) unchanged (Stack*).
    ;; Pass 2nd parameter (rdx) unchanged (StackVisitor*).
    ;; Save 3rd parameter (r8; IterateStackCallback).
    mov r9, r8
    ;; Pass 3rd parameter as rsp (stack pointer).
    mov r8, rsp
    call r9

    add rsp, 224
    pop rbp
    ret
PAPushAllRegistersAndIterateStack endp

end
