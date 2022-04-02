#include <stdio.h>
#include <string.h>
#include "base.h"	// Aqui estão definidos o buffer e o read_line() e as declarações das demais funções.
	// Essas structs servem para salvarmos as informacoes necessarias e uteis das
// nossas variaveis locais para facilitar o uso do registrador da pilha
// correspondentes a uma variavel.
typedef struct stack_info
{
	int offset;
	unsigned int size;
}
stack_info;

// temos no maximo 5 variaveis locais.
stack_info stack[5];

// temos tbm 3 parametros que podem vir com a funcao
stack_info parameter[3];

// Aqui é onde o processo de compilação de BPL para Assembly ocorre.
// Todas as funções relacionadas a gerar código Assembly são feitas aqui.

// Essa função é chamada quando encontra-se uma função em BPL
// Buffer atual: "function fN {pX1 {pX2 {pX3}}}"
// Esta função retorna quando encontra-se a palavra-chave "end"

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

	process_local_variables(parameters);

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

	int matches =
		sscanf(buffer, "function f%d p%c1 p%c2 p%c3", &function_number, &parameter_types[0], &parameter_types[1], &parameter_types[2]);

	for (int i = 0; i < matches; i++)
	{
		if (parameter_types[i] == 'i')
			parameter[i].offset = 4;
		if (parameter_types[i] == 'a')
			parameter[i].offset = 8;
	}

	// Sabemos que pelo menos o primeiro %d foi lido com sucesso.
	// Para descobrir a quantidade de parâmetros. Devemos olhar quantos matches
	// foram feitos.

	printf(".globl f%d\n", function_number);
	printf("f%d:\n", function_number);

	return matches - 1;
}

void process_local_variables(int a)
{
	// Buffer atual: "function fN {pX1 {pX2 {pX3}}}"

	read_line();	// Buffer atual: "def"
	// Agora iremos ler as próximas linhas até encontrar "enddef"
	// E alocar o espaço necessário na pilha.

	int required_bytes = 0;
	int index;

	do {
		read_line();
		if (strncmp(buffer, "var", 3) == 0)
		{
			sscanf(buffer, "var vi%d", &index);

			required_bytes += 4;

			stack[index - 1].offset = required_bytes *(-1);
			printf("    #vi%d = %d\n", index, stack[index - 1].offset);

			continue;
		}
		if (strncmp(buffer, "vet", 3) == 0)
		{
			int vector_size = 0;
			sscanf(buffer, "vet va%d size ci%d", &index, &vector_size);

			required_bytes += 4 * vector_size;

			stack[index - 1].size = vector_size;

			stack[index - 1].offset = (required_bytes) *(-1);
			printf("    #va%d = %d\n", index, stack[index - 1].offset);
			continue;
		}
	} while (strncmp(buffer, "enddef", 6) != 0);

	// Adicionando os parametros à pilha em caso de chamada de funcoes
	for (int i = 0; i < a; i++)
	{
		// Para paremetros do tipo inteiro
		if (parameter[i].offset == 4)
		{
			required_bytes += 4;
			parameter[i].offset = required_bytes *(-1);
			printf("    #pi%d: %d\n", i + 1, parameter[i].offset);
			parameter[i].size = 1;
		}
		else if (parameter[i].offset == 8)
		{
			// Para parametros ponteiros
			required_bytes += 8;

			//É necessario garantir alinhamento do tipo ponteiro com 8
			while (required_bytes % 8 != 0)
				required_bytes += 4;
			parameter[i].offset = required_bytes *(-1);
			printf("    #pa%d: %d\n", i + 1, parameter[i].offset);
			parameter[i].size = 2;
		}
	}

	// Agora que sabemos quantos bytes precisamos, hora de alocar a pilha.
	// Lembrando que a pilha deve sempre ser alocada em múltiplos de 16

	if (required_bytes == 0)
		return;

	int stack_size = 0;
	while (stack_size < required_bytes)
		stack_size += 16;

	printf("    subq $%d, %%rsp\n\n", stack_size);
}

void process_instructions()
{
	// Buffer atual: "enddef"

	read_line();	// Buffer atual: ??? ("end" ou instrução)

	// Enquanto não encontrarmos o final da função, iremos processar as operações.

	while (strncmp(buffer, "end", 3) != 0)
	{
		if (strncmp(buffer, "vi", 2) == 0)
			process_attribution();
		// if(strncmp(buffer, "pi", 2) == 0) process_attribution();
		if (strncmp(buffer, "get", 3) == 0)
			process_vector_getter();
		if (strncmp(buffer, "set", 2) == 0)
			process_vector_setter();
		if (strncmp(buffer, "return", 6) == 0)
			process_return();
		read_line();
	}
}

void process_attribution()
{
	// Processar as operações é um simples caso de casar a string de formatação.
	// Ao chegar no final da função, pare.

	int matches = 0;	// Numero de acertos na funcao strncmp.
	char operation;	// tipo da operaçao.
	int main_variable;	// Numero da vaariavel a ser alterada.
	char variable_type[2];	// numero das variaveis usadas na operacao.
	int variable_number[2];	// tipo da variavel utilizada.

	matches = sscanf(buffer, "vi%d = %ci%d %c %ci%d", &main_variable, &variable_type[0], &variable_number[0], &operation, &variable_type[1], &variable_number[1]);
	// Caso de atribuicao.
	if (matches == 3)
	{

		if (variable_type[0] == 'c')
			printf("    movl $%d, %d(%%rbp)\n", variable_number[0],
				stack[main_variable - 1].offset);

		if (variable_type[0] == 'v')
		{
			printf("    movl %d(%%rbp), %%eax\n",
				stack[variable_number[0] - 1].offset);
			printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable - 1].offset);
		}

		if (variable_type[0] == 'p')
		{
			if (variable_number[0] == 1)
				printf("    movl %%edi, %d(%%rbp)\n", stack[main_variable - 1].offset);
			else if (variable_number[0] == 2)
				printf("    movl %%esi, %d(%%rbp)\n", stack[main_variable - 1].offset);
			else
				printf("    movl %%edx, %d(%%rbp)\n", stack[main_variable - 1].offset);
		}
	}
	// caso seja divisão
	if (operation == '/')
	{
		char dividend[10], divisor[10];
		if (variable_type[0] == 'c')
		{
			sprintf(dividend, "$%d", variable_type[0]);
		}
		if (variable_type[0] == 'v')
		{
			sprintf(dividend, "%d(%%rbp)", stack[variable_number[0] - 1].offset);
		}
		if (variable_type[0] == 'p')
		{
			if (variable_number[0] == 1)
				strcpy(dividend, "%%edi");
			if (variable_number[0] == 2)
				strcpy(dividend, "%%esi");
			if (variable_number[0] == 3)
				strcpy(dividend, "%%edx");
		}
		if (variable_type[1] == 'c')
		{
			sprintf(divisor, "$%d", variable_type[1]);
		}
		if (variable_type[1] == 'v')
		{
			sprintf(divisor, "%d(%%rbp)", stack[variable_number[1] - 1].offset);
		}
		if (variable_type[1] == 'p')
		{
			if (variable_number[1] == 1)
				strcpy(divisor, "%%edi");
			if (variable_number[1] == 2)
				strcpy(divisor, "%%esi");
			if (variable_number[1] == 3)
				strcpy(divisor, "%%edx");
		}

		printf("    movl %s, %%ecx\n", divisor);
		printf("    movl %s, %%eax\n", dividend);
		printf("    cltd\n");
		printf("    idivl %%ecx\n");
		printf("    movl %%eax, %d(%%rbp)\n\n", stack[main_variable - 1].offset);
	}

	// Aqui é designado qual tipo de operação ira ser executada entre soma,
	// subtração e multiplição.
	if (operation != '0' && operation != '/')
	{
		char op[6];
		if (operation == '+')
			strcpy(op, "addl");
		if (operation == '-')
			strcpy(op, "subl");
		if (operation == '*')
			strcpy(op, "imull");

		if (variable_type[0] == 'c')
		{

			if (variable_type[1] == 'c')
			{
				printf("    movl $%d, %%eax\n", variable_number[0]);
				printf("    %s $%d, %%eax\n", op, variable_number[1]);
				printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable - 1].offset);
			}

			if (variable_type[1] == 'v')
			{
				printf("    movl %d(%%rbp), %%eax\n",
					stack[variable_number[1] - 1].offset);
				printf("    %s $%d, %%eax\n", op, variable_number[0]);
				printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable - 1].offset);
			}

			if (variable_type[1] == 'p')
			{
				if (variable_number[1] == 1)
				{
					printf("    movl $%d, %%eax\n", variable_number[0]);
					printf("    %s %%edi, %%eax\n", op);
					printf("    movl %%eax, %d(%%rbp)\n",
						stack[main_variable - 1].offset);
				}
				else if (variable_number[1] == 2)
				{
					printf("    movl $%d, %%eax\n", variable_number[0]);
					printf("    %s %%esi, %%eax\n", op);
					printf("    movl %%eax, %d(%%rbp)\n",
						stack[main_variable - 1].offset);
				}
				else
				{
					printf("    movl $%d, %%eax\n", variable_number[0]);
					printf("    %s %%edx, %%eax\n", op);
					printf("    movl %%eax, %d(%%rbp)\n",
						stack[main_variable - 1].offset);
				}
			}
		}

		if (variable_type[0] == 'v')
		{

			if (variable_type[1] == 'c')
			{
				printf("    movl %d(%%rbp), %%eax\n",
					stack[variable_number[0] - 1].offset);
				printf("    %s $%d, %%eax\n", op, variable_number[1]);
				printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable - 1].offset);
			}

			if (variable_type[1] == 'v')
			{
				printf("    movl %d(%%rbp), %%eax\n",
					stack[variable_number[0] - 1].offset);
				printf("    %s %d(%%rbp), %%eax\n", op,
					stack[variable_number[1] - 1].offset);
				printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable - 1].offset);
			}

			if (variable_type[1] == 'p')
			{
				if (variable_number[1] == 1)
				{
					printf("    movl %d(%%rbp), %%eax\n",
						stack[variable_number[0] - 1].offset);
					printf("    %s %%edi, %%eax\n", op);
					printf("    movl %%eax, %d(%%rbp)\n",
						stack[main_variable - 1].offset);
				}
				else if (variable_number[1] == 2)
				{
					printf("    movl %d(%%rbp), %%eax\n",
						stack[variable_number[0] - 1].offset);
					printf("    %s %%esi, %%eax\n", op);
					printf("    movl %%eax, %d(%%rbp)\n",
						stack[main_variable - 1].offset);
				}
				else
				{
					printf("    movl %d(%%rbp), %%eax\n",
						stack[variable_number[0] - 1].offset);
					printf("    %s %%edx, %%eax\n", op);
					printf("    movl %%eax, %d(%%rbp)\n",
						stack[main_variable - 1].offset);
				}
			}
		}

		if (variable_type[0] == 'p')
		{
			if (variable_number[0] == 1)
			{
				if (variable_type[1] == 'c')
				{
					printf("    movl $%d, %%eax\n", variable_number[1]);
					printf("    %s %%edi, %%eax\n", op);
					printf("    movl %%eax, %d(%%rbp)\n",
						stack[main_variable - 1].offset);
				}

				if (variable_type[1] == 'v')
				{
					printf("    movl %d(%%rbp), %%eax\n",
						stack[variable_number[1] - 1].offset);
					printf("    %s %%edi, %%eax\n", op);
					printf("    movl %%eax, %d(%%rbp)\n",
						stack[main_variable - 1].offset);
				}
				if (variable_type[1] == 'p')
				{
					if (variable_number[1] == 1)
					{
						printf("    movl %%edi, %%eax\n");
						printf("    %s %%edi, %%eax\n", op);
						printf("    movl %%eax, %d(%%rbp)\n",
							stack[main_variable - 1].offset);
					}
					else if (variable_number[1] == 2)
					{
						printf("    movl %%edi, %%eax\n");
						printf("    %s %%esi, %%eax\n", op);
						printf("    movl %%eax, %d(%%rbp)\n",
							stack[main_variable - 1].offset);
					}
					else
					{
						printf("    movl %%edi, %%eax\n");
						printf("    %s %%edx, %%eax\n", op);
						printf("    movl %%eax, %d(%%rbp)\n",
							stack[main_variable - 1].offset);
					}
				}
			}
			else if (variable_number[0] == 2)
			{
				if (variable_type[1] == 'c')
				{
					printf("    movl $%d, %%eax\n", variable_number[1]);
					printf("    %s %%esi, %%eax\n", op);
					printf("    movl %%eax, %d(%%rbp)\n",
						stack[main_variable - 1].offset);
				}

				if (variable_type[1] == 'v')
				{
					printf("    movl %d(%%rbp), %%eax\n",
						stack[variable_number[1] - 1].offset);
					printf("    %s %%esi, %%eax\n", op);
					printf("    movl %%eax, %d(%%rbp)\n",
						stack[main_variable - 1].offset);
				}
				if (variable_type[1] == 'p')
				{
					if (variable_number[1] == 1)
					{
						printf("    movl %%esi, %%eax\n");
						printf("    %s %%edi, %%eax\n", op);
						printf("    movl %%eax, %d(%%rbp)\n",
							stack[main_variable - 1].offset);
					}
					else if (variable_number[1] == 2)
					{
						printf("    movl %%esi, %%eax\n");
						printf("    %s %%esi, %%eax\n", op);
						printf("    movl %%eax, %d(%%rbp)\n",
							stack[main_variable - 1].offset);
					}
					else
					{
						printf("    movl %%esi, %%eax\n");
						printf("    %s %%edx, %%eax\n", op);
						printf("    movl %%eax, %d(%%rbp)\n",
							stack[main_variable - 1].offset);
					}
				}
			}
			else
			{
				if (variable_type[1] == 'c')
				{
					printf("    movl $%d, %%eax\n", variable_number[1]);
					printf("    %s %%edx, %%eax\n", op);
					printf("    movl %%eax, %d(%%rbp)\n",
						stack[main_variable - 1].offset);
				}

				if (variable_type[1] == 'v')
				{
					printf("    movl %d(%%rbp), %%eax\n",
						stack[variable_number[1] - 1].offset);
					printf("    %s %%edx, %%eax\n", op);
					printf("    movl %%eax, %d(%%rbp)\n",
						stack[main_variable - 1].offset);
				}
				if (variable_type[1] == 'p')
				{
					if (variable_number[1] == 1)
					{
						printf("    movl %%edx, %%eax\n");
						printf("    %s %%edi, %%eax\n", op);
						printf("    movl %%eax, %d(%%rbp)\n",
							stack[main_variable - 1].offset);
					}
					else if (variable_number[1] == 2)
					{
						printf("    movl %%edx, %%eax\n");
						printf("    %s %%esi, %%eax\n", op);
						printf("    movl %%eax, %d(%%rbp)\n",
							stack[main_variable - 1].offset);
					}
					else
					{
						printf("    movl %%edx, %%eax\n");
						printf("    %s %%edx, %%eax\n", op);
						printf("    movl %%eax, %d(%%rbp)\n",
							stack[main_variable - 1].offset);
					}
				}
			}
		}
	}
	matches = sscanf(buffer, "vi%d = call", &main_variable);
	if (matches == 1)
		call_function();
}

void call_function()
{
	int matches = 0;	// numero de acertos na funcao strncmp.
	char param[3] = { '0', '0', '0' }, param_t[3];	// Parametro e tipo do parametro
	int p_num[3], variable_n,
		f_num;	// numero do parametro, numero da variavel, numero função
	char inst[3][5];	// instrução de atribuição de parametros
	char instp[5], type_param[3][6];	// instrução para salvar e recuperar a pilha

	matches = sscanf(buffer, "vi%d = call f%d %c%c%d %c%c%d %c%c%d", &variable_n, &f_num, &param[0], &param_t[0], &p_num[0], &param[1], &param_t[1], &p_num[1], &param[2], &param_t[2], &p_num[2]);

	if (parameter[0].size != 0)
	{
		// se houver pelo menos 1 parametro
		printf("    #salvar pilha\n");
	}
	for (int i = 0; i < 3; ++i)
	{
		if (parameter[i].size == 0)
			break;
		if (parameter[i].size == 2)
		{
			strcpy(instp, "movq");
			if (i == 0)
			{
				strcpy(type_param[i], "%rdi");
			}
			if (i == 1)
			{
				strcpy(type_param[i], "%rsi");
			}
			if (i == 2)
			{
				strcpy(type_param[i], "%rdx");
			}
		}
		if (parameter[i].size == 1)
		{
			strcpy(instp, "movl");
			if (i == 0)
			{
				strcpy(type_param[i], "%edi");
			}
			if (i == 1)
			{
				strcpy(type_param[i], "%esi");
			}
			if (i == 2)
			{
				strcpy(type_param[i], "%edx");
			}
		}
		printf("    %s %s, %d(%%rbp)\n", instp, type_param[i], parameter[i].offset);
	}

	printf("\n");

	for (int i = 0; i < 3; ++i)
	{
		if (param[i] == 'v' && param_t[i] == 'a')
		{
			strcpy(inst[i], "leaq");
		}
		else if (param[i] == 'p' && param_t[i] == 'a')
		{
			strcpy(inst[i], "movq");
		}
		else if (param[i] != 0)
		{
			strcpy(inst[i], "movl");
		}
	}

	int i = 0;
	for (int j = 5; j <= matches; j = j + 3)
	{
		char ed[3];
		if (i == 0)
			strcpy(ed, "di");
		if (i == 1)
			strcpy(ed, "si");
		if (i == 2)
			strcpy(ed, "dx");

		if (param[i] == 'c')
			printf("    %s $%d, %%e%s\n", inst[i], p_num[i], ed);
		if (param[i] == 'v')
		{
			if (param_t[i] == 'a')
			{
				printf("    %s %d(%%rbp), %%r%s\n", inst[i], stack[p_num[i] - 1].offset,
					ed);
			}
			if (param_t[i] == 'i')
			{
				printf("    %s %d(%%rbp), %%e%s\n", inst[i], stack[p_num[i] - 1].offset,
					ed);
			}
		}
		if (param[i] == 'p')
		{
			if (param_t[i] == 'a')
			{
				printf("    %s %d(%%rbp), %%r%s\n", inst[i],
					parameter[p_num[i] - 1].offset, ed);
			}
			if (param_t[i] == 'i')
			{
				printf("    %s %d(%%rbp), %%e%s\n", inst[i],
					parameter[p_num[i] - 1].offset, ed);
			}
		}
		i++;
	}

	printf("    call f%d\n\n", f_num);

	printf("    movl %%eax, %d(%%rbp)\n\n",
		stack[variable_n - 1].offset);	// passa o valor para a variavel

	if (parameter[0].size != 0)
	{
		// se houver pelo menos 1 parametro
		printf("    #recuperar pilha\n");
	}
	for (i = 0; i < 3; ++i)
	{
		if (parameter[i].size == 0)
			break;
		printf("    %s %d(%%rbp), %s\n", instp, parameter[i].offset, type_param[i]);
	}
	printf("\n");
}

void process_vector_getter()
{
	// Buffer atual: "get CaN index ciN to CiN"

	char vec_type;	// variável local ou parâmetro
	int vec_index;	// índice do vetor

	int vec_offset;	// A posição a ser acessada

	char target_type;	// variável local ou parâmetro
	int target_index;	// índice do target

	sscanf(buffer, "get %ca%d index ci%d to %ci%d", &vec_type, &vec_index, &vec_offset, &target_type, &target_index);

	printf("       #Acessando array.\n");
	printf("       #Array: %ca%d\n", vec_type, vec_index);
	printf("       #Index: %d\n", vec_offset);
	printf("       #Destino: %ci%d\n", target_type, target_index);

	char register_pointer[4];
	int stack_offset;

	if (vec_type == 'v')
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

	if (target_type == 'p')
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

	sscanf(buffer, "set %ca%d index ci%d with %ci%d", &vec_type, &vec_index, &vec_offset, &base_type, &base_index);

	printf("       #Escrevendo no array.\n");
	printf("       #Array: %ca%d\n", vec_type, vec_index);
	printf("       #Index: %d\n", vec_offset);
	printf("       #Valor: %ci%d\n", base_type, base_index);

	char base_register[4];
	int base_offset;

	if (base_type == 'p')
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
	else	// base_type == 'c' (constante)
	{
		printf("    movl $%d, %%eax\n", base_index);
	}

	char register_pointer[4];
	int stack_offset;

	if (vec_type == 'v')
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

void process_return()
{
	// Buffer atual: "return CiN"

	char return_type;
	int return_value;

	sscanf(buffer, "return %ci%d", &return_type, &return_value);
	printf("        #Retornando...\n");
	printf("        #Valor de retorno: %ci%d\n", return_type, return_value);

	if (return_type == 'c')
		printf("    movl $%d, %%eax\n", return_value);
	else if (return_type == 'p')
	{
		char return_register[4];

		switch (return_value)
		{
			case 1:
				strcpy(return_register, "edi");
				break;
			case 2:
				strcpy(return_register, "esi");
				break;
			case 3:
				strcpy(return_register, "edx");
				break;
		}

		printf("    movl %%%s, %%eax\n", return_register);
	}
	else	// return_type == 'v'
	{
		printf("    movl %d(%%rbp), %%eax\n", stack[return_value - 1].offset);
	}
}