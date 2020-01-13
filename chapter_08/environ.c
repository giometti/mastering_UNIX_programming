#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char *argv[])
{
	int n;

	for (n = 0; environ[n]; n++)
		printf("environ[%d]=\"%s\"\n", n, environ[n]);

	return 0;
}
