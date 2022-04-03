#include <stdio.h>

int f9999(int a);

int fatorial(int num)
{
	if(num == 0)
		return 1;

	return num * fatorial(num - 1);
}

int main()
{
	printf("Fatorial:\n");

	for(int i = 0; i <= 10; i++)
	{
		printf("C   - fatorial de %d = %d\n", i, fatorial(i));
		printf("BPL - fatorial de %d = %d\n\n", i, f9999(i));
	}

	printf("fim\n");
}