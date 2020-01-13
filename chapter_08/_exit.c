#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int val;

void func(void)
{
	printf("atexit func\n");
}

void subfunc(void)
{
	_exit(val);

	printf("this point is unreachable too!\n");
}

int main(int argc, char *argv[])
{
	int ret;

	ret = atexit(func);
	if (ret) {
		fprintf(stderr, "cannot set atexit func\n");
		return -1;
	}

	if (argc >= 2)
		val = atoi(argv[1]);

	printf("this is a message");

	subfunc();

	printf("this point is unreachable!\n");

	return 0;
}
