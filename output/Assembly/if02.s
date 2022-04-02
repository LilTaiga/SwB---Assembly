.globl f500
f500:
    pushq %rbp
    movq %rsp, %rbp
        # Reservando espaço para as variáveis locais na pilha
        #vi1.offset: -4
        # Reservando espaço (caso necessário) para os registradores na pilha.
        #pi1.offset: -8
        #pi2.offset: -12
        #pi3.offset: -16
    subq $16, %rsp

    movl $5, -4(%rbp)

        # if encontrado
        # Comparando o valor de: pi1
    cmp $0, %edi
    je f500_if1

        # Instrução do if:
    movl %esi, %eax
    addl %edx, %eax
    movl %eax, -4(%rbp)

        # Fim do if
f500_if1:

        #Retornando...
        #Valor de retorno: ci0
    movl $0, %eax
    leave
    ret

