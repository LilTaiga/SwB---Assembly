.globl f9950
f9950:
    pushq %rbp
    movq %rsp, %rbp
        # Reservando espaço para as variáveis locais na pilha
        #vi1.offset: -4
        #vi2.offset: -8
        #vi3.offset: -12
        # Reservando espaço (caso necessário) para os registradores na pilha.
        #pi1.offset: -16
        #pi2.offset: -20
        #pi3.offset: -24
    subq $32, %rsp

        #Multiplicação:
    movl %esi, %eax
    imull %esi, %eax
    movl %eax, -4(%rbp)

        #Multiplicação:
    movl $4, %eax
    imull %edi, %eax
    movl %eax, -8(%rbp)

        #Multiplicação:
    movl -8(%rbp), %eax
    imull %edx, %eax
    movl %eax, -8(%rbp)

        #Subtração:
    movl -4(%rbp), %eax
    subl -8(%rbp), %eax
    movl %eax, -4(%rbp)


        # Chamada de função!
        #Salvando os nossos registradores na pilha
    movl %edi, -16(%rbp)
    movl %esi, -20(%rbp)
    movl %edx, -24(%rbp)

    movl -4(%rbp), %edi

        # Chamando a função
    call f9951

    movl %eax, -12(%rbp)

    # Recuperando os nossos registradores da pilha
    movl -16(%rbp), %edi
    movl -20(%rbp), %esi
    movl -24(%rbp), %edx

        # Fim da chamada de função!

        # if encontrado
        # Comparando o valor de: vi3
    cmpl $0, -12(%rbp)
    je f9950_if1

        # Instrução do if:

        # Chamada de função!
        #Salvando os nossos registradores na pilha
    movl %edi, -16(%rbp)
    movl %esi, -20(%rbp)
    movl %edx, -24(%rbp)


        # Chamando a função
    call f9949

    movl %eax, -8(%rbp)

    # Recuperando os nossos registradores da pilha
    movl -16(%rbp), %edi
    movl -20(%rbp), %esi
    movl -24(%rbp), %edx

        # Fim da chamada de função!

        # Fim do if
f9950_if1:


        # Chamada de função!
        #Salvando os nossos registradores na pilha
    movl %edi, -16(%rbp)
    movl %esi, -20(%rbp)
    movl %edx, -24(%rbp)

    movl -4(%rbp), %edi

        # Chamando a função
    call f9952

    movl %eax, -12(%rbp)

    # Recuperando os nossos registradores da pilha
    movl -16(%rbp), %edi
    movl -20(%rbp), %esi
    movl -24(%rbp), %edx

        # Fim da chamada de função!

        # if encontrado
        # Comparando o valor de: vi3
    cmpl $0, -12(%rbp)
    je f9950_if2

        # Instrução do if:

        # Chamada de função!
        #Salvando os nossos registradores na pilha
    movl %edi, -16(%rbp)
    movl %esi, -20(%rbp)
    movl %edx, -24(%rbp)


        # Chamando a função
    call f9948

    movl %eax, -8(%rbp)

    # Recuperando os nossos registradores da pilha
    movl -16(%rbp), %edi
    movl -20(%rbp), %esi
    movl -24(%rbp), %edx

        # Fim da chamada de função!

        # Fim do if
f9950_if2:


        # Chamada de função!
        #Salvando os nossos registradores na pilha
    movl %edi, -16(%rbp)
    movl %esi, -20(%rbp)
    movl %edx, -24(%rbp)

    movl -4(%rbp), %edi

        # Chamando a função
    call f9953

    movl %eax, -12(%rbp)

    # Recuperando os nossos registradores da pilha
    movl -16(%rbp), %edi
    movl -20(%rbp), %esi
    movl -24(%rbp), %edx

        # Fim da chamada de função!

        # if encontrado
        # Comparando o valor de: vi3
    cmpl $0, -12(%rbp)
    je f9950_if3

        # Instrução do if:

        # Chamada de função!
        #Salvando os nossos registradores na pilha
    movl %edi, -16(%rbp)
    movl %esi, -20(%rbp)
    movl %edx, -24(%rbp)


        # Chamando a função
    call f9947

    movl %eax, -8(%rbp)

    # Recuperando os nossos registradores da pilha
    movl -16(%rbp), %edi
    movl -20(%rbp), %esi
    movl -24(%rbp), %edx

        # Fim da chamada de função!

        # Fim do if
f9950_if3:

        #Retornando...
        #Valor de retorno: vi1
    movl -4(%rbp), %eax
    leave
    ret

.globl f9961
f9961:
    pushq %rbp
    movq %rsp, %rbp
        # Reservando espaço para as variáveis locais na pilha
        #vi1.offset: -4
        #vi2.offset: -8
        #vi3.offset: -12
        # Reservando espaço (caso necessário) para os registradores na pilha.
        #pi1.offset: -16
        #pi2.offset: -20
        #pi3.offset: -24
    subq $32, %rsp

        #Multiplicação:
    movl $-1, %eax
    imull %edx, %eax
    movl %eax, -4(%rbp)

        #Multiplicação:
    movl $2, %eax
    imull %esi, %eax
    movl %eax, -8(%rbp)

        #Subtração:
    movl -4(%rbp), %eax
    subl %edi, %eax
    movl %eax, -12(%rbp)

        #Divisão:
    movl -8(%rbp), %ecx
    movl -12(%rbp), %eax
    cltd
    idivl %ecx
    movl %eax, -12(%rbp)

        #Retornando...
        #Valor de retorno: vi3
    movl -12(%rbp), %eax
    leave
    ret

.globl f9962
f9962:
    pushq %rbp
    movq %rsp, %rbp
        # Reservando espaço para as variáveis locais na pilha
        #vi1.offset: -4
        #vi2.offset: -8
        #vi3.offset: -12
        # Reservando espaço (caso necessário) para os registradores na pilha.
        #pi1.offset: -16
        #pi2.offset: -20
        #pi3.offset: -24
    subq $32, %rsp

        #Multiplicação:
    movl $-1, %eax
    imull %edx, %eax
    movl %eax, -4(%rbp)

        #Multiplicação:
    movl $2, %eax
    imull %esi, %eax
    movl %eax, -8(%rbp)

        #Adição:
    movl -4(%rbp), %eax
    addl %edi, %eax
    movl %eax, -12(%rbp)

        #Divisão:
    movl -8(%rbp), %ecx
    movl -12(%rbp), %eax
    cltd
    idivl %ecx
    movl %eax, -12(%rbp)

        #Retornando...
        #Valor de retorno: vi3
    movl -12(%rbp), %eax
    leave
    ret

