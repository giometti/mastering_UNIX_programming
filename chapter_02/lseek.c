#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	char c;
	off_t pos;
	int ret;

	/* Check if the file is lseek()-able */
	ret = lseek(STDIN_FILENO, 0, SEEK_CUR);
	if (ret < 0) {
		perror("cannot lseek()");
		return -1;
	}

	/* Move the offset to position -16 (16 bytes from the end of
	 * the file).
	 */
	pos = lseek(STDIN_FILENO, -16, SEEK_END);
	if (pos < 0) {
		perror("cannot move to position -16");
		return -1;
	}
	
	/* Read and then print out the data */
	ret = read(STDIN_FILENO, &c, 1);
	if (ret == 1)
		printf("file@%ld=%c\n", pos, c);

	return 0;
}
