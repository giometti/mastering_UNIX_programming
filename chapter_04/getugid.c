#ifdef _HAS_GETRESUID
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#ifdef _HAS_GETRESUID
static uid_t getsuid(void)
{
	uid_t dummy, suid;

	getresuid(&dummy, &dummy, &suid);
	/* No errors checks... see manpages */

	return suid;
}

static gid_t getsgid(void)
{
	gid_t dummy, sgid;

	getresgid(&dummy, &dummy, &sgid);
	/* No errors checks... see manpages */

	return sgid;
}
#endif

int main(int argc, char *argv[])
{
	int ret;

	printf("real user/group ID:      %d/%d\n", getuid(), getgid());
	printf("effective user/group ID: %d/%d\n", geteuid(), getegid());
#ifdef _HAS_GETRESUID
	printf("saved user/group ID:     %d/%d\n", getsuid(), getsgid());
#endif

	if (argc > 1) {
		ret = open(argv[1], O_RDONLY);
		printf("file %s can%s be read\n",
			argv[1], ret < 0 ? "'t" : "");
	}

	return 0;
}
