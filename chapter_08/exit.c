#include <stdio.h>
#include <stdlib.h>

int val;

void subfunc(void)
{
	exit(val);

	printf("this point is unreachable too!\n");
}

int main(int argc, char *argv[])
{
	if (argc >= 2)
		val = atoi(argv[1]);

	printf("this is a message");

	subfunc();

	printf("this point is unreachable!\n");

	return 0;
}
