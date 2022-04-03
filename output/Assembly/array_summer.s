.globl f9000
f9000:
    pushq %rbp
    movq %rsp, %rbp
        # Reservando espaço para as variáveis locais na pilha
        #vi1.offset: -4
        #vi2.offset: -8
        # Reservando espaço (caso necessário) para os registradores na pilha.
        #pa1.offset: -16
    subq $16, %rsp

        #Acessando array.
        #Array: pa1
        #Index: 0
        #Destino: vi2
    movl 0(%rdi), %eax
    movl %eax, -8(%rbp)
        #Adição:
    movl -4(%rbp), %eax
    addl -8(%rbp), %eax
    movl %eax, -4(%rbp)

        #Acessando array.
        #Array: pa1
        #Index: 1
        #Destino: vi2
    movl 4(%rdi), %eax
    movl %eax, -8(%rbp)
        #Adição:
    movl -4(%rbp), %eax
    addl -8(%rbp), %eax
    movl %eax, -4(%rbp)

        #Acessando array.
        #Array: pa1
        #Index: 2
        #Destino: vi2
    movl 8(%rdi), %eax
    movl %eax, -8(%rbp)
        #Adição:
    movl -4(%rbp), %eax
    addl -8(%rbp), %eax
    movl %eax, -4(%rbp)

        #Acessando array.
        #Array: pa1
        #Index: 3
        #Destino: vi2
    movl 12(%rdi), %eax
    movl %eax, -8(%rbp)
        #Adição:
    movl -4(%rbp), %eax
    addl -8(%rbp), %eax
    movl %eax, -4(%rbp)

        #Acessando array.
        #Array: pa1
        #Index: 4
        #Destino: vi2
    movl 16(%rdi), %eax
    movl %eax, -8(%rbp)
        #Adição:
    movl -4(%rbp), %eax
    addl -8(%rbp), %eax
    movl %eax, -4(%rbp)

        #Retornando...
        #Valor de retorno: vi1
    movl -4(%rbp), %eax
    leave
    ret

