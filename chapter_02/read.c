#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "wrappers.h"

#define TMP_FILE	"/tmp/file"

#define BUF_SIZE	16

int main(void)
{
	int fd;
	int nr, nw;
	char buf[BUF_SIZE];

	fd = open(TMP_FILE, O_RDONLY);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	do {
		nr = read(fd, buf, BUF_SIZE);
		if (nr < 0) {
			perror("read");
			return -1;
		}

		nw = writen(STDOUT_FILENO, buf, nr);
		if (nw < nr) {
			perror("write");
			return -1;
		}

		sleep(1);
	} while (nr > 0);

	return 0;
}
