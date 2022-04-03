#include <stdio.h>
#include <math.h>

int f9947()
{
	printf("Há duas soluções reais.\n");

	return 1;
}

int f9948()
{
	printf("Há uma solução real.\n");

	return 0;
}

int f9949()
{
	printf("Não há soluções reais.\n");

	return -1;
}

// Calculador de delta
int f9950(int a, int b, int c);

// Retorna se o delta é negativo.
int f9951(int delta)
{
	return delta < 0;
}

// Calcula o quadrado do delta
// Retorna se o resultado é 0
int f9952(int delta)
{
	double root = sqrt(delta);

	return root == 0;
}

int f9953(int delta)
{
	double root = sqrt(delta);

	return root > 0;
}

int f9961(int delta, int a, int b);
int f9962(int delta, int a, int b);

int main()
{
	int a;
	int b;
	int c;

	scanf("%d %d %d", &a, &b, &c);
	int delta = f9950(a, b, c);

	if (delta < 0)
		return 

	double sdelta = sqrt(delta);
	delta = (int)sdelta;
	
	if (sdelta != delta)
	{
		printf("Não é possível resolver essa equação.\n");
		printf("O delta precisa ser um quadrado perfeito.\n");
		return 0;
	}

	delta = (int) sdelta;

	if (delta != 0)
		printf("x = %d\n", f9961((int)sdelta, a, b));
	printf("x = %d\n", f9962((int)sdelta, a, b));

}