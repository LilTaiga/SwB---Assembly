.globl f29
f29:
    pushq %rbp
    movq %rsp, %rbp
        #va1.offset = -20
    subq $32, %rsp

       #Escrevendo no array.
       #Array: va1
       #Index: 0
       #Valor: pi1
    movl %edi, %eax
    movl %eax, -20(%rbp)
       #Escrevendo no array.
       #Array: va1
       #Index: 3
       #Valor: ci24
    movl $24, %eax
    movl %eax, -8(%rbp)
       #Escrevendo no array.
       #Array: va1
       #Index: 2
       #Valor: pi1
    movl %edi, %eax
    movl %eax, -12(%rbp)
    leave
    ret

.globl f33
f33:
    pushq %rbp
    movq %rsp, %rbp
        #va1.offset = -28
        #va2.offset = -64
        #va3.offset = -108
    subq $112, %rsp

       #Escrevendo no array.
       #Array: va1
       #Index: 6
       #Valor: pi1
    movl %edi, %eax
    movl %eax, -4(%rbp)
       #Escrevendo no array.
       #Array: va1
       #Index: 0
       #Valor: ci1
    movl $1, %eax
    movl %eax, -28(%rbp)
       #Escrevendo no array.
       #Array: va2
       #Index: 8
       #Valor: pi2
    movl %esi, %eax
    movl %eax, -32(%rbp)
       #Escrevendo no array.
       #Array: va2
       #Index: 0
       #Valor: ci2
    movl $2, %eax
    movl %eax, -64(%rbp)
       #Escrevendo no array.
       #Array: va3
       #Index: 10
       #Valor: pi3
    movl %edx, %eax
    movl %eax, -68(%rbp)
       #Escrevendo no array.
       #Array: va3
       #Index: 0
       #Valor: ci3
    movl $3, %eax
    movl %eax, -108(%rbp)
    leave
    ret

