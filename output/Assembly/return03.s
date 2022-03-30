.globl f153
f153:
    pushq %rbp
    movq %rsp, %rbp
        #vi1.offset = -4
    subq $16, %rsp

        #Retornando...
        #Valor de retorno: vi1
    movl -4(%rbp), %eax
    leave
    ret

.globl f154
f154:
    pushq %rbp
    movq %rsp, %rbp
        #vi1.offset = -4
        #vi2.offset = -8
        #vi3.offset = -12
    subq $16, %rsp

        #Retornando...
        #Valor de retorno: vi3
    movl -12(%rbp), %eax
    leave
    ret

.globl f155
f155:
    pushq %rbp
    movq %rsp, %rbp
        #va1.offset = -28
        #vi2.offset = -32
    subq $32, %rsp

        #Retornando...
        #Valor de retorno: vi2
    movl -32(%rbp), %eax
    leave
    ret

