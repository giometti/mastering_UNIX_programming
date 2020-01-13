#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define TMP_FILE	"/tmp/file"

int main(void)
{
	int fd;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	/* Opens a file for writing creating the file if it does not
	 * already exist.
	 */
	fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, mode);
	if (fd < 0)
		perror("open(O_WRONLY | O_CREAT | O_TRUNC)");
	else
		close(fd);

	/* Try to create TMP_FILE file and then to open it for writing.
	 * Thanks to the O_EXCL flag the call fails if the file already
	 * exists otherwise the file existence and creation is done
	 * atomically.
	 */
	fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_EXCL, mode);
	if (fd < 0)
		perror("open(O_WRONLY | O_CREAT | O_EXCL)");
	else
		close(fd);

	return 0;
}
