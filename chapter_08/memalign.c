#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	size_t alignment, size;
	void *ptr;
	int ret;

	/* Parse the command line */
	if (argc < 3) {
		fprintf(stderr,
			"usage: %s <align-size> <size>\n", argv[0]);
		return -1;
	}
	alignment = atoi(argv[1]);
	size = atoi(argv[2]);

	/* Try memory allocation */
	ret = posix_memalign(&ptr, alignment, size);
	if (ret) {
		/* Set errno is such a way perror() may work correctly */
		errno = ret;
		perror("posix_memalign");
		return -1;
	}
	printf("posix_memalign(%ld, %ld) returned %p\n",
		alignment, size, ptr);
	free(ptr);

	return 0;
}
