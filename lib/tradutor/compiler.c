#include <stdio.h>
#include <string.h>

#include "base.h"  // Aqui estão definidos o buffer e o read_line()

int function_initialization();
void process_local_variables(int a);
void process_instructions();
void process_attribuition();
 
//Essas structs servem para salvarmos as informacoes necessarias e uteis das nossas variaveis locais para facilitar o uso do registrador da pilha correspondentes a uma variavel.
typedef struct stack_info
{
	int offset;
	unsigned int size;
} stack_info;

//temos no maximo 5 variaveis locais.
stack_info stack[5];
//temos tbm 3 parametros que podem vir com a funcao
stack_info parameter[3];

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
	if(matches == 3){
		
    if(variable_type[0] == 'c') 
			printf("    movl $%d, %d(%%rbp)\n", variable_number[0], stack[main_variable-1].offset);
		
    if(variable_type[0] == 'v'){
			printf("    movl %d(%%rbp), %%eax\n", stack[variable_number[0]-1].offset);
      printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
    }
		
    if(variable_type[0] == 'p'){
			if(variable_number[0] == 1) 
        printf("    movl %%edi, %d(%%rbp)\n", stack[main_variable-1].offset);
			else if(variable_number[0] == 2) 
        printf("    movl %%esi, %d(%%rbp)\n", stack[main_variable-1].offset);
			else 
        printf("    movl %%edx, %d(%%rbp)\n", stack[main_variable-1].offset);
		}
	}
  
  if(operation != ' '){
    char op[6];
    if(operation == '+')
      strcpy(op, "addl");
    if(operation == '-')
      strcpy(op, "subl");
    if(operation == '*')
      strcpy(op, "imull");
    
    if(variable_type[0] == 'c'){
     
      if(variable_type[1] == 'c'){
        printf("    movl $%d, %%eax\n", variable_number[0]);
        printf("    %s $%d, %%eax\n", op, variable_number[1]);
        printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
      }
      
      if(variable_type[1] == 'v'){
        printf("    movl %d(%%rbp), %%eax\n", stack[variable_number[1]-1].offset);
        printf("    %s $%d, %%eax\n", op, variable_number[0]);
        printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
      }

      if(variable_type[1] == 'p'){
        if(variable_number[1] == 1){
          printf("    movl $%d, %%eax\n", variable_number[0]);
          printf("    %s %%edi, %%eax\n", op);
          printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
        }
			  else if(variable_number[1] == 2){
          printf("    movl $%d, %%eax\n", variable_number[0]);
          printf("    %s %%esi, %%eax\n", op);
          printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
        }
			  else{
          printf("    movl $%d, %%eax\n", variable_number[0]);
          printf("    %s %%edx, %%eax\n", op);
          printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
        }  
      }
      
    }

    if(variable_type[0] == 'v'){

      if(variable_type[1] == 'c'){
        printf("    movl %d(%%rbp), %%eax\n", stack[variable_number[0]-1].offset);
        printf("    %s $%d, %%eax\n", op, variable_number[1]);
        printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
      }
      
      if(variable_type[1] == 'v'){
        printf("    movl %d(%%rbp), %%eax\n", stack[variable_number[0]-1].offset);
        printf("    %s %d(%%rbp), %%eax\n", op, stack[variable_number[1]-1].offset);
        printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
      }

      if(variable_type[1] == 'p'){
        if(variable_number[1] == 1){
          printf("    movl %d(%%rbp), %%eax\n", stack[variable_number[0]-1].offset);
          printf("    %s %%edi, %%eax\n", op);
          printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
        }
			  else if(variable_number[1] == 2){
          printf("    movl %d(%%rbp), %%eax\n", stack[variable_number[0]-1].offset);
          printf("    %s %%esi, %%eax\n", op);
          printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
        }
			  else{
          printf("    movl %d(%%rbp), %%eax\n", stack[variable_number[0]-1].offset);
          printf("    %s %%edx, %%eax\n", op);
          printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
        }  
      }
    }

    if(variable_type[0] == 'p'){
      if(variable_number[0] == 1){ 
        if(variable_type[1] == 'c'){
          printf("    movl $%d, %%eax\n", variable_number[1]);
          printf("    %s %%edi, %%eax\n", op);
          printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
        }
          
        if(variable_type[1] == 'v'){
          printf("    movl %d(%%rbp), %%eax\n", stack[variable_number[1]-1].offset);
          printf("    %s %%edi, %%eax\n", op);
          printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
        }
        if(variable_type[1] == 'p'){
          if(variable_number[1] == 1){
            printf("    movl %%edi, %%eax\n");
            printf("    %s %%edi, %%eax\n", op);
            printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
          }
  			  else if(variable_number[1] == 2){
            printf("    movl %%edi, %%eax\n");
            printf("    %s %%esi, %%eax\n", op);
            printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
          }
  			  else{
            printf("    movl %%edi, %%eax\n");
            printf("    %s %%edx, %%eax\n", op);
            printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
          }
        }
      }
			else if(variable_number[0] == 2){ 
         if(variable_type[1] == 'c'){
          printf("    movl $%d, %%eax\n", variable_number[1]);
          printf("    %s %%esi, %%eax\n", op);
          printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
        }
          
        if(variable_type[1] == 'v'){
          printf("    movl %d(%%rbp), %%eax\n", stack[variable_number[1]-1].offset);
          printf("    %s %%esi, %%eax\n", op);
          printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
        }
        if(variable_type[1] == 'p'){
          if(variable_number[1] == 1){
            printf("    movl %%esi, %%eax\n");
            printf("    %s %%edi, %%eax\n", op);
            printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
          }
  			  else if(variable_number[1] == 2){
            printf("    movl %%esi, %%eax\n");
            printf("    %s %%esi, %%eax\n", op);
            printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
          }
  			  else{
            printf("    movl %%esi, %%eax\n");
            printf("    %s %%edx, %%eax\n", op);
            printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
          }
        }
      }
        
			else{
        if(variable_type[1] == 'c'){
          printf("    movl $%d, %%eax\n", variable_number[1]);
          printf("    %s %%edx, %%eax\n", op);
          printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
        }
          
        if(variable_type[1] == 'v'){
          printf("    movl %d(%%rbp), %%eax\n", stack[variable_number[1]-1].offset);
          printf("    %s %%edx, %%eax\n", op);
          printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
        }
        if(variable_type[1] == 'p'){
          if(variable_number[1] == 1){
            printf("    movl %%edx, %%eax\n");
            printf("    %s %%edi, %%eax\n", op);
            printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
          }
  			  else if(variable_number[1] == 2){
            printf("    movl %%edx, %%eax\n");
            printf("    %s %%esi, %%eax\n", op);
            printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
          }
  			  else{
            printf("    movl %%edx, %%eax\n");
            printf("    %s %%edx, %%eax\n", op);
            printf("    movl %%eax, %d(%%rbp)\n", stack[main_variable-1].offset);
          }
        }
      } 
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

	int matches = sscanf(buffer, "function f%d p%c1 p%c2 p%c3", &function_number,
						 &parameter_types[0], &parameter_types[1], &parameter_types[2]);

  for(int i = 0; i<matches; i++){
    if(parameter_types[i] == 'i') parameter[i].offset = 4;
    if(parameter_types[i] == 'a') parameter[i].offset = 8;
  }

	// Sabemos que pelo menos o primeiro %d foi lido com sucesso.
	// Para descobrir a quantidade de parâmetros. Devemos olhar quantos matches foram feitos.

	printf(".globl f%d\n", function_number);
	printf("f%d:\n", function_number);

	return matches;
}

void process_local_variables(int a)
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
      printf("#vi%d: %d\n", index, stack[index-1].offset);
			continue;
		}
		if(strncmp(buffer, "vet", 3) == 0)
		{
			int vector_size = 0;
			sscanf(buffer, "vet va%d size ci%d", &index, &vector_size);

			required_bytes += 4 * vector_size;

			stack[index-1].size = vector_size;
			stack[index-1].offset = required_bytes * (-1);
      printf("#va%d: %d\n", index, stack[index-1].offset);
		}


	} while(strncmp(buffer, "enddef", 6) != 0);

  //Adicionando os parametros à pilha em caso de chamada de funcoes 
  for(int i = 0; i < a; i++){
    //Para paremetros do tipo inteiro
    if(parameter[i].offset == 4){
      required_bytes += 4;
      parameter[i].offset = required_bytes * (-1);
      printf("#pi%d: %d\n", i+1, parameter[i].offset);
    }else if(parameter[i].offset == 8){ //Para parametros ponteiros
      required_bytes += 4;

      //É necessario garantir alinhamento do tipo ponteiro com 8
      while(required_bytes%8 != 0)
        required_bytes += 4;
      parameter[i].offset = required_bytes * (-1);
      printf("#pa%d: %d\n", i+1, parameter[i].offset);
    }
  }

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