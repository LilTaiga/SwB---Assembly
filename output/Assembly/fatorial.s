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

    movl $1, %eax
    subl %edi, %eax
    movl %eax, -4(%rbp)

        # if encontrado
        # Comparando o valor de: vi1
    cmp $0, -4(%rbp)
    je f9999_if1

        # Instrução do if:

        # Fim do if
f9999_if1:


        # Chamada de função!
        #Salvando os nossos registradores na pilha
    movl %edi, -12(%rbp)

    movl -4(%rbp), %edi

        # Chamando a função
    call f9999

    movl %eax, -8(%rbp)

    # Recuperando os nossos registradores da pilha
    movl -12(%rbp), %edi

        # Fim da chamada de função!
    movl -8(%rbp), %eax
    imull %edi, %eax
    movl %eax, -8(%rbp)
        #Retornando...
        #Valor de retorno: vi2
    movl -8(%rbp), %eax
    leave
    ret

