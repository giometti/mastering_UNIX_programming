#include "unistd.h"
#include "stdio.h"

int main(void)
{
	pid_t pid;

	pid = getpid();
	printf("my PID is %d\n", pid);

	return 0;
}
