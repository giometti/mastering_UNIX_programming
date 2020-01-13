#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int ret;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		return -1;
	}

	printf("%s: ", argv[1]);
	ret = access(argv[1], F_OK);
	if (ret < 0) {
		perror("access");
		return -1;
	}
	ret = access(argv[1], R_OK);
	if (ret == 0)
		printf("r");
	ret = access(argv[1], W_OK);
	if (ret == 0)
		printf("w");
	ret = access(argv[1], X_OK);
	if (ret == 0)
		printf("x");
	printf("\n");

	return 0;
}
