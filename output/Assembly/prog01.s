.globl f1
f1:
    pushq %rbp
    movq %rsp, %rbp
    #vi1 = -4
    #va2 = -24
    #pi1: -28
    subq $32, %rsp

    #salvar pilha
    movl %edi, -28(%rbp)

    movl -28(%rbp), %edi
    movl $3, %esi
    leaq -24(%rbp), %rdx
    call f2

    movl %eax, -4(%rbp)

    #recuperar pilha
    movl -28(%rbp), %edi

    #salvar pilha
    movl %edi, -28(%rbp)

    movl -4(%rbp), %edi
    movl -28(%rbp), %esi
    movl $-5, %edx
    call f2

    movl %eax, -4(%rbp)

    #recuperar pilha
    movl -28(%rbp), %edi

        #Retornando...
        #Valor de retorno: ci1024
    movl $1024, %eax
    leave
    ret

