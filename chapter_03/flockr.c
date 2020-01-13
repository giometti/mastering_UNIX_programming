#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	char buf[32];
	struct flock fl;
	int ret;

	/* Open the file */
	fd = open("file.locked", O_RDONLY);
	if (fd < 0) {
		perror("open");
		return -1;
	}
	printf("file opened\n");

	/* Establish a read lock */
	fl.l_type   = F_RDLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start  = 0;        /* Offset from l_whence */
	fl.l_len    = 0;        /* length, 0 = to EOF   */
	fl.l_pid    = getpid(); /* our PID              */
	ret = fcntl(fd, F_SETLKW, &fl);
	if (ret < 0) {
		perror("fcntl(F_SETLKW)");
		return -1;
	}
	printf("read lock get\n");

	/* Do the read */
	ret = read(fd, buf, 32);
	if (ret < 0) {
		perror("read");
		return -1;
	}
	printf("read done\n");

	printf("sleeping 10s...\n");
	sleep(10);

	/* Unlock the region */
	fl.l_type   = F_UNLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start  = 0;        /* Offset from l_whence */
	fl.l_len    = 0;        /* length, 0 = to EOF   */
	fl.l_pid    = getpid(); /* our PID              */
	ret = fcntl(fd, F_UNLCK, &fl);
	if (ret < 0) {
		perror("fcntl(F_SETLKW)");
		return -1;
	}
	printf("unlock done\n");

	close(fd);

	return 0;
}
