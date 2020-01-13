#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

int func1(char *s, jmp_buf env)
{
	int ret;

	ret = setjmp(env);
	printf("func1: setjmp() returned %d\n", ret);

	printf("func1: &s=%p\n", s);
	printf("func1: s=%s\n", s);

	return ret;
}

int func2(int i, jmp_buf env)
{
	printf("func2: i=%d\n", i);

	printf("func2: calling longjmp()\n");
	longjmp(env, i);
}

int main(int argc, char *argv[])
{
	jmp_buf env;
	int ret;

	ret = func1("foo", env);
	if (ret)
		return -1;

	func2(3, env);

	return 0;
}
