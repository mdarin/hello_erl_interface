#include <stdio.h>

void ctest1(int *);
void ctest2(int *);

int main(void)
{
	int x = 0;
	ctest1(&x);
	printf("ctest1() -> %d\n", x);
	ctest2(&x);
	printf("ctest2() -> %d\n", x);
	return 0;
}
