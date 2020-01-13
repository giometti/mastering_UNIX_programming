#include <stdio.h>
#include <stdio_ext.h>

void print_buftype(char *name, int mode, size_t size)
{
	if (mode)
		fprintf(stderr, "%s is line buffered\n", name);
	else if (size > 1)
		fprintf(stderr, "%s is fully buffered, "
				"size is %ld bytes\n",
				name, size);
	else
		fprintf(stderr, "%s is unbuffered\n", name);
}

int main(void)
{
	/* The following two operations are needed to force
	 * the underlying mechanisms to correctly setup
	 * its internal data.
	 */
	fseek(stdout, 0, SEEK_SET);
	fseek(stdin, 0, SEEK_SET);

	/* Got stdin data information */
	print_buftype("stdin", __flbf(stdin),
				__fbufsize(stdin));

	/* Got stdin data information */
	print_buftype("stdout", __flbf(stdout),
				__fbufsize(stdout));

	/* Got stderr data information */
	print_buftype("stderr", __flbf(stderr),
				__fbufsize(stderr));
	return 0;
}
