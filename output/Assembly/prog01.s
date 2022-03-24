.globl f1
f1:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    movl %edi, -4(%rbp)
    leave
    ret

.globl f2
f2:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    leave
    ret

.globl f3
f3:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    leave
    ret

