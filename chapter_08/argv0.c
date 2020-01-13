#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

int main(int argc, char *argv[])
{
	char *name;

	/* Get the file name removing the prepending path name */
	name = basename(argv[0]);

	/* Do different actions according to the invoking name */
	if (strcmp(name, "hello") == 0) {
		printf("hello ");
		if (argc >= 2)
			printf("%s!", argv[1]);
		else
			printf("world");
		printf("\n");
	} else if (strcmp(name, "sum") == 0) {
		if (argc >= 3)
			printf("%d\n", atoi(argv[1]) + atoi(argv[2]));
		else
			printf("too few arguments!\n");
	} else {
		printf("change my name!\n");
	}

	return 0;
}
