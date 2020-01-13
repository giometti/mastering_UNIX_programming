#include <unistd.h>
#include <stdlib.h>

#define MAX_SIZE	(1 << 20)	/* 1MB */

#define err(msg)	write_err(msg, sizeof(msg))

static int write_err(const char *msg, size_t len)
{
	return write(STDERR_FILENO, msg, len);
}

int main(int argc, char *argv[])
{
	int n, size;
	char buf[MAX_SIZE];

	if (argc < 2) {
		err("invalid command line\n");
		return -1;
	}
	size = atoi(argv[1]);

	while ((n = read(STDIN_FILENO, buf, size)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			err("write error\n");
	if (n < 0)
		err("read error\n");

	return 0;
}
