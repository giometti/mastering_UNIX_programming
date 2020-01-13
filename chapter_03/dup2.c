#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int ret;

	ret = dup2(STDOUT_FILENO, STDERR_FILENO);
	if (ret < 0) {
		perror("dup2");
		return -1;
	}

	/* WARNING: this is an example! NEVER, NEVER, NEVER call
	 *          a system call without checking its return value!
	 */
	write(STDOUT_FILENO, "stdout\n", 7);
	write(STDERR_FILENO, "stderr\n", 7);

	return 0;
}
