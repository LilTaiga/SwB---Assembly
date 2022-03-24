#include <stdio.h>
#include <string.h>

char buffer[1024];


// Lê uma linha da entrada e a armazena em buffer.
// Caso ele leia com sucesso, ele retorna 1.
// Em caso de erro ou EOF, ele retorna 0.
int read_line()
{
	char* result = fgets(buffer, 1024, stdin);
	return result != NULL;
}

// buffer = "function fN pxN pxN pxN pxN pxN"
// 
void parse_function_arguments()
{
	int offset; //Usar para navegar no buffer / offset = 0 primeira posição

	/*for(offset = 9; buffer[offset] != '\n'; offset++)
	{
		
	}*/

	int function_name;

	char argument_type[5];
	int argument_number[5];

	int match = fscanf(buffer, "function f%d p%c%d %c%d p%c%d p%c%d p%c%d",
		&function_name, 
		&argument_type[0], &argument_number[0], 
		&argument_type[1], &argument_number[1], 
		&argument_type[2], &argument_number[2], 
		&argument_type[3], &argument_number[3], 
		&argument_type[4], &argument_number[4]);

	
}

// buffer = "def"
void parse_function_variables()
{
	
}


void parse_function_instructions()
{
	
}

void parse_function_call()
{
	
}

// Encontramos uma função.
// Devemos transformar o corpo dela em Assembly.
void translate_function()
{
	// Processar os argumentos da função
	parse_function_arguments();

	// Processar a definição de variáveis locais
	parse_function_variables();

	// Processar as instruções da função
	parse_function_instructions();
}

int main()
{
	// Lê uma linha da entrada.
	// Continua lendo enquanto não encontrar EOF, ou um erro de leitura.
	while(read_line())
	{
		if(strstr(buffer, "function"))
			parse_function_arguments();
	}
}