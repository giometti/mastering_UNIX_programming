#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "wrappers.h"

#define MAX_SIZE	(4 << 10)	/* 4KB */

int main(void)
{
	int fd, n;
	char buf[MAX_SIZE];
	int ret;

	ret = open("data.bin", O_WRONLY | O_CREAT,
			S_IWUSR);
	if (ret < 0) {
		perror("open");
		return -1;
	}
	fd = ret;

	for (n = 0; n < 128; n++) {
		ret = write(fd, buf, n);
		if (ret < 0) {
			perror("write");
			return -1;
		}
	}

	close(fd);

	return 0;
}
