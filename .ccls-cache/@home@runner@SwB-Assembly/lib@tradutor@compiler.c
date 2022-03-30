#include <stdio.h>
#include <string.h>

#include "base.h"  // Aqui estão definidos o buffer e o read_line()

int function_initialization();
void process_local_variables();
void process_instructions();
void process_attribuition();
void process_vector_getter();
void process_vector_setter();

//Essas structs servem para salvarmos as informacoes necessarias e uteis das nossas variaveis locais para facilitar o uso do registrador da pilha correspondentes a uma variavel.
typedef struct stack_info
{
	int offset;
	unsigned int size;
} stack_info;

//temos no maximo 5 variaveis locais.
stack_info stack[5];

void compile_function()
{
	// Registradores:
	// Primeiro parâmetro: %di
	// Segundo parâmetro: %si
	// Terceiro parâmetro: %dx
	int parameters = function_initialization();
	
	// Inicializar a pilha

	printf("    pushq %%rbp\n");
	printf("    movq %%rsp, %%rbp\n");

	// Processar as variáveis locais

	process_local_variables();
	
	// Processar as instruções

	process_instructions();

	// Desfazer a pilha

	printf("    leave\n");
	printf("    ret\n\n");
}

int function_initialization()
{
	int function_number = 0;
	char parameter_types[3];

	int matches = sscanf(buffer, "function f%d p%c1 p%c2 p%c3", &function_number,
						 &parameter_types[0], &parameter_types[1], &parameter_types[2]);

	// Sabemos que pelo menos o primeiro %d foi lido com sucesso.
	// Para descobrir a quantidade de parâmetros. Devemos olhar quantos matches foram feitos.

	printf(".globl f%d\n", function_number);
	printf("f%d:\n", function_number);

	return matches - 1;
}

void process_local_variables()
{
	// Buffer atual: "function fN {pX1 {pX2 {pX3}}}"

	read_line();  	// Buffer atual: "def"
	// Agora iremos ler as próximas linhas até encontrar "enddef"
	// E alocar o espaço necessário na pilha.

	int required_bytes = 0;
	int index;
		
	do
	{
		read_line();
		if(strncmp(buffer, "var", 3) == 0)
		{
			sscanf(buffer, "var vi%d", &index);
			
			required_bytes += 4;

			stack[index-1].offset = required_bytes * (-1);

			printf("        #vi%d.offset = %d\n", index, stack[index-1].offset);
			
			continue;
		}
		if(strncmp(buffer, "vet", 3) == 0)
		{
			int vector_size = 0;
			sscanf(buffer, "vet va%d size ci%d", &index, &vector_size);

			required_bytes += 4 * vector_size;

			stack[index-1].size = vector_size;
			stack[index-1].offset = (required_bytes) * (-1);

			printf("        #va%d.offset = %d\n", index, stack[index-1].offset);
			continue;
		}
		
	} while(strncmp(buffer, "enddef", 6) != 0);

	// Agora que sabemos quantos bytes precisamos, hora de alocar a pilha.
	// Lembrando que a pilha deve sempre ser alocada em múltiplos de 16

	if(required_bytes == 0)
		return;

	int stack_size = 0;
	while(stack_size < required_bytes)
		stack_size += 16;

	printf("    subq $%d, %%rsp\n\n", stack_size);
}

void process_instructions()
{
	// Buffer atual: "enddef"

	read_line();	// Buffer atual: ??? ("end" ou instrução)

	while(strncmp(buffer, "end", 3) != 0)
	{
		if(strncmp(buffer, "get", 3) == 0) process_vector_getter();
		if(strncmp(buffer, "set", 2) == 0) process_vector_setter();
		read_line();
	}
}

void process_vector_getter()
{
	// Buffer atual: "get CaN index ciN to CiN"

	char vec_type;	// variável local ou parâmetro
	int vec_index;	// índice do vetor

	int vec_offset;	// A posição a ser acessada

	char target_type;	// variável local ou parâmetro
	int target_index;	// índice do target

	sscanf(buffer, "get %ca%d index ci%d to %ci%d", 
		&vec_type, &vec_index, &vec_offset,
		&target_type, &target_index);

	printf("       #Acessando array.\n");
	printf("       #Array: %ca%d\n", vec_type, vec_index);
	printf("       #Index: %d\n", vec_offset);
	printf("       #Destino: %ci%d\n", target_type, target_index);

	char register_pointer[4];
	int stack_offset;

	if(vec_type == 'v')
	{
		strcpy(register_pointer, "rbp");
		stack_offset = stack[vec_index - 1].offset;	// vec_offset = &va
		stack_offset += 4 * vec_offset;
	}
	else	// vec_type = "p"
	{
		switch (vec_index)
		{
			case 1:
				strcpy(register_pointer, "rdi");
				break;
			case 2:
				strcpy(register_pointer, "rsi");
				break;
			case 3:
				strcpy(register_pointer, "rdx");
				break;
		}

		stack_offset = vec_offset * 4;
	}

	printf("    movl %d(%%%s), %%eax\n", stack_offset, register_pointer);

	char target_register[4];
	int target_offset;
	
	if(target_type == 'p')
	{
		switch (target_index)
		{
			case 1:
				strcpy(target_register, "edi");
				break;
			case 2:
				strcpy(target_register, "esi");
				break;
			case 3:
				strcpy(target_register, "edx");
				break;
		}

		printf("    movl %%eax, %%%s\n", target_register);
	}
	else	// target_type == 'v'
	{
		strcpy(target_register, "rbp");
		target_offset = stack[target_index - 1].offset;
		printf("    movl %%eax, %d(%%%s)\n", target_offset, target_register);
	}
}

void process_vector_setter()
{
	// Buffer atual: "set CaN index ciN with CiN"

	char vec_type;
	int vec_index; 

	int vec_offset;

	char base_type;
	int base_index;

	sscanf(buffer, "set %ca%d index ci%d with %ci%d", 
		&vec_type, &vec_index, &vec_offset,
		&base_type, &base_index);

	printf("       #Escrevendo no array.\n");
	printf("       #Array: %ca%d\n", vec_type, vec_index);
	printf("       #Index: %d\n", vec_offset);
	printf("       #Valor: %ci%d\n", base_type, base_index);

	char base_register[4];
	int base_offset;
	
	if(base_type == 'p')
	{
		switch (base_index)
		{
			case 1:
				strcpy(base_register, "edi");
				break;
			case 2:
				strcpy(base_register, "esi");
				break;
			case 3:
				strcpy(base_register, "edx");
				break;
		}

		printf("    movl %%%s, %%eax\n", base_register);
	}
	else if (base_type == 'v')
	{
		strcpy(base_register, "rbp");
		base_offset = stack[base_index - 1].offset;
		printf("    movl %d(%%%s), %%eax\n", base_offset, base_register);
	}
	else	//base_type == 'c' (constante)
	{
		printf("    movl $%d, %%eax\n", base_index);
	}

	char register_pointer[4];
	int stack_offset;

	if(vec_type == 'v')
	{
		strcpy(register_pointer, "rbp");
		stack_offset = stack[vec_index - 1].offset;	// vec_offset = &va
		stack_offset += 4 * vec_offset;
	}
	else	// vec_type = "p"
	{
		switch (vec_index)
		{
			case 1:
				strcpy(register_pointer, "rdi");
				break;
			case 2:
				strcpy(register_pointer, "rsi");
				break;
			case 3:
				strcpy(register_pointer, "rdx");
				break;
		}

		stack_offset = vec_offset * 4;
	}

	printf("    movl %%eax, %d(%%%s)\n", stack_offset, register_pointer);
}