#include <stdio.h>

void status(FILE *fp)
{
	printf("stream error status is %s\n",
		ferror(fp) ? "on" : "off");
}

int main(void)
{
	FILE *fp;
	char c;

	/* Open a file for writing */
	fp = fopen("file.txt", "w");
	if (!fp) {
		perror("fopen");
		return -1;
	}
	printf("file descriptor number is %d\n", fileno(fp));

	/* Try to read data from file */
	while (!ferror(fp))
		c = fgetc(fp);
	status(fp);

	/* Clear the error status and re-check it */
	clearerr(fp);
	status(fp);

	fclose(fp);

	return 0;
}
