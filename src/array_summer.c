#include <stdio.h>

int f9000(int* nums);

int sum(int* vec)
{
	int sum = 0;

	for(int i = 0; i < 5; i++)
		sum += vec[i];

	return sum;
}

int main()
{
	int nums[5];

	for(int i = 0; i < 5; i++)
		scanf("%d", &nums[i]);

	printf("C - sum    = %d\n", sum(nums));
	printf("BPL - sum  = %d\n\n", f9000(nums));
}