#include <stdio.h>

#define BUF_SIZE	256
char buf[BUF_SIZE];

void dump(FILE *fp)
{
	int c;
	while ((c = fgetc(fp)) != EOF)
		printf("%c", c);
	printf("\n");
}

int main(void)
{
	FILE *fp;

	fp = fmemopen(buf, BUF_SIZE, "r+");
	if (!fp) {
		perror("fmemopen");
		return -1;
	}

	/* Write something in the stream */
	fprintf(fp, "the buffer is %d bytes long\n", BUF_SIZE);

	/* Rewind the "current position" pointer */
	rewind(fp);

	printf("Data in the stream:\n");
	dump(fp);

	fclose(fp);

	return 0;
}
