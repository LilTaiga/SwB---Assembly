here
.globl f60
f60:
    pushq %rbp
    movq %rsp, %rbp
        #vi1.offset = -4
    subq $16, %rsp

       #Escrevendo no array.
       #Array: pa1
       #Index: 2
       #Valor: vi1
    movl -4(%rbp), %eax
    movl %eax, 8(%rdi)
       #Escrevendo no array.
       #Array: pa1
       #Index: 1
       #Valor: pi2
    movl %esi, %eax
    movl %eax, 4(%rdi)
       #Escrevendo no array.
       #Array: pa1
       #Index: 4
       #Valor: pi2
    movl %esi, %eax
    movl %eax, 16(%rdi)
       #Escrevendo no array.
       #Array: pa1
       #Index: 3
       #Valor: vi1
    movl -4(%rbp), %eax
    movl %eax, 12(%rdi)
       #Escrevendo no array.
       #Array: pa1
       #Index: 0
       #Valor: ci55
    movl $55, %eax
    movl %eax, 0(%rdi)
        #Retornando...
        #Valor de retorno: ci2
    movl $2, %eax
    leave
    ret

.globl f63
f63:
    pushq %rbp
    movq %rsp, %rbp
        #vi1.offset = -4
        #vi2.offset = -8
    subq $16, %rsp

       #Escrevendo no array.
       #Array: pa2
       #Index: 100
       #Valor: pi1
    movl %edi, %eax
    movl %eax, 400(%rsi)
       #Escrevendo no array.
       #Array: pa2
       #Index: 50
       #Valor: vi1
    movl -4(%rbp), %eax
    movl %eax, 200(%rsi)
       #Escrevendo no array.
       #Array: pa2
       #Index: 25
       #Valor: vi2
    movl -8(%rbp), %eax
    movl %eax, 100(%rsi)
       #Escrevendo no array.
       #Array: pa3
       #Index: 2
       #Valor: vi2
    movl -8(%rbp), %eax
    movl %eax, 8(%rdx)
       #Escrevendo no array.
       #Array: pa3
       #Index: 5
       #Valor: vi1
    movl -4(%rbp), %eax
    movl %eax, 20(%rdx)
       #Escrevendo no array.
       #Array: pa3
       #Index: 9
       #Valor: pi1
    movl %edi, %eax
    movl %eax, 36(%rdx)
       #Escrevendo no array.
       #Array: pa2
       #Index: 12
       #Valor: ci12
    movl $12, %eax
    movl %eax, 48(%rsi)
       #Escrevendo no array.
       #Array: pa3
       #Index: 7
       #Valor: ci123456
    movl $123456, %eax
    movl %eax, 28(%rdx)
        #Retornando...
        #Valor de retorno: ci42
    movl $42, %eax
    leave
    ret

