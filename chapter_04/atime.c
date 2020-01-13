#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define __USE_XOPEN
#include <time.h>	/* For strptime() and mktime() */

int main(int argc, char *argv[])
{
	struct tm tm;
	struct timespec times[2];
	char *c;
	int fd;
        int ret;

	/* Do not touch the last modification time! */
	times[1].tv_nsec = UTIME_OMIT;

        if (argc < 2) {
                fprintf(stderr, "usage: %s <file> [<newtime>]\n",
                        argv[0]);
                return -1;
        } else if (argc > 2) {
		/* Parse the new time as: Mmm DD HH:MM:SS YYYY*/
		c = strptime(argv[2],
			"%b %d %H:%M:%S %Y", &tm);
		if (c == NULL || *c != '\0') {
			fprintf(stderr, "invalid time!\n");
			return -1;	
		}
		times[0].tv_sec = mktime(&tm);
		times[0].tv_nsec = 0;
	} else {
		/* Set the current time */
		times[0].tv_nsec = UTIME_NOW;
	}

	ret = open(argv[1], O_RDONLY);
	if (ret < 0) {
		perror("open");
		return -1;
	}
	fd = ret;

	ret = futimens(fd, times);
	if (ret < 0) {
		perror("open");
		return -1;
	}

	close(fd);

        return 0;
}
