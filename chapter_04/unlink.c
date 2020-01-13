#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int ret;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <file>\n",
			argv[0]);
		return -1;
	}

	printf("unlinking %s\n", argv[1]);
	ret = unlink(argv[1]);
	if (ret < 0) {
		perror("link");
		return -1;
	}

	return 0;
}
