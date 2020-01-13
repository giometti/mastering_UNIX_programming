#include "stdio.h"
#include "string.h"

#define DATA_SIZE	(128<<10)	/* 128KB */

#define err(msg)	fputs(msg, stderr)

int main(void)
{
	int n;
	char buf[DATA_SIZE];

	memset(buf, 0, DATA_SIZE);
	for (n = 0; n < DATA_SIZE; n++)
		if (fputc(buf[n], stdout) != buf[n]) {
			err("write error\n");
			break;
		}

	return 0;
}
