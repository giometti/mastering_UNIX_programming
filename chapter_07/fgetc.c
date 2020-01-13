#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	size_t size = BUFSIZ;
	char c;
	int ret;

        if (argc > 1)
		size = atoi(argv[1]);
	if (size <= 1) {
                fprintf(stderr, "invalid size, must be greater than 1\n");
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
		ret = fgetc(stdin);
		if (ret == EOF) {
			if (ferror(stdin)) {
				fprintf(stderr, "error in reading\n");
				return -1;
			}
			break;
		}
		c = (char) ret;

		/* Write data to output file */
		ret = fputc(c, stdout);
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
