#include "unistd.h"
#include "string.h"

#define DATA_SIZE	(128<<10)	/* 128KB */

#define err(msg)	write_err(msg, sizeof(msg))

static int write_err(const char *msg, size_t len)
{
	return write(STDERR_FILENO, msg, len);
}

int main(void)
{
	int n;
	char buf[DATA_SIZE];

        memset(buf, 0, DATA_SIZE);
	for (n = 0; n < DATA_SIZE; n++)
		if (write(STDOUT_FILENO, &buf[n], 1) != 1) {
			err("write error\n");
			break;
		}

	return 0;
}
