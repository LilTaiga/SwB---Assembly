.globl f15
f15:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    movl -4(%rbp), %eax
    movl %eax, -0(%rbp)
    movl 0(%rbp), %eax
    movl %eax, -0(%rbp)
    movl 0(%rbp), %eax
    movl %eax, -0(%rbp)
    leave
    ret

.globl f16
f16:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    movl -20(%rbp), %eax
    movl %eax, --4(%rbp)
    movl -20(%rbp), %eax
    movl %eax, -0(%rbp)
    movl -4(%rbp), %eax
    movl %eax, --4(%rbp)
    movl 544499047(%rbp), %eax
    movl %eax, --4(%rbp)
    leave
    ret

