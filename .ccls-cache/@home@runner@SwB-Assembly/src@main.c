#include <stdio.h>

int f1();
int f2(int a);
int f3(int a[], int b);

int main()
{
	int vet[] = {1, 2, 3, 4, 5};
	
	printf("f1: %d\n", f1());
	printf("f2: %d\n", f2(2));
	printf("f3: %d\n", f3(vet, 5));
}