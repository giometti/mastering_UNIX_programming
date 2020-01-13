#include <stdio.h>
#include <setjmp.h>

int main(int argc, char *argv[])
{
	jmp_buf env;
	int ret;

	ret = setjmp(env);
	printf("setjmp() returned %d\n", ret);
	if (ret)
		return 0;

	longjmp(env, 1);

	printf("never printed!\n");

	return 0;
}
