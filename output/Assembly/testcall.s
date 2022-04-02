.globl f1
f1:
    pushq %rbp
    movq %rsp, %rbp
    #vi1 = -4
    #va2 = -24
    #pi1: -28
    #pa2: -40
    #pi3: -44
    subq $48, %rsp

    #salvar pilha
    movl %edi, -28(%rbp)
    movq %rsi, -40(%rbp)
    movl %edx, -44(%rbp)

    movq -40(%rbp), %rdi
    movl $3, %esi
    leaq -24(%rbp), %rdx
    call f2

    movl %eax, -4(%rbp)

    #recuperar pilha
    movl -28(%rbp), %edi
    movl -40(%rbp), %rsi
    movl -44(%rbp), %edx

    #salvar pilha
    movl %edi, -28(%rbp)
    movq %rsi, -40(%rbp)
    movl %edx, -44(%rbp)

    movl -4(%rbp), %edi
    movl -28(%rbp), %esi
    movl $-5, %edx
    call f2

    movl %eax, -4(%rbp)

    #recuperar pilha
    movl -28(%rbp), %edi
    movl -40(%rbp), %rsi
    movl -44(%rbp), %edx

        #Retornando...
        #Valor de retorno: ci1024
    movl $1024, %eax
    leave
    ret

