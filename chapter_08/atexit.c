#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void func1(void)
{
	printf("atexit func1\n");
}

void func2(void)
{
	printf("atexit func2\n");
}

int main(void)
{
	long atexit_max;
	int ret;

#ifdef ATEXIT_MAX
	atexit_max = ATEXIT_MAX;
#else
	errno = 0;
	atexit_max = sysconf(_SC_ATEXIT_MAX);
	if (atexit_max < 0) {
		if (errno == 0) {
			fprintf(stderr, "_SC_ATEXIT_MAX limit not supported\n");
		} else {
			perror("sysconf");
			return -1;
		}
	}
#endif
	printf("ATEXIT_MAX = %ld\n", atexit_max);

	ret = atexit(func1);
	if (ret) {
		fprintf(stderr, "cannot set atexit func1\n");
		return -1;
	}

	ret = atexit(func2);
	if (ret) {
		fprintf(stderr, "cannot set atexit func2\n");
		return -1;
	}

	printf("press ENTER to continue >");
	getchar();

	return 0;
}
