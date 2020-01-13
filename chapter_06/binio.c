#include <stdio.h>

int main(void)
{
	FILE *fp;
	int outdata[4] = { 10, -3, 200, 0 };
	int indata[4];
	int n;

	/* Open a file for writing */
	fp = fopen("file.txt", "w");
	if (!fp) {
		perror("fopen");
		return -1;
	}

	/* Try to write data to file */
	n = fwrite(outdata, sizeof(int), 4, fp);
	if (n < 4) {
		fprintf(stderr, "cannot fwrite\n");
		return -1;
	}
	printf("written %d, %d, %d, %d\n",
		outdata[0], outdata[1],
		outdata[2], outdata[3]);

	/* Writing done */
	fclose(fp);

	/* Open a file for reading */
	fp = fopen("file.txt", "r");
	if (!fp) {
		perror("fopen");
		return -1;
	}

	/* Try to read data from file */
	n = fread(indata, sizeof(int), 4, fp);
	if (n < 4) {
		if (ferror(fp))
			fprintf(stderr, "cannot fread\n");
		if (feof(fp))
			fprintf(stderr, "too few data to read\n");
		return -1;
	}
	printf("read %d, %d, %d, %d\n",
		indata[0], indata[1],
		indata[2], indata[3]);

	/* Reading done */
	fclose(fp);

	return 0;
}
