extern halCounterQueryRoutine:QWORD
extern circularKernelContextLogger:QWORD
extern keQueryPerformanceCounterHook:PROC


PUSHAQ MACRO
    push    rax
    push    rcx
    push    rdx
    push    rbx
    push    -1      ; dummy for rsp
    push    rbp
    push    rsi
    push    rdi
    push    r8
    push    r9
    push    r10
    push    r11
    push    r12
    push    r13
    push    r14
    push    r15
ENDM


POPAQ MACRO
    pop     r15
    pop     r14
    pop     r13
    pop     r12
    pop     r11
    pop     r10
    pop     r9
    pop     r8
    pop     rdi
    pop     rsi
    pop     rbp
    add     rsp, 8    ; dummy for rsp
    pop     rbx
    pop     rdx
    pop     rcx
    pop     rax
ENDM

.code
; Not the most reliable and clean check, but still better than
; having to pattern scan for functions and checking the stack backtrace
checkLogger PROC
	;cmp rbx, circularKernelContextLogger
	;je correctLogger
	;cmp rbp, circularKernelContextLogger
	;je correctLogger
	;cmp rsi, circularKernelContextLogger
	;je correctLogger
	;cmp rdi, circularKernelContextLogger
	;je correctLogger
	;cmp r10, circularKernelContextLogger
	;je correctLogger
	;cmp r11, circularKernelContextLogger
	;je correctLogger
	;cmp r12, circularKernelContextLogger
	;je correctLogger
	;cmp r13, circularKernelContextLogger
	;je correctLogger
	;cmp r14, circularKernelContextLogger
	;je correctLogger
	;cmp r15, circularKernelContextLogger
	;jne exit
correctLogger:
	push rcx
	mov rcx,rsp
	call keQueryPerformanceCounterHook
	pop rcx
exit:
	mov rax, halCounterQueryRoutine
	jmp rax
checkLogger ENDP
end