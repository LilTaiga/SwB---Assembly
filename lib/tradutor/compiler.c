#include <stdio.h>
#include <string.h>

#include "base.h"  // Aqui estão definidos o buffer e o read_line()

int function_initialization();
void process_local_variables();
void process_instructions();
void process_attribuition();

//Essas structs servem para salvarmos as informacoes necessarias e uteis das nossas variaveis locais para facilitar o uso do registrador da pilha correspondentes a uma variavel.
typedef struct variables_simple{ //struct para variaveis int (viN).
	int pile_place, value;
}variables;

typedef struct variables_array{ //struct para arrays (vaN).
	int pile_place, size, value;
}variables_a;

//temos no maximo 5 variaveis locais.
variables v1[5]; // v1 é dedicado a variaveis que nao sao arrays.
variables_a v2[5]; // v2 é dedicado a variaveis que sao arrays.

// Aqui é onde o processo de compilação de BPL para Assembly ocorre.
// Todas as funções relacionadas a gerar código Assembly são feitas aqui.

// Essa função é chamada quando encontra-se uma função em BPL
// Buffer atual: "function fN {pX1 {pX2 {pX3}}}"
// Esta função retorna quando encontra-se a palavra-chave "end"

void process_attribution()
{
	// Processar as operações é um simples caso de casar a string de formatação.
	// Ao chegar no final da função, pare.


	int matches = 0; //Numero de acertos na funcao strncmp.
	char operation; // tipo da operaçao.
	int main_variable; // Numero da vaariavel a ser alterada.
	char variable_type[2]; // numero das variaveis usadas na operacao.
	int variable_number[2]; // tipo da variavel utilizada.
	
  	matches = sscanf(buffer, "vi%d = %ci%d %c %ci%d", &main_variable, &variable_type[0], &variable_number[0], &operation, &variable_type[1], &variable_number[1]);
	// Caso de atribuicao.
	if(matches == 3)
	{
		if(variable_type[0] == 'c') 
			printf("    movl $%d, %d(%%rbp)\n", variable_number[0], v1[main_variable-1].pile_place);
		if(variable_type[0] == 'v') 
			printf("    movl %d(%%rbp), %d(%%rbp)\n", v1[variable_number[0]-1].pile_place, v1[main_variable-1].pile_place);
		if(variable_type[0] == 'p')
		{
			if(variable_number[0] == 1) 
				printf("    movl %%edi, %d(%%rbp)\n", v1[main_variable-1].pile_place);
			else if(variable_number[0] == 2) 
				printf("    movl %%esi, %d(%%rbp)\n", v1[main_variable-1].pile_place);
			else 
				printf("    movl %%edx, %d(%%rbp)\n", v1[main_variable-1].pile_place);
		}
	}
}

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

			v1[index-1].pile_place = required_bytes * (-1); 
			continue;
		}
		if(strncmp(buffer, "vet", 3) == 0)
		{
			int vector_size = 0;
			sscanf(buffer, "vet va%d size ci%d", &index, &vector_size);

			required_bytes += 4 * vector_size;

			v2[index-1].size = vector_size;
			v2[index-1].pile_place = required_bytes * (-1);
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

	// Enquanto não encontrarmos o final da função, iremos processar as operações.
	
	while(strncmp(buffer, "end", 3) != 0)
	{ 
		if(strncmp(buffer, "vi", 2) == 0) process_attribution();
		read_line();
	}
}
