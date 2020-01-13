#include <stdio.h>

int main(int argc, char *argv[])
{
	int n;

	for (n = 0; n < argc; n++)
		printf("argv[%d]=\"%s\"\n", n, argv[n]);

	return 0;
}
