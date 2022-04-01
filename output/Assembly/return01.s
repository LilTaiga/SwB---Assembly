.globl f123
f123:
    pushq %rbp
    movq %rsp, %rbp
        #Retornando...
        #Valor de retorno: ci0
    movl $0, %eax
    leave
    ret

.globl f124
f124:
    pushq %rbp
    movq %rsp, %rbp
        #Retornando...
        #Valor de retorno: ci24
    movl $24, %eax
    leave
    ret

.globl f125
f125:
    pushq %rbp
    movq %rsp, %rbp
        #Retornando...
        #Valor de retorno: ci-420
    movl $-420, %eax
    leave
    ret

