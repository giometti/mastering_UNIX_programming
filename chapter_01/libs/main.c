#include <stdio.h>
#include "iops.h"

int main(void)
{
	int a = 10, b = 3;

	printf("%d + %d = %d\n", a, b, isum(a,b));
	printf("%d - %d = %d\n", a, b, isub(a,b));
	printf("%d * %d = %d\n", a, b, imul(a,b));
	printf("%d / %d = %d\n", a, b, idiv(a,b));

	return 0;
}
