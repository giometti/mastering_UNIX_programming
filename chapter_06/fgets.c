#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE	(32 * BUFSIZ)

int main(int argc, char *argv[])
{
	size_t size = BUFSIZ;
	char buf[MAX_SIZE];
	char *ptr;
	int ret;

        if (argc > 1)
		size = atoi(argv[1]);
	if ((size <= 1) || (size > MAX_SIZE)) {
                fprintf(stderr, "invalid size, must be in [2,%d]\n",
			MAX_SIZE);
                return -1;
	}
	fprintf(stderr, "set buffer size to %ld\n", size);

	ret = setvbuf(stdin, NULL, _IOFBF, size);
	if (ret) {
		fprintf(stderr, "setvbuf error for stdin\n");
		return -1;
	}
	ret = setvbuf(stdout, NULL, _IOFBF, size);
	if (ret) {
		fprintf(stderr, "setvbuf error for stdout\n");
		return -1;
	}

	while (!feof(stdin)) {
		/* Read data from input file */
		ptr = fgets(buf, size, stdin);
		if (ptr == NULL) {
			if (ferror(stdin)) {
				fprintf(stderr, "error in reading\n");
				return -1;
			}
			break;
		}

		/* Write data to output file */
		ret = fputs(buf, stdout);
		if (ret == EOF) {
			if (ferror(stdout)) {
				fprintf(stderr, "error in writing\n");
				return -1;
			}
			break;
		}
	}

	return 0;
}
