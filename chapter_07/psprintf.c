#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifdef __GNUC__
static int psprintf(char **str, const char *name,
		const char *fmt, ...) \
		__attribute__ ((format (printf, 3, 4)));
#endif
static int psprintf(char **str, const char *name,
		const char *fmt, ...)
{
	int size;
	char *nfmt;
	va_list ap;
	int ret;

	/* Compute the new format size.
	 *
	 * The new format string is formed as:
	 *     <name>: <fmt>\0
	 * so it must be computed as:
	 */
	size = strlen(name) + strlen(fmt) + 3;

	/* Allocate the new format */
	nfmt = malloc(size);
	if (!nfmt)
		return -1;

	/* Build the new format as "<name>: <fmt>".
	 *
	 * Note that nft string has the right size so
	 * we can safely not check the return value
	 */
	snprintf(nfmt, size, "%s: %s", name, fmt);
	
	/* Compute the output size */
	va_start(ap, fmt);
	ret = vsnprintf(NULL, 0, nfmt, ap);
	va_end(ap);
	if (ret < 0)
		goto free_nfmt;
	size = ret + 1; /* for '\0' */

	/* Allocate the output buffer */
	*str = malloc(size);
	if (*str == NULL) {
		ret = -1;
		goto free_nfmt;
	}

	/* Build the output string */
	va_start(ap, fmt);
	ret = vsnprintf(*str, size, nfmt, ap);
	va_end(ap);
	if (ret < 0)
		goto free_nfmt;

free_nfmt:
	free(nfmt);

	return ret;
}

int main(int argc, char *argv[])
{
	char *msg;
	int ret;

        if (argc < 2) {
                fprintf(stderr, "usage: %s <prefix>\n",
                        argv[0]);
                return -1;
        }

	/* Format the message with the supplied prefix */
	ret = psprintf(&msg, argv[1],
		"some data: %d, %c\n", 10, 'x');
	if (ret < 0) {
		fprintf(stderr, "psprintf error\n");
		return -1;
	}

	/* Print the message on stdout */
	fputs(msg, stdout);

	/* Free the allocated memory buffer */
	free(msg);

	return 0;
}
