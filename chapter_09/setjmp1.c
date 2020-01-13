#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

int func4(jmp_buf env, int i)
{
	if (i == 0)
		longjmp(env, 1);

	return 14 % i;
}
  
int func3(jmp_buf env, int i, int j)
{
	return func4(env, i) + func4(env, j - 2);
}

int func2(jmp_buf env, int i, int j, int k)
{
	return func3(env, i - 1, k) + func3(env, j + 4, k);
}

int func1(jmp_buf env, int i, int j, int k, int l)
{
	return func2(env, i, j, k + 1);
}

int main(int argc, char *argv[])
{
	jmp_buf env;
	int i, j, k, l;
	int ret;

	if (argc < 5) {
		fprintf(stderr, "usage: %s <i> <j> <k> <l>\n", argv[0]);
		return -1;
	}

	/* Here we check if nested functions detect an error */
	ret = setjmp(env);
	if (ret != 0) {
		fprintf(stderr, "bad values!\n");
		return -1;
	}

	/* Convert the input values and then call func1() */
	i = atoi(argv[1]);
	j = atoi(argv[2]);
	k = atoi(argv[3]);
	l = atoi(argv[4]);
	printf("func1() returned %d\n", func1(env, i, j, k, l));

	return 0;
}
