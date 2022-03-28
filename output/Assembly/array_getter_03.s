.globl f60
f60:
    pushq %rbp
    movq %rsp, %rbp
        #vi1.offset = -4
    subq $16, %rsp

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
    leave
    ret

.globl f63
f63:
    pushq %rbp
    movq %rsp, %rbp
        #vi1.offset = -4
        #vi2.offset = -8
    subq $16, %rsp

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
    leave
    ret

