.globl f29
f29:
    pushq %rbp
    movq %rsp, %rbp
        #va1.offset = -20
    subq $32, %rsp

       #Acessando array.
       #Array: va1
       #Index: 0
       #Destino: pi1
    movl -20(%rbp), %eax
    movl %eax, %edi
       #Acessando array.
       #Array: va1
       #Index: 3
       #Destino: pi1
    movl -8(%rbp), %eax
    movl %eax, %edi
       #Acessando array.
       #Array: va1
       #Index: 2
       #Destino: pi1
    movl -12(%rbp), %eax
    movl %eax, %edi
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

       #Acessando array.
       #Array: va1
       #Index: 6
       #Destino: pi1
    movl -4(%rbp), %eax
    movl %eax, %edi
       #Acessando array.
       #Array: va1
       #Index: 0
       #Destino: pi1
    movl -28(%rbp), %eax
    movl %eax, %edi
       #Acessando array.
       #Array: va2
       #Index: 8
       #Destino: pi2
    movl -32(%rbp), %eax
    movl %eax, %esi
       #Acessando array.
       #Array: va2
       #Index: 0
       #Destino: pi2
    movl -64(%rbp), %eax
    movl %eax, %esi
       #Acessando array.
       #Array: va3
       #Index: 10
       #Destino: pi3
    movl -68(%rbp), %eax
    movl %eax, %edx
       #Acessando array.
       #Array: va3
       #Index: 0
       #Destino: pi3
    movl -108(%rbp), %eax
    movl %eax, %edx
    leave
    ret

