#include <stdio.h>

int main(void)
{
	FILE *fp;
	int i;
	char c;

	/* Open a file for writing */
	fp = fopen("file.txt", "r");
	if (!fp) {
		perror("fopen");
		return -1;
	}

	/* Start reading first three bytes */
	for (i = 0; i < 3; i++) {
		c = fgetc(fp);
		if (ferror(fp) || feof(fp)) {
			fprintf(stderr, "cannot read\n");
			return -1;
		}
		printf("\ngot '%c'", c);
	}

	/* Do the unread */
	if (ungetc('x', fp) == EOF) {
		fprintf(stderr, "cannot unread\n");
		return -1;
	}
	printf(" but unread 'x'\n");

	/* Now continue reading the whole file */
	while (1) {
		c = fgetc(fp);
		if (ferror(fp)) {
			fprintf(stderr, "cannot read\n");
			return -1;
		}
		if (feof(fp))
			break;
		printf("got '%c'\n", c);
	}

	fclose(fp);

	return 0;
}
