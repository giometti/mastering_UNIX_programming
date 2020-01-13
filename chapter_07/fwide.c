#include <stdio.h>
#include <wchar.h>
#include <errno.h>

int main(void)
{
	int mode;

	errno = 0;
	mode = fwide(stdout, 0);
	if (errno) {
		perror("fwide");
		return -1;
	}
	wprintf(L"by default stdout has mode=%d\n", mode);

	errno = 0;
	mode = fwide(stdout, 0);
	if (errno) {
		perror("fwide");
		return -1;
	}
	wprintf(L"now stdout has mode=%d\n", mode);

	return 0;
}
