#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int ret;

	if (argc < 3) {
		fprintf(stderr, "usage: %s <oldfile> <newfile>\n",
			argv[0]);
		return -1;
	}

	printf("linking %s to %s\n", argv[1], argv[2]);
	ret = link(argv[1], argv[2]);
	if (ret < 0) {
		perror("link");
		return -1;
	}

	return 0;
}
