.globl f1
f1:
    pushq %rbp
    movq %rsp, %rbp
        # Reservando espaço para as variáveis locais na pilha
        #vi1.offset: -4
        #va2.offset: -24
        # Reservando espaço (caso necessário) para os registradores na pilha.
        #pi1.offset: -28
        #pa2.offset: -40
        #pi3.offset: -44
    subq $48, %rsp


        # Chamada de função!
        #Salvando os nossos registradores na pilha
    movl %edi, -28(%rbp)
    movq %rsi, -40(%rbp)
    movl %edx, -44(%rbp)

    movq -40(%rbp), %rdi
    movl $3, %esi
    leaq -24(%rbp), %rdx

        # Chamando a função
    call f2

    movl %eax, -4(%rbp)

    # Recuperando os nossos registradores da pilha
    movl -28(%rbp), %edi
    movq -40(%rbp), %rsi
    movl -44(%rbp), %edx

        # Fim da chamada de função!

        # Chamada de função!
        #Salvando os nossos registradores na pilha
    movl %edi, -28(%rbp)
    movq %rsi, -40(%rbp)
    movl %edx, -44(%rbp)

    movl -4(%rbp), %edi
    movl -28(%rbp), %esi
    movl $-5, %edx

        # Chamando a função
    call f2

    movl %eax, -4(%rbp)

    # Recuperando os nossos registradores da pilha
    movl -28(%rbp), %edi
    movq -40(%rbp), %rsi
    movl -44(%rbp), %edx

        # Fim da chamada de função!
        #Retornando...
        #Valor de retorno: ci1024
    movl $1024, %eax
    leave
    ret

