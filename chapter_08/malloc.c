#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	size_t size;
	void *ptr, *nptr;

	/* Parse the command line */
	if (argc < 2) {
		fprintf(stderr,
			"usage: %s <size>\n", argv[0]);
		return -1;
	}
	size = atoi(argv[1]);

	/* Try memory allocation */
	ptr = malloc(size);
	if (ptr == NULL) {
		perror("malloc");
		return -1;
	}
	printf("malloc(%ld) returned %p\n", size, ptr);
	free(ptr);

	/* Try calloc) of doubled space and then realloc()
	 * of doubled-doubed space.
	 */
	ptr = calloc(2, size);
	if (ptr == NULL) {
		perror("malloc");
		return -1;
	}
	printf("calloc(2, %ld) returned %p\n", size, ptr);

	nptr = realloc(ptr, size * 2 * 2);
	if (ptr == NULL) {
		perror("malloc");
		return -1;
	}
	printf("realloc(%p, %ld) returned %p\n", ptr, size * 2 * 2, nptr);
	free(nptr);

	return 0;
}
