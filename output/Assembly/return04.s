.globl f888
f888:
    pushq %rbp
    movq %rsp, %rbp
        #va1.offset = -20
        #vi2.offset = -24
    subq $32, %rsp

        #Retornando...
        #Valor de retorno: vi2
    movl -24(%rbp), %eax
    leave
    ret

.globl f999
f999:
    pushq %rbp
    movq %rsp, %rbp
        #vi1.offset = -4
        #va2.offset = -24
    subq $32, %rsp

        #Retornando...
        #Valor de retorno: pi3
    movl %edx, %eax
    leave
    ret

.globl f101010
f101010:
    pushq %rbp
    movq %rsp, %rbp
        #vi1.offset = -4
        #va2.offset = -44
        #vi3.offset = -48
        #va4.offset = -128
        #vi5.offset = -132
    subq $144, %rsp

        #Retornando...
        #Valor de retorno: vi5
    movl -132(%rbp), %eax
    leave
    ret

