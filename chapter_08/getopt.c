#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int c;
	int flag = 0, error = 0;
	char *name = NULL;
	int i;

	while ((c = getopt(argc, argv, ":af:")) != -1) {
		switch(c) {
		case 'a':
			flag++;
			break;
		case 'f':
			name = optarg;
			break;
		case ':':       /* missing operand? */
			fprintf(stderr,
				"option -%c requires an operand\n",
				optopt);
			error++;
			break;
		case '?':	/* invalid option? */
			fprintf(stderr,
				"unrecognized option '-%c'\n",
				optopt);
			error++;
		}
	}
	if (error) {
		fprintf(stderr,
			"usage: %s [-a] [-f <name>] [<arg> ...]\n",
			argv[0]);
		return -1;
	}

	/* Print the parsing result */
	if (flag)
		printf("-a\n");
	if (name)
		printf("-f=%s\n", name);
	for (i = optind; i < argc; i++)
		printf("argv[%d]=%s\n", i - optind, argv[i]);

	return 0;
}
