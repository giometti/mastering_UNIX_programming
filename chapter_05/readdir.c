#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	struct stat buf;
	DIR *d;
	struct dirent *dp;
	int dirfd, fd;
        int ret;

        if (argc < 2) {
                fprintf(stderr, "usage: %s <dir>\n", argv[0]);
                return -1;
        }

	/* Open the directory entry */
	dirfd = open(argv[1], O_RDONLY);
	if (dirfd < 0) {
		perror("open");
		return -1;
	}

	/* Create the DIR stream over the dirfd */
	d = fdopendir(dirfd);
	if (d == NULL) {
		fprintf(stderr,
			"Cannot open %s directory\n", argv[1]);
		return -1;
	}

	/* Now iterate over files */
	printf("Files list for directory %s:\n", argv[1]);
	printf("size\tname\n");
	while ((dp = readdir(d)) != NULL) {
		/* Get a file descriptor for next direntry */
		fd = openat(dirfd, dp->d_name, O_RDONLY);
		if (fd < 0) {
			perror(dp->d_name);
			continue;
		}

		/* Get file's statistics */
		ret = fstat(fd, &buf);
		close(fd); /* fd is not needed anymore */
		if (ret < 0) {
			perror(dp->d_name);
			continue;
		}

		/* Print the file entry (size & name) */
		printf("%ld\t%s\n",
			(intmax_t) buf.st_size,
			dp->d_name);
	}

	closedir(d); /* this implicitly closes dirfd */

	return 0;
}
