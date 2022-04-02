.globl f60
f60:
    pushq %rbp
    movq %rsp, %rbp
        # Reservando espaço para as variáveis locais na pilha
        #vi1.offset: -4
        # Reservando espaço (caso necessário) para os registradores na pilha.
        #pa1.offset: -16
        #pi2.offset: -20
    subq $32, %rsp

        #Acessando array.
        #Array: pa1
        #Index: 2
        #Destino: vi1
    movl 8(%rdi), %eax
    movl %eax, -4(%rbp)
        #Acessando array.
        #Array: pa1
        #Index: 1
        #Destino: pi2
    movl 4(%rdi), %eax
    movl %eax, %esi
        #Acessando array.
        #Array: pa1
        #Index: 4
        #Destino: pi2
    movl 16(%rdi), %eax
    movl %eax, %esi
        #Acessando array.
        #Array: pa1
        #Index: 3
        #Destino: vi1
    movl 12(%rdi), %eax
    movl %eax, -4(%rbp)
        #Retornando...
        #Valor de retorno: ci2
    movl $2, %eax
    leave
    ret

.globl f63
f63:
    pushq %rbp
    movq %rsp, %rbp
        # Reservando espaço para as variáveis locais na pilha
        #vi1.offset: -4
        #vi2.offset: -8
        # Reservando espaço (caso necessário) para os registradores na pilha.
        #pi1.offset: -12
        #pa2.offset: -24
        #pa3.offset: -32
    subq $32, %rsp

        #Acessando array.
        #Array: pa2
        #Index: 100
        #Destino: pi1
    movl 400(%rsi), %eax
    movl %eax, %edi
        #Acessando array.
        #Array: pa2
        #Index: 50
        #Destino: vi1
    movl 200(%rsi), %eax
    movl %eax, -4(%rbp)
        #Acessando array.
        #Array: pa2
        #Index: 25
        #Destino: vi2
    movl 100(%rsi), %eax
    movl %eax, -8(%rbp)
        #Acessando array.
        #Array: pa3
        #Index: 2
        #Destino: vi2
    movl 8(%rdx), %eax
    movl %eax, -8(%rbp)
        #Acessando array.
        #Array: pa3
        #Index: 5
        #Destino: vi1
    movl 20(%rdx), %eax
    movl %eax, -4(%rbp)
        #Acessando array.
        #Array: pa3
        #Index: 9
        #Destino: pi1
    movl 36(%rdx), %eax
    movl %eax, %edi
        #Retornando...
        #Valor de retorno: ci42
    movl $42, %eax
    leave
    ret

