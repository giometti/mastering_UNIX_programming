#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
	char *val;
	bool do_set = false, do_unset = false;
	int ret;

	/* Check the command line */
	if (argc < 2) {
		fprintf(stderr, "usage: %s [-]<var> [<val>]\n", argv[0]);
		return -1;
	}
	if (argv[1][0] == '-') {
		do_unset = true;
		argv[1]++;
	} else if (argc == 3)
		do_set = true;

	if (do_set || do_unset) {
		/* Try to set/unset the environment variable */
		if (do_set)
			ret = setenv(argv[1], argv[2], 1);
		else
			ret = unsetenv(argv[1]);
		if (ret) {
			perror(do_set ? "setenv" : "unsetenv");
			return -1;
		}
	}

	/* Try to get the environment variable */
	val = getenv(argv[1]);
	if (val == NULL) {
		fprintf(stderr, "variable %s %s\n", argv[1],
			do_unset ? "canceled" : "not found");
		return -1;
	}

	printf("%s\n", val);

	return 0;
}
