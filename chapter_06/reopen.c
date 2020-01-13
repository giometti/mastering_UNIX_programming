#include <stdio.h>
#include <wchar.h>

int main(void)
{
	int mode;
	FILE *fp;

	mode = fwide(stdout, 0);
	wprintf(L"by default stdout has mode=%d\n", mode);
	mode = fwide(stdout, 0);
	wprintf(L"now stdout has mode=%d\n", mode);

	fp = freopen(NULL, "a+", stdout);
	if (!fp) {
		perror("freopen");
		return -1;
	}

	mode = fwide(stdout, 0);
	wprintf(L"after freopen() stdout has mode=%d\n", mode);

	return 0;
}
