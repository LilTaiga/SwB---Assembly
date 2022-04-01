.globl f87
f87:
    pushq %rbp
    movq %rsp, %rbp
        #Retornando...
        #Valor de retorno: pi1
    movl %edi, %eax
    leave
    ret

.globl f88
f88:
    pushq %rbp
    movq %rsp, %rbp
        #Retornando...
        #Valor de retorno: pi2
    movl %esi, %eax
    leave
    ret

.globl f89
f89:
    pushq %rbp
    movq %rsp, %rbp
        #Retornando...
        #Valor de retorno: pi3
    movl %edx, %eax
    leave
    ret

