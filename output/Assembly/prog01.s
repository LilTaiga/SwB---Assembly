.globl f1
f1:
    pushq %rbp
    movq %rsp, %rbp
#vi1: -4
#pi1: -8
    subq $16, %rsp

    movl -4(%rbp), %eax
    subl $5, %eax
    movl %eax, -4(%rbp)
    leave
    ret

.globl f2
f2:
    pushq %rbp
    movq %rsp, %rbp
#vi1: -4
#pi1: -8
    subq $16, %rsp

    movl %edi, -4(%rbp)
    leave
    ret

.globl f3
f3:
    pushq %rbp
    movq %rsp, %rbp
#vi1: -4
#pa1: -8
#pi2: -12
    subq $16, %rsp

    movl -4(%rbp), %eax
    addl $1, %eax
    movl %eax, -4(%rbp)
    leave
    ret

