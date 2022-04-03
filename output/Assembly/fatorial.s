.globl f9999
f9999:
    pushq %rbp
    movq %rsp, %rbp
        # Reservando espaço para as variáveis locais na pilha
        #vi1.offset: -4
        #vi2.offset: -8
        # Reservando espaço (caso necessário) para os registradores na pilha.
        #pi1.offset: -12
    subq $16, %rsp


        # Chamada de função!
        #Salvando os nossos registradores na pilha
    movl %edi, -12(%rbp)

    movl -12(%rbp), %edi

        # Chamando a função
    call f9998

    movl %eax, -8(%rbp)

    # Recuperando os nossos registradores da pilha
    movl -12(%rbp), %edi

        # Fim da chamada de função!

        # if encontrado
        # Comparando o valor de: vi2
    cmpl $0, -8(%rbp)
    je f9999_if1

        # Instrução do if:
        #Retornando...
        #Valor de retorno: ci1
    movl $1, %eax
    leave
    ret


        # Fim do if
f9999_if1:

        #Subtração:
    movl %edi, %eax
    subl $1, %eax
    movl %eax, -8(%rbp)


        # Chamada de função!
        #Salvando os nossos registradores na pilha
    movl %edi, -12(%rbp)

    movl -8(%rbp), %edi

        # Chamando a função
    call f9999

    movl %eax, -4(%rbp)

    # Recuperando os nossos registradores da pilha
    movl -12(%rbp), %edi

        # Fim da chamada de função!
        #Multiplicação:
    movl -4(%rbp), %eax
    imull %edi, %eax
    movl %eax, -4(%rbp)

        #Retornando...
        #Valor de retorno: vi1
    movl -4(%rbp), %eax
    leave
    ret

.globl f9998
f9998:
    pushq %rbp
    movq %rsp, %rbp
        # Reservando espaço para as variáveis locais na pilha
        # Reservando espaço (caso necessário) para os registradores na pilha.
        #pi1.offset: -4
    subq $16, %rsp


        # if encontrado
        # Comparando o valor de: pi1
    cmpl $0, %edi
    je f9998_if1

        # Instrução do if:
        #Retornando...
        #Valor de retorno: ci0
    movl $0, %eax
    leave
    ret


        # Fim do if
f9998_if1:

        #Retornando...
        #Valor de retorno: ci1
    movl $1, %eax
    leave
    ret

