.globl f15
f15:
    pushq %rbp
    movq %rsp, %rbp
        #va1.offset = -20
        #vi2.offset = -24
    subq $32, %rsp

       #Acessando array.
       #Array: va1
       #Index: 2
       #Destino: vi2
    movl -12(%rbp), %eax
    movl %eax, -24(%rbp)
       #Acessando array.
       #Array: va1
       #Index: 0
       #Destino: vi2
    movl -20(%rbp), %eax
    movl %eax, -24(%rbp)
       #Acessando array.
       #Array: va1
       #Index: 4
       #Destino: vi2
    movl -4(%rbp), %eax
    movl %eax, -24(%rbp)
    leave
    ret

.globl f16
f16:
    pushq %rbp
    movq %rsp, %rbp
        #va1.offset = -20
        #va2.offset = -60
        #vi3.offset = -64
        #vi4.offset = -68
    subq $80, %rsp

       #Acessando array.
       #Array: va1
       #Index: 1
       #Destino: vi3
    movl -16(%rbp), %eax
    movl %eax, -64(%rbp)
       #Acessando array.
       #Array: va2
       #Index: 1
       #Destino: vi4
    movl -56(%rbp), %eax
    movl %eax, -68(%rbp)
       #Acessando array.
       #Array: va1
       #Index: 4
       #Destino: vi3
    movl -4(%rbp), %eax
    movl %eax, -64(%rbp)
       #Acessando array.
       #Array: va2
       #Index: 9
       #Destino: vi3
    movl -24(%rbp), %eax
    movl %eax, -64(%rbp)
    leave
    ret

