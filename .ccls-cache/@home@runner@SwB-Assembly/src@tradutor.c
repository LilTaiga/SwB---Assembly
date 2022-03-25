#include <stdio.h>
#include <string.h>

#include "base.h"
#include "compiler.c"

int main()
{
	while(read_line())
	{
		if(strncmp(buffer, "function", 8) == 0)
			compile_function();
	}
}