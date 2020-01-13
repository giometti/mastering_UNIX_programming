#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int  fd;
	char buf[32];
	int ret;
	struct flock fl;

        /* Open the file */
        fd = open("file.locked", O_WRONLY);
        if (fd < 0) {
                perror("open");
                return -1;
        }
        printf("file opened\n");

	/* Establish the write lock */
	fl.l_type   = F_WRLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start  = 0;        /* Offset from l_whence */
	fl.l_len    = 0;        /* length, 0 = to EOF   */
	fl.l_pid    = getpid();
	ret = fcntl(fd, F_SETLKW, &fl);
	if (ret < 0) {
                perror("fcntl(F_SETLKW)");
                return -1;
        }
        printf("write lock get\n");

	ret = write(fd, buf, 32);
        if (ret < 0) {
                perror("write");
                return -1;
        }
        printf("write done\n");

        printf("sleeping 10s...\n");
        sleep(10);

        /* Unlock the region */
        fl.l_type   = F_UNLCK;
        fl.l_whence = SEEK_SET;
        fl.l_start  = 0;        /* Offset from l_whence */
        fl.l_len    = 0;        /* length, 0 = to EOF   */
        fl.l_pid    = getpid();
        ret = fcntl(fd, F_UNLCK, &fl); 
        if (ret < 0) {
                perror("fcntl(F_SETLKW)");
                return -1;
        }
        printf("unlock done\n");

	close(fd);

	return 0;
}
