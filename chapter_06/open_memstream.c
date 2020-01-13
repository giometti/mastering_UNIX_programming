#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *fp;
	char *buf;
	size_t len;

	fp = open_memstream(&buf, &len);
        if (!fp) {
                perror("open_memstream");
                return -1;
        }

	/* Write something in the stream */
	fprintf(fp, "first write");
	fflush(fp);
	printf("buf=%s len=%zu\n", buf, len);

	/* Move to the beginning of the stream */
	rewind(fp);

	/* Write something else in the stream (overwriting
	 * old data)
	 */
	fprintf(fp, "second write");
	fclose(fp);
	printf("buf=%s len=%zu\n", buf, len);

	/* Must free the buffer! */
	free(buf);

	return 0;
}
