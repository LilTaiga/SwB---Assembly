.globl f24
f24:
    pushq %rbp
    movq %rsp, %rbp
        #va1.offset = -20
        #vi2.offset = -24
    subq $32, %rsp

       #Escrevendo no array.
       #Array: va1
       #Index: 2
       #Valor: vi2
    movl -24(%rbp), %eax
    movl %eax, -12(%rbp)
       #Escrevendo no array.
       #Array: va1
       #Index: 0
       #Valor: ci7
    movl $7, %eax
    movl %eax, -20(%rbp)
       #Escrevendo no array.
       #Array: va1
       #Index: 4
       #Valor: ci-5
    movl $-5, %eax
    movl %eax, -4(%rbp)
    leave
    ret

.globl f29
f29:
    pushq %rbp
    movq %rsp, %rbp
        #va1.offset = -20
        #va2.offset = -60
        #vi3.offset = -64
        #vi4.offset = -68
    subq $80, %rsp

       #Escrevendo no array.
       #Array: va1
       #Index: 1
       #Valor: vi3
    movl -64(%rbp), %eax
    movl %eax, -16(%rbp)
       #Escrevendo no array.
       #Array: va2
       #Index: 1
       #Valor: vi4
    movl -68(%rbp), %eax
    movl %eax, -56(%rbp)
       #Escrevendo no array.
       #Array: va1
       #Index: 4
       #Valor: vi3
    movl -64(%rbp), %eax
    movl %eax, -4(%rbp)
       #Escrevendo no array.
       #Array: va2
       #Index: 9
       #Valor: ci50
    movl $50, %eax
    movl %eax, -24(%rbp)
    leave
    ret

