#include <stdio.h>

#include "base.h"

char buffer[1024];

// Lê uma linha da entrada e a armazena em buffer.
// Caso ele leia com sucesso, ele retorna 1.
// Em caso de erro ou EOF, ele retorna 0.
int read_line()
{
	char* result = fgets(buffer, 1024, stdin);
  
	return result != NULL;
}