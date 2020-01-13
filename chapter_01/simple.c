#include "unistd.h"

#define BUFFSIZE	4096

#define err(msg)	write_err(msg, sizeof(msg))

static int write_err(const char *msg, size_t len)
{
	return write(STDERR_FILENO, msg, len);
}

int main(void)
{
	int n;
	char buf[BUFFSIZE];

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			err("write error\n");
	if (n < 0)
		err("read error\n");

	return 0;
}
